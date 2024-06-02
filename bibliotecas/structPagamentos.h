#ifndef structPagamentos_h
#define structPagamentos_h

#include "calculaTotaisVendas.h"


/*Esta armazena a venda já fechada e possui um índice (códgo da venda) para ser consultada depois;*/
typedef struct 
{
    int codigoVenda;
    float valorTotalVenda;
    char tipoPag[2];
    float vTotalPagoDinheiro;
    float vTotalPagoCartao;
} HistoricoVendas;


HistoricoVendas* fAlocaMemoriaVendas(HistoricoVendas* Venda, int vIndiceVenda){
    HistoricoVendas* vEndMemoriaAlocada;
    if (vIndiceVenda ==0)
    {
        
        vEndMemoriaAlocada = (HistoricoVendas*)calloc((vIndiceVenda+1),sizeof(HistoricoVendas));
        return vEndMemoriaAlocada;
    } else
    {
        vEndMemoriaAlocada = (HistoricoVendas*) realloc(Venda,(vIndiceVenda+1)* sizeof(HistoricoVendas));
        return vEndMemoriaAlocada;
    }
    if (vEndMemoriaAlocada == NULL)
    {
        printf("Falha ao alocar memoria\n"); 
        return NULL;
    }   
}

float fExibeDesconto(float vTotalVenda, float vPercDesconto){
    float vDesconto =0;
    if (vTotalVenda <= 50)
    {
        vDesconto = vTotalVenda*0.05;
        return vDesconto;
    } else if (vTotalVenda >50 && vDesconto <200)
    {
        vDesconto = vTotalVenda*0.1;
        return vDesconto;
    } else if (vTotalVenda>=200)
    {
        vDesconto = vTotalVenda*(vPercDesconto/100);
        return vDesconto;
    }    
    return vDesconto;   
}
void fMenuPagamento(float vTotalVenda){
    system("cls");
    printf("Compra no valor total de R$ %.2f\n",vTotalVenda); 
    if (vTotalVenda<200)
    {
        printf("Lhe dá direito a um desconto de R$ %.2f (%d%%) para pagamento em dinheiro\n",fExibeDesconto(vTotalVenda,0),((vTotalVenda<50)?5:10)); 
    } else
    {
        printf("Lhe dá direito a um desconto(pagando em espécie), que será decidido pelo bom humor da dona!\nBoa sorte =)\n"); 
    }
    printf("As opções de pagamento são:\n"); 
    printf("1. Dinheiro\n"); 
    printf("2. Cartão\n"); 
}
void fProcessaPagamentoDinheiro(){}
void fProcessaPagamentoCartao(){}
#endif