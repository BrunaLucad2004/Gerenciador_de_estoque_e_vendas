#define CABECALHO_H

// Definindo a struct para produtos
typedef struct {
    int id;
	char nome[50];
    int quantidade;
    float preco;
} Produto;

// Definindo a struct para os nos da fila
typedef struct no {
	Produto *produto;
	struct no* prox;
} No;

// Definindo a struct para a fila
typedef struct fila{
	No* inicio;
	No* fim;
} Fila;

// Definindo a struct para os nos da pilha
typedef struct no_pilha {
    Produto *produto;
    int operacao;
    struct no_pilha* prox;
} NoP;

// Definindo a struct para a pilha
typedef struct Pilha {
    NoP* topo;
} Pilha;


// Protótipos das funções

//FUNÇÕES DO PRODUTO:

//Cria um produto vazio e retorna um ponteiro do tipo produto;
Produto* criar_produto();

//Realiza a leitura das informações de um produto, este passado como parametro;
void ler_produto(Produto *produto);

//Imprime as informações do produto passado como parametro;
void imprimir_produto(Produto *prod);


//FUNÇÕES DA FILA:

//Cria uma fila vazia e retorna um ponteiro do tipo pilha;
Fila* criar_fila();

//Realiza a inserção de um produto no final da fila;
void inserir(Fila* f, Produto *prod);

//Imprime todos os itens presentes na fila passada como parametro;
void imprimir_fila(Fila* f);

//Realiza a remoção do produto da fila, passando como a fila como parametro 
//e o ID do produto a ser removido, se realizado com sucesso retorna 1, caso contrario 0;
int remover_produto(Fila* f, int id);

//Verifica se o produto, este sendo referenciado pelo ID,
//está presente na fila passada como parametro;
int existe_produto(Fila* f, int id);

//Adiciona um produto na fila: obtendo as informações do produto, 
//verificando se ele ja esta presente na fila, se não o insere;
void adicionar_produto(Fila* f, Produto *produto);

//Realiza a atualização da quantidade de um produto presente na fila;
void Repor_Estoque(Fila* f, int id, int quantidade_adicionada);

//Realiza a busca por um produto na lista, imprimindo as informações em seguida;
int consultar_item(Fila* f, int id);


//FUNÇÕES DA PILHA:

//Cria uma pilha vazia e retorna um ponteiro do tipo pilha;
Pilha* cria_pilha();

//Realiza a inserção de um produto sempre no topo da pilha;
void push(Pilha* p, Produto *produto);

//Realiza a insercao de um inteiro referente a operação realizada,passada como parametro
// assim como a pilha aonde será empilhada a informação;
void pushh(Pilha* p, int operacao);

//Imprimir pilha de operacoes realizadas;
void imprime_operacoes(Pilha *p);

//Realiza a venda de um produto: primeira busca o produto na fila,
//através do ID, posteriomente atualiza a quantidade do produto em estoque,
//e registra essa venda em na pilha passada como parametro;
void vender_produto(Fila* f, Pilha *pilha, int id, int quantidade);

//Calcula o valor total das vendas, calculando a quantidade de produtos vendidos registrado na pilha;
float calcular_vendas(Pilha* p);

//Imprime na tela o historico de vendas realizadas, armazenadas na pilha que foi passada como parametro,
//também apresenta o total das vendas;
void imprimir_historico(Pilha* p);