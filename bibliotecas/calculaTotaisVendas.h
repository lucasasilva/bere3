#ifndef calcuTotaisVendas_h
#define calcuTotaisVendas_h

#include <stdbool.h>

#include "structsCadastrosProdutos.h"

typedef struct 
{
    float totalVendaDinheiro;
    float totalVendaCartao;
    float totalDescontos;
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
/*Percorre a lista de produtos cadastrados e retorna o "preço de venda" * quantidade escolhida pelo cliente*/
float fRetornaTotalBrutoProduto(int codProduto, int qtdProdutosCadastrados, int qtdCompra, Produtos* produto){
    float precoVenda = 0;
    float valorTotalItem= 0;
    for (int i = 0; i < qtdProdutosCadastrados; i++)
    {
        if (produto[i].codigoProduto == codProduto)
        {
            precoVenda = fRetornaPrecoVenda(codProduto,qtdProdutosCadastrados, produto);
            valorTotalItem= (qtdCompra*precoVenda);
            return valorTotalItem;
        }    
    }
    return 0;
}

/*Aloca memória para +1 produto na lista, sempre que a pessoa escolhe continuar comprando
se for a primeira vez, libera espaço para 1 produto*/
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
    if (vEndMemoriaAlocada == NULL)
    {
        printf("Falha ao alocar memoria\n"); 
        return NULL;
    }   
}

/*Guarda os dados da venda na estrutura*/
void fRegistraprodutosVendaAtual(int produto, int produtosIndice, int produtosAlocadas, VendaAtual* venda, int quantidade, Produtos* cadProd){
    venda[produtosIndice].codigoProduto = produto;
    venda[produtosIndice].quantidade = quantidade,
    venda[produtosIndice].valorTotalItem = fRetornaTotalBrutoProduto(produto, produtosAlocadas, quantidade, cadProd);
    venda[produtosIndice].sequenciaProduto = produtosIndice+1;
}
/*Exibe os dados da venda atual na tela de forma de pagamento*/
void fExibeTotaisVendaAtual(int sequenciaProduto, int qtdProdutosCadastrados, VendaAtual* vVenda, Produtos* vListaProdutos){
    printf("%-7s %-10s %-10s %-10s %-10s\n", 
           "Código", "Descrição", "Preço Venda", "Quantidade", "Total"); 
    for (int  i = 0; i < sequenciaProduto; i++)
    {
        printf("%-7d %-10s R$ %-10.2f %-8d %-10.2f\n",
                vVenda[i].codigoProduto,
                fRetornaNomeProduto(vVenda[i].codigoProduto,qtdProdutosCadastrados, vListaProdutos),
                fRetornaPrecoVenda(vVenda[i].codigoProduto,qtdProdutosCadastrados, vListaProdutos),
                vVenda[i].quantidade,
                vVenda[i].valorTotalItem); 
    }
    
}

float fRetornaTotalVendaAtual(VendaAtual* vVenda, int vSequenciaMaxProduto){
    float totalVendaAtual=0;
    for (int i = 0; i <=vSequenciaMaxProduto; i++)
    {
        totalVendaAtual+=vVenda[i].valorTotalItem;   
    }
    return totalVendaAtual;
}


bool fBloqueiaVendaEstoqueNegativoZerado(Produtos* produto, int quantidadeVenda){
    if ((produto->qtdEstoque- quantidadeVenda) <=0)
    {
        return 0;
    }
    return 1;
}
#endif