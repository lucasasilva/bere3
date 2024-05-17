
#include <stdio.h>
#include <stdlib.h>

//#include "utilidades.h"

typedef struct 
{
    int codigoProduto;
    char nomeProduto[80];
    int categoria;
    float custoProduto;
    float margemLucro;
} Produtos;

typedef struct 
{
    char rua[100];
    int  ruaNumero;
    char bairro[50];
} Endereco;

typedef struct 
{
   int codigo;
   char nomeRegistro[150];
   char nomeSocial[150];
   char cpf[14];
   Endereco Endereco;
} Terceiros;

typedef struct 
{
    float totalVendaAtual;
    float totalVendaDinheiro;
    float totalVendaCartao;
    float totalVendidoDia;
} SaldosVendas;

typedef struct 
{
    int codigoVenda;
    int codigoProduto;
    int quantidade;
    float valorTotalItem;
    char status;   
} Venda;


void fRetornaProdutosCadastros (Produtos *produto, int tamanho, char *categoria){
    printf("Código \tNome \t\tCategoria \t\tCusto \tMargem de Lucro\n"); 
    for (int i = 0; i < tamanho; i++) {
        printf("%d \t%s  \t%s \t%.2f \t%.2f%%", produto[i].codigoProduto, produto[i].nomeProduto, categoria, produto[i].custoProduto, produto[i].margemLucro);
        printf("\n");
    }
}