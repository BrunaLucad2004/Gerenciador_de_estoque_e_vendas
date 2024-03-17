#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

int main() {
    
    Fila* fila = criar_fila();
    Pilha* pilha = cria_pilha();
    Pilha* registro = cria_pilha();

    int id, opcao;
    int flag = 0;
    Produto *produto;

    do {
        printf("\n Gerenciador de Vendas e Estoque\n");
        printf("-------------------------------\n");
        printf("     1 - Adicionar produto\n");
        printf("     2 - Remover produto\n");
        printf("     3 - Vender produto\n");
        printf("     4 - Listar produtos\n");
        printf("     5 - Historico de Vendas\n");
        printf("     6 - Repor Estoque\n");
        printf("     7 - Consultar Produto\n");
        printf("     8 - Historico de Operacoes\n");
        printf("     0 - Sair\n");
        printf("-------------------------------\n");
        printf("    Digite a opcao desejada: ");
        scanf("%d", &opcao);
        

        switch(opcao) {
            case 0:
                flag = 1;
                printf("    Saindo...\n");
                break;
            case 1:
                pushh(registro, opcao);
                produto = criar_produto();
				ler_produto(produto);
                adicionar_produto(fila, produto);
                break;
            case 2:
                
                pushh(registro, opcao);
                printf("\nDigite o ID do produto: ");
                scanf("%d", &id);
                if(remover_produto(fila, id)) {
                    printf("\nProduto removido com sucesso!\n");
                }else{
                    printf("\nProduto nao encontrado!\n");
                }
                break;
            case 3:
                pushh(registro, opcao);
                int venda;
                printf("\nDigite o ID do produto: ");
                scanf("%d", &id);
                if(existe_produto(fila, id)){
                    printf("\nDigite a quantiade de produtos vendidos: ");
                    scanf("%d", &venda);
                    vender_produto(fila, pilha, id, venda);
                }else{
                     printf("\nProduto nao encontrado!\n");
                }
                break;
            case 4:
                pushh(registro, opcao);
                imprimir_fila(fila);
                break;
            case 5:
                pushh(registro, opcao);
                imprimir_historico(pilha);
                break;
            case 6:
                pushh(registro, opcao);
                int reposicao;
                printf("\nDigite o ID do produto: ");
                scanf("%d", &id);
                if(existe_produto(fila, id)){
                    printf("\nDigite a nova quantidade do produto: ");
                    scanf("%d", &reposicao);
                    Repor_Estoque(fila, id, reposicao);
                }else{
                     printf("\nProduto nao encontrado!\n");
                }
                break;
            case 7:
                pushh(registro, opcao);
                printf("\nDigite o ID do produto: ");
                scanf("%d", &id);
                if(existe_produto(fila, id)){
                    consultar_item(fila, id);
                }else{
                     printf("\nProduto nao encontrado!\n");
                }
                break;
            case 8:
                pushh(registro, opcao);
                imprime_operacoes(registro);
                break;
            default:
                printf("    Opcao Invalida!!");
                break;
        }
    } while(flag == 0);
    
    return 0;
}
