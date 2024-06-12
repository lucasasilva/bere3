#ifndef structPagamentos_h
#define structPagamentos_h

#include "calculaTotaisVendas.h"
#include "utilidades.h"


/*Esta armazena a venda já fechada e possui um índice (códgo da venda) para ser consultada depois;*/
typedef struct 
{
    int codigoVenda;
    float valorTotalVenda;
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

void fGravaVendasDia(int vIndiceVenda, HistoricoVendas* vVendasDia, SaldosVendas *vSaldosVendas, float *vDesconto){
    vVendasDia[vIndiceVenda-1].codigoVenda = vIndiceVenda;
    vVendasDia[vIndiceVenda-1].vTotalPagoCartao = vSaldosVendas->vValorPagoCartaoVendaAtual;
    vVendasDia[vIndiceVenda-1].vTotalPagoDinheiro = vSaldosVendas->vValorPagodinheiroVendaAtual;
    vVendasDia[vIndiceVenda-1].valorTotalVenda = (vSaldosVendas->vValorPagoCartaoVendaAtual+vSaldosVendas->vValorPagodinheiroVendaAtual+*vDesconto);

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
    system("clear || cls");
    printf("Compra no valor total de R$ %.2f\n",vTotalVenda); 
    if (vTotalVenda<200)
    {
        printf("Lhe dá direito a um desconto de R$ %.2f (%d%%) para pagamento em dinheiro\n",fExibeDesconto(vTotalVenda,0),((vTotalVenda<50)?5:10)); 
        printf("Totalizando: R$ %.2f\n", (vTotalVenda-fExibeDesconto(vTotalVenda,0))); 
    } else
    {
        printf("Lhe dá direito a um desconto(pagando em espécie), que será decidido pelo bom humor da dona!\nBoa sorte =)\n"); 
    }
    printf("As opções de pagamento são:\n"); 
    printf("1. Dinheiro\n"); 
    printf("2. Cartão\n");
    printf("3. Sair\n");  
}
void fProcessaPagamentoDinheiro(float* vTotalVenda, SaldosVendas *vSaldosVendas, float *vDesconto, float *vTotalPago){
    /*Para não ter que lidar com isso na main. Se o total pago for maior que o total devido, para fim dos cálculos,
    interpreta-se que a venda foi totalmente quitada.*/
    if (vTotalPago > vTotalVenda)
    {
        *vTotalPago = *vTotalVenda;
    }
    
    vSaldosVendas->totalVendidoDia+=*vTotalVenda;
    *vTotalVenda -= (*vDesconto+*vTotalPago);
    vSaldosVendas->saldoDisponivelDinheiro+=*vTotalPago;
    vSaldosVendas->totalDescontos+=*vDesconto;
    vSaldosVendas->totalVendaDinheiro+=*vTotalPago-*vDesconto;
    vSaldosVendas->vValorPagodinheiroVendaAtual+=*vTotalPago;
}

void fProcessaPagamentoCartao(float* vTotalVenda, SaldosVendas* vSaldosVendas, float *vTotalPago){
    vSaldosVendas->totalVendidoDia+=*vTotalVenda;
    vSaldosVendas->totalVendaCartao+=*vTotalPago;
    vSaldosVendas->vValorPagoCartaoVendaAtual+=*vTotalPago;
    *vTotalVenda -= (*vTotalPago);

}

void fImprimeVendas(int vIndiceVendas, HistoricoVendas* vVendasDia){
    system("clear || cls");
    printf("%-20s %-20s %-20s %-20s\n", 
    "Código venda", "Total Dinheiro", "Total Cartão", "Total Venda");
    for (int i = 0; i < vIndiceVendas; i++)
    {
        printf("%-20d %-20.2f %-20.2f %-20.2f\n",
        vVendasDia[i].codigoVenda,
        vVendasDia[i].vTotalPagoDinheiro,
        vVendasDia[i].vTotalPagoCartao,
        vVendasDia[i].valorTotalVenda); 
    }
    
}

void fFechamentoCaixa(SaldosVendas *vSaldoVendas, int vIndiceVendas){
    printf("Valor abertura caixa: %.2f\n",vSaldoVendas->vValorAberturaCaixa); 
    printf("Quantidade de vendas do dia: %d\n",vIndiceVendas);
    printf("Total venda cartões: %.2f\n",vSaldoVendas->totalVendaCartao); 
    printf("Total vebda dinheiro: %.2f\n",vSaldoVendas->totalVendidoDia); 
    printf("Total descontos ofertados: %.2f\n", vSaldoVendas->totalDescontos);
    printf("Total geral vendas: %.2f\n",(vSaldoVendas->totalVendaCartao+vSaldoVendas->totalVendidoDia+vSaldoVendas->totalDescontos)); 
    printf("Total sangrias dia: %.2f\n",vSaldoVendas->vSangriasdias);   
}

#endif