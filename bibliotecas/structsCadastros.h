
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
    int qtdEstoque;
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

char* fREtornaCategoria(int categoria){
    switch (categoria)
    {
    case 1:
        return "Material de Limpeza";
        break;
    case 2:
        return "Alimentos & Bebidas";
        break;
    case 3:
        return "Padaria";
        break;
    default:
        return "Categoria não cadastrada";
        break;
    }
}

void fRetornaCadastrosProdutos (Produtos *produto, int tamanho){    
    printf("%-8s %-19s %-20s %-10s %-16s %-20s\n","Código", "Nome", "Categoria", "Custo", "Margem de Lucro(%)", "Quantidade em Estoque"); 
    for (int i = 0; i < tamanho; i++) {
        if (produto[i].categoria== 1)
        {
            printf("%-7d %-19s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, produto[i].nomeProduto, fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }
        else if (produto[i].categoria==2)
        {
            printf("%-7d %-20s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, produto[i].nomeProduto, fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }
        else if (produto[i].categoria==3)
        {
            printf("%-7d %-21s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, produto[i].nomeProduto, fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }      
    }
}