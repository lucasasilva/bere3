#ifndef calcuTotaisVendas_h
#define calcuTotaisVendas_h

#include "structsCadastrosProdutos.h"

typedef struct 
{
    float totalVendaAtual;
    float totalVendaDinheiro;
    float totalVendaCartao;
    float totalVendidoDia;
    float saldoDisponivelDinheiro;
} SaldosVendas;

typedef struct 
{
    int codigoVenda;
    int codigoProduto;
    int quantidade;
    float valorTotalItem;
    char status;   
} Venda;

void fCalculaTotalVendaAtual(Produtos *entrada){
    printf("Teste 1");
}

#endif