#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNCOES DOS PRODUTOS
Produto* criar_produto(){
	Produto* prod = malloc(sizeof(Produto));
    if(prod){
    	prod->preco = 0.00;
    	prod->quantidade = 0;
    	return prod;
    }
}

void ler_produto(Produto *produto){
	printf("\nDigite o ID do produto: ");
    scanf("%d", &produto->id);
    fflush(stdin);
    printf("Digite o nome do produto: ");
    scanf(" %49[^\n]", produto->nome);
    fflush(stdin);
    printf("Digite o preco do produto: ");
    scanf("%f", &produto->preco);
    fflush(stdin);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &produto->quantidade);
    fflush(stdin);
}

void imprimir_produto(Produto *prod){
	printf("    ID: %d\n", prod->id);
	printf("    Nome: %s\n", prod->nome);
	printf("    Preco: %0.2f\n", prod->preco);
	printf("    Quantidade em Estoque: %d\n", prod->quantidade);
}


//FUNCOES DA FILA

Fila* criar_fila(){
	Fila* f = malloc(sizeof(Fila));
	if(f){
		f->inicio = NULL;
		f->fim = NULL;
		return f;
	}else{
		printf("ERRO DE ALOCACAO");
		exit(1);
	}
}

void inserir(Fila* f, Produto *prod){ 
	No* novo = malloc(sizeof(No));
	
	if(novo){
		novo->produto = prod;
		novo->prox = NULL;
		
		if(f->inicio == NULL){ 
			f->inicio = novo;
		}else{
			f->fim->prox = novo;
		}	
		
		f->fim = novo;
		
	}else{
		printf("ERRO DE ALOCACAO");
		exit(1);
	}
}

void imprimir_fila(Fila* f){
    No* aux = f->inicio;

    if(aux == NULL) {
        printf("\nNenhum produto cadastrado!");
        return;
    }

    printf("\n Lista de produtos:\n");
    printf("ID | Nome.....................| Preco.....| Quantidade\n");
    printf("--------------------------------------------------");

    while(aux != NULL) {
        printf("\n%-2d | %-19s| R$ %.2f   | %-9d", aux->produto->id, aux->produto->nome, aux->produto->preco, aux->produto->quantidade);
        aux = aux->prox;
    }
     printf("\n");
}


int remover_produto(Fila* f, int id) {
    No* aux = f->inicio;
    No* ant = NULL;

    while(aux != NULL) {
        
        if(aux->produto->id == id) {
            
            if(ant == NULL) {
                f->inicio = aux->prox;
            } else {
                ant->prox = aux->prox;
            }
            
            if(aux->prox == NULL) {
                f->fim = ant;
            }
            
            imprimir_produto(aux->produto);
            free(aux);
            
            return 1;
        
        }
        
        ant = aux;
        aux = aux->prox;
    }
    
    return 0;
}

void adicionar_produto(Fila* f, Produto *produto) {
    if(existe_produto(f, produto->id)) {
        printf("\nProduto ja cadastrado!\n");
    } else {
        inserir(f, produto);
        printf("\nProduto adicionado com sucesso!\n");
    }
}

void Repor_Estoque(Fila* f, int id, int valor){
    No* aux = f->inicio;
    
    while(aux != NULL) {
        if(aux->produto->id == id) {
            int ant = aux->produto->quantidade;
            aux->produto->quantidade = (ant + valor);
            return ;
        }
        aux = aux->prox;
    }
}

int consultar_item(Fila* f, int id){
    No* aux = f->inicio;
    
    while(aux != NULL) {
        if(aux->produto->id == id) {
            imprimir_produto(aux->produto);
        }
        aux = aux->prox;
    }
    
}

// FUNCOES DA PILHA
Pilha* cria_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if(p){
        p->topo = NULL;
        return p;
    }
}

//Para empilhar produtos
void push(Pilha* p, Produto *produto) { 
    NoP* novo = (NoP*) malloc(sizeof(NoP));
    if(novo){
    	novo->produto = produto;
    	novo->prox = p->topo;
    	p->topo = novo;
	}else{
		printf("ERRO DE ALOCACAO");
		exit(1);
	}
}

//Para empilhar operações
void pushh(Pilha* p, int operacao) { 
    NoP* novo = (NoP*) malloc(sizeof(NoP));
    if(novo){
    	novo->operacao = operacao;
    	novo->prox = p->topo;
    	p->topo = novo;
	}else{
		printf("ERRO DE ALOCACAO");
		exit(1);
	}
}

//Imprimir pilha de operacoes;
void imprime_operacoes(Pilha *p){
    NoP* aux = p->topo;
    
    printf("      HISTORICO DE OPERACOES:       ");
    printf("\n");
    while(aux != NULL){
        switch(aux->operacao){
            
            case 1:
                printf("     1 - Adicionar produto\n");
                break;
            case 2:
                printf("     2 - Remover produto\n");
                break;
            case 3:
                printf("     3 - Vender produto\n");
                break;
            case 4:
                printf("     4 - Listar produtos\n");
                break;
            case 5:
                printf("     5 - Historico de Vendas\n");
                break;
            case 6:
                printf("     6 - Repor Estoque\n");
                break;
            case 7:
                printf("     7 - Consultar Produto\n");
                break;
            case 8:
                printf("     8 - Historico de Operacoes\n");
                break;
        }
        
        aux = aux->prox;
    }
}

void vender_produto(Fila* f, Pilha *pilha, int id, int quantidade) {

    No* aux = f->inicio;
    
    while(aux != NULL) {
        if(aux->produto->id == id) {
            if(aux->produto->quantidade > 0 && quantidade <= aux->produto->quantidade) {
                aux->produto->quantidade = (aux->produto->quantidade - quantidade);
                
                Produto *produto_vendido = malloc(sizeof(Produto));
				if(produto_vendido){
					produto_vendido->id = aux->produto->id;
					strcpy (produto_vendido->nome, aux->produto->nome);
					produto_vendido->preco = aux->produto->preco;
					produto_vendido->quantidade = quantidade;	
				} else{
					printf("ERRO DE ALOCACAO");
					exit(1);
				}
				
                push(pilha, produto_vendido);
                
                printf("\n   Venda realizada com sucesso!\n");
                printf("\n   Novo estoque: %d\n", aux->produto->quantidade);
            } else {
                printf("\n   Produto sem estoque!\n");
            }
            return;
        }
        aux = aux->prox;
    }

    printf("\n  Produto nao encontrado!\n");
}

float calcular_vendas(Pilha* p){
	NoP* aux = p->topo;
	
	if(aux != NULL){
		float soma = 0;
		
		while(aux != NULL) {
        	soma += (aux->produto->preco * aux->produto->quantidade);
        	aux = aux->prox;
    	}
    	
    	return soma;
	}
	
	return 0;
}


void imprimir_historico(Pilha* p) {
    NoP* aux = p->topo;

    if(aux == NULL) {
        printf("\n  Nenhuma venda realizada!\n");
        return;
    }
    printf("\nHistorico de vendas:\n");
    printf("ID | Nome.................| Preco.....| Quantidade\n");
    printf("--------------------------------------------------");
    while(aux != NULL) {
        printf("\n%-2d | %-19s| R$ %.2f   | %-9d", aux->produto->id, aux->produto->nome, aux->produto->preco, aux->produto->quantidade);
        aux = aux->prox;
    }
    
    printf("\nTOTAL DAS VENDAS:  %.2f\n", calcular_vendas(p));
    
}
