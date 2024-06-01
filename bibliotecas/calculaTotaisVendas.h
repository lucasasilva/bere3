#ifndef calcuTotaisVendas_h
#define calcuTotaisVendas_h

#include <stdbool.h>

#include "structsCadastrosProdutos.h"

typedef struct 
{
    float totalVendaDinheiro;
    float totalVendaCartao;
    float totalVendidoDia;
    float saldoDisponivelDinheiro;
} SaldosVendas;

/*Esta armazena a venda já fechada e possui um índice (códgo da venda) para ser consultada depois;*/
typedef struct 
{
    int codigoVenda;
    int codigoProduto;
    int quantidade;
    float valorTotalItem;
} HistoricoVendas;

/*Esta serve para manter o controle da venda corrente e será descarregada na de cima, quando a venda for fechada
gerando um índice (código de venda)
Isso faz com que não tenhamos que realocar memória toda vez que a pessoa entra na*/
typedef struct 
{
    int sequenciaProduto;
    int codigoProduto;
    int quantidade;
    float valorTotalItem;
} VendaAtual;


VendaAtual* fAlocaMemoriaProdutos(VendaAtual* Venda, int vIndiceProduto){
    VendaAtual* vEndMemoriaAlocada;
    if (vIndiceProduto ==0)
    {
        vEndMemoriaAlocada = (VendaAtual*)calloc((vIndiceProduto+1),sizeof(VendaAtual));
        return vEndMemoriaAlocada;
    } else
    {
        vEndMemoriaAlocada = (VendaAtual*) realloc(Venda,(vIndiceProduto+1)* sizeof(VendaAtual));
        return vEndMemoriaAlocada;
    }
    return NULL;
    
}

/*Percorre a lista de produtos cadastrados e retorna o "preço de venda" * quantidade escolhida pelo cliente*/
float fRetornaTotalBrutoProduto(int codProduto, int qtdProdutosCadastrados, int qtdCompra){
    Produtos* produto;
    for (int i = 0; i < qtdProdutosCadastrados; i++)
    {
        if (produto[i].codigoProduto == codProduto)
        {
            return (produto[i].custoProduto * (produto[i].margemLucro/100))*qtdCompra;
        }    
    }
    return 0;
}


void fRegistraprodutosVendaAtual(int produto, int produtosIndice, int produtosAlocadas, VendaAtual* venda, int quantidade){
    venda[produtosIndice].codigoProduto = produto;
    venda[produtosIndice].quantidade = quantidade,
    venda[produtosIndice].valorTotalItem = fRetornaTotalBrutoProduto(produto, produtosAlocadas, quantidade);
    venda[produtosIndice].sequenciaProduto = produtosIndice+1;
}

bool fBloqueiaVendaEstoqueNegativoZerado(Produtos* produto, int quantidadeVenda){
    if ((produto->qtdEstoque- quantidadeVenda) <=0)
    {
        return 0;
    }
    return 1;
}
#endif