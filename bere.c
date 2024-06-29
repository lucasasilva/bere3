#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"
#include "./bibliotecas/structsCadastrosProdutos.h"
#include "./bibliotecas/structCadastrosTerceiros.h"
#include "./bibliotecas/calculaTotaisVendas.h"
#include "./bibliotecas/structPagamentos.h"
#include "./bibliotecas/utilidades.h"

int main()
{   
    /*Porque linux usa / e windows usa \ como separador de pasta, vamos de variável global para não quebrar as chamadas
    aí, em vossas máquinas, basta mudar os caminhos aqui (lembrando de usar \\) que vai dar bom*/
    char vCaminhoArquivoProduto[100] = "./data/Produtos.csv";
    char vCaminhoArquivoTerceiro[100] = "./data/Terceiros.csv";


    system("chcp 65001"); // Muda a página de código dos consoles para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
    int vMenu;
    int vInputUsuario;
    int vProduto, vQuantidade;
    float vValorPagar;

    /*Uma forma de manter controle sobre quanto temos alocado e quantos produtos temos "cadastrados", já que essa bosta dessa linguagem
    não permite o rastreio de quantos bytes uma variável tem alocada em memória.*/
    int vAlocacaoMemoriaVendas = 0;
    int vAlocacaoMemoriaCliente =fRetornaQTDTercArquivo(vCaminhoArquivoTerceiro, "T");
    printf("qtd clientes lidos %d\n",vAlocacaoMemoriaCliente); 
    int vAlocacaoMemoriaProdutos = fRetornaQTDItensArquivo(vCaminhoArquivoProduto, "P"); //Percorre o arquivo de produtos e retorna a quantidade máxima de produtos cadastrados;


    int vIndiceVenda = 0;   // indice das vendas armazenadas no dia. Pensem isso como um "generator".
    int vIndiceProduto = 0; // seve para adicionarmos mais itens a venda;


    float vDesconto = 0;
    float vPercDesconto;
    float vTotalVendaAtual = 0;
    float vRetiradaCaixa;
    char vValidaAberturaCaixa = 'N';
    char vContinuaCompra = 'S';
    char vStatusVenda = 'F'; //VERIFICA SE HÁ VENDA UMA VENDA EM ABERTO OU NÃO

    Terceiros *cliente = NULL;
    cliente = (Terceiros *)fAlocaMemoria(cliente, vAlocacaoMemoriaCliente, sizeof(Terceiros));
    fAlocaTerceirosLidosArquivo(cliente, vCaminhoArquivoTerceiro);

    Produtos *produto = NULL; 
    produto =(Produtos *)fAlocaMemoria(produto, vAlocacaoMemoriaProdutos,sizeof(Produtos));//Aloca memória o suficiente para a quantidade de produtos previamente lida no arquivo 
    fAlocaProdutosLidosArquivo(produto, vCaminhoArquivoProduto);//Aloca, na memória, os produtos que estão dentro do arquivo.
   
    VendaAtual *vVendaAtual = NULL; // Commo a pessoa pode entrar na tela mas NÃO escolher nada, melhor não alocar memória e nem deixar o ponteiro locaço, apontando para qualquer coisa
    HistoricoVendas *vVendasDia = NULL;
    SaldosVendas vsaldosVendas = {0};
    

    fMenuPrincipal();
    scanf("%d", &vMenu);

    do
    {
        switch (vMenu)
        {
        case 1: // cadastros
            do
            {
                fMenuCadastros();
                scanf("%d", &vMenu);
                if (vMenu == 3)
                {
                    printf("Retornando ao menu principal\n");
                    fGetcharParaSubstituirPause();
                    break;
                }
                if (vMenu == 1) // produtos
                {
                    printf("Quantos produtos deseja cadastrar?\n");
                    scanf("%d", &vInputUsuario);
                    vAlocacaoMemoriaProdutos += vInputUsuario;
                    produto = (Produtos*) fAlocaMemoria(produto, vAlocacaoMemoriaProdutos, sizeof(Produtos));
                    fCadastraProdutos(vAlocacaoMemoriaProdutos, vInputUsuario, produto, vCaminhoArquivoProduto);
                    printf("Retornando ao menu!\n");
                    fGetcharParaSubstituirPause();
                }
                else if (vMenu == 2) // clientes
                {
                    printf("Quantos clientes deseja cadastrar?\n");
                    scanf("%d", &vInputUsuario);
                    getchar();
                    vAlocacaoMemoriaCliente += vInputUsuario;
                    cliente = fRealocaClientes((vAlocacaoMemoriaCliente), cliente);
                    fCadastraClientes(vAlocacaoMemoriaCliente, vInputUsuario, cliente, vCaminhoArquivoTerceiro);
                    printf("Retornando ao menu\n");
                    fGetcharParaSubstituirPause();
                }
                else if ((vMenu != 1 || vMenu != 2 || vMenu != 3))
                {
                    printf("Opção inválida! selecione uma das opções do menu, entre:\n1 Cadastrar produtos\n2 Cadastrar clientes\n3 Sair\n");
                    scanf("%d", &vMenu);
                }
            } while (vMenu != 3);

            break;
        case 2: // vendas
            if (toupper(vValidaAberturaCaixa) == 'N')
            {
                printf("por gentileza abra o caixa!\n");
                fGetcharParaSubstituirPause();
                break;
            }
            if (toupper(vStatusVenda) == 'E')
            {
                printf("Venda em fechamento! Não é possível adicionar novos itens\n");
                fGetcharParaSubstituirPause();
                break;
            }
            do
            {
                fMenuVendas();
                scanf("%d", &vMenu);
                switch (vMenu)
                {
                case 1: // nova venda
                    do
                    {
                        fExibeProdutosTelaVenda(produto, vAlocacaoMemoriaProdutos);
                        if (vIndiceProduto > 0)
                        {
                            printf("\n");
                            printf("                         NO CARRINHO                  \n");
                            printf("\n");
                            fExibeTotaisVendaAtual(vIndiceProduto, vAlocacaoMemoriaProdutos, vVendaAtual, produto);
                            printf("\n");
                            printf("Total da venda atual: R$ %.2f", vTotalVendaAtual);
                            printf("\n");
                        }

                        printf("Qual produto deseja comprar ou 4 para sair: ");
                        scanf("%d", &vProduto);
                        if (vProduto == 4)
                        {
                            printf("Retornando ao menu principal\n");
                            fGetcharParaSubstituirPause();
                            break;
                        }
                        while (!fValidaProdutoCadastrado(vProduto, vAlocacaoMemoriaProdutos, produto))
                        {
                            printf("Produto não cadastrado, informe um produto válido da lista acima\n");
                            scanf("%d", &vProduto);
                            if (vProduto==4)
                            break;
                        }
                        while (!fBloqueiaVendaEstoqueNegativoZerado(vProduto, vAlocacaoMemoriaProdutos , produto))
                        {
                            printf("Produto com estoque zerado, informe outro produto\n"); 
                            scanf("%d", &vProduto);
                            if (vProduto==4)
                            break;
                        }
                        if (vProduto == 4)
                        {
                            printf("Retornando ao menu principal\n");
                            fGetcharParaSubstituirPause();
                            break;
                        }
                        
                        printf("Qual a quantidade que deseja comprar: ");
                        scanf("%d", &vQuantidade);
                        printf("Deseja continuar comprando? S/N\n");
                        scanf(" %c", &vContinuaCompra);
                        vIndiceProduto += 1;
                        vStatusVenda = 'A';
                        vVendaAtual = fAlocaMemoriaProdutos(vVendaAtual, vIndiceProduto); // Como foi colocada uma quantidade, agora sim aloca memória;
                        fRegistraprodutosVendaAtual(vProduto, vIndiceProduto, vAlocacaoMemoriaProdutos, vVendaAtual, vQuantidade, produto);
                        vTotalVendaAtual = fRetornaTotalVendaAtual(vVendaAtual, vIndiceProduto);
                        fDeduzQtdEstoque(produto, vQuantidade, vProduto, vAlocacaoMemoriaProdutos);

                    } while (toupper(vContinuaCompra) != 'N');
                    break;
                case 2: // SANGRIA
                    if (toupper(vValidaAberturaCaixa) == 'N')
                    {
                        printf("por gentileza abra o caixa!\n");
                        fGetcharParaSubstituirPause();
                        break;
                    }
                    if (vsaldosVendas.saldoDisponivelDinheiro <= 50)
                    {
                        printf("Valor disponível de %.2f não permite retirada, pois é menor que o mínimo!\n", vsaldosVendas.saldoDisponivelDinheiro);
                        break;
                    }

                    printf("Valor disponível para retirada: R$ %.2f\n", vsaldosVendas.saldoDisponivelDinheiro);
                    printf("Qual valor deseja retirar\n");
                    scanf("%f", &vRetiradaCaixa);
                    while ((vsaldosVendas.saldoDisponivelDinheiro - vRetiradaCaixa) < 50)
                    {
                        printf("Valor disponível no fundo de caixa ficará menor que o mínimo de R$ 50.00, não é possível realizar sangria!\n");
                        printf("Informe um valor diferente\n");
                        printf("Valor disponível para retirada: R$ %.2f\n", vsaldosVendas.saldoDisponivelDinheiro);
                        scanf("%f", &vRetiradaCaixa);
                    }
                    vsaldosVendas.vSangriasdias += vRetiradaCaixa;
                    vsaldosVendas.saldoDisponivelDinheiro -= vRetiradaCaixa;
                    break;
                case 3: // PAGAMENTO
                    if (toupper(vValidaAberturaCaixa) == 'N')
                    {
                        printf("por gentileza abra o caixa!\n");
                        fGetcharParaSubstituirPause();
                        break;
                    }
                    if (vStatusVenda == 'F')
                    {
                        printf("Não há uma venda aberta no momento!\n");
                        fGetcharParaSubstituirPause();
                        break;
                    }
                    fExibeTotaisVendaAtual(vIndiceProduto, vAlocacaoMemoriaProdutos, vVendaAtual, produto);
                    fMenuPagamento(vTotalVendaAtual);
                    scanf("%d", &vMenu);
                    printf("Qual valor deseja pagar?\n");
                    scanf("%f", &vValorPagar);
                    switch (vMenu)
                    {
                    case 1:
                        if (vTotalVendaAtual >= 200)
                        {
                            do
                            {
                                printf("Qual a porcentagem de desconto(Precisa ser maior que 10)\n");
                                scanf("%f", &vPercDesconto);
                                vDesconto = fExibeDesconto(vTotalVendaAtual, vPercDesconto);
                            } while (vPercDesconto <= 10);
                        }
                        else
                        {
                            vDesconto = fExibeDesconto(vTotalVendaAtual, 0);
                        }
                        if (vValorPagar > vTotalVendaAtual) // validação do troco
                        {
                            if ((vValorPagar - vTotalVendaAtual) > vsaldosVendas.saldoDisponivelDinheiro)
                            {
                                printf("Saldo de %.2f insuficiente para o troco de %.2f\n", vsaldosVendas.saldoDisponivelDinheiro, (vValorPagar - (vTotalVendaAtual-vDesconto)));
                                fGetcharParaSubstituirPause();
                            }
                            else
                            {
                                printf("Troco de : R$ %.2f\n", (vValorPagar - (vTotalVendaAtual-vDesconto)));
                                fGetcharParaSubstituirPause();
                            }
                        }
                        fProcessaPagamentoDinheiro(&vTotalVendaAtual, &vsaldosVendas, &vDesconto, &vValorPagar);
                        if (vTotalVendaAtual <= 0)
                        {
                            vIndiceVenda += 1;
                            vVendasDia = fAlocaMemoriaVendas(vVendasDia, vIndiceVenda);
                            fGravaVendasDia(vIndiceVenda, vVendasDia, &vsaldosVendas, &vDesconto);
                            free(vVendaAtual);
                            vVendaAtual = NULL;
                            vStatusVenda = 'F';
                            vIndiceProduto = 0;
                            vsaldosVendas.vValorPagoCartaoVendaAtual = 0;
                            vsaldosVendas.vValorPagodinheiroVendaAtual = 0;
                        }
                        break;
                    case 2:
                        while (vValorPagar > vTotalVendaAtual)
                        {
                            printf("Valor maio que o devido para forma de pagamento cartão, informe novamente\n"); 
                            scanf("%f", &vValorPagar);
                        }
                        
                        printf("Cartão foi autorizado?\n");
                        scanf(" %c", &vContinuaCompra);
                        if (toupper(vContinuaCompra) == 'S')
                        {
                            fProcessaPagamentoCartao(&vTotalVendaAtual, &vsaldosVendas, &vValorPagar);
                        }
                        else
                        {
                            printf("Cartão não autorizado, retornando ao menu principal\n");
                            fGetcharParaSubstituirPause();
                            break;
                        }

                        if (vTotalVendaAtual <= 0)
                        {
                            vIndiceVenda += 1;
                            vVendasDia = fAlocaMemoriaVendas(vVendasDia, vIndiceVenda);
                            fGravaVendasDia(vIndiceVenda, vVendasDia, &vsaldosVendas, &vDesconto);
                            free(vVendaAtual);
                            vVendaAtual = NULL;
                            vStatusVenda = 'F';
                            vIndiceProduto = 0;
                            vsaldosVendas.vValorPagoCartaoVendaAtual = 0;
                            vsaldosVendas.vValorPagodinheiroVendaAtual = 0;
                        }
                        break;
                    case 3:
                        printf("Retornando ao menu principal\n");
                        fGetcharParaSubstituirPause();
                        break;
                    default:
                        fMenuPagamento(vTotalVendaAtual);
                        scanf("%d", &vMenu);
                        break;
                    }
                    break;
                case 4:
                    printf("Retornando ao menu principal\n");
                    fGetcharParaSubstituirPause();
                    break;
                default:
                    fMenuVendas();
                    printf("Opção inválida!\n");
                    scanf("%d", &vMenu);
                    break;
                }
            } while (vMenu != 4);
            break;
        case 3: // abertura caixa
            if (toupper(vValidaAberturaCaixa) == 'S')
            {
                printf("Caixa já está aberto!\n");
                fGetcharParaSubstituirPause();
                break;
            }
            else
            {
                printf("Qual o valor da abertura?\n");
                scanf("%f", &vsaldosVendas.vValorAberturaCaixa);
                vsaldosVendas.saldoDisponivelDinheiro = vsaldosVendas.vValorAberturaCaixa;
                vValidaAberturaCaixa = 'S';
            }
            break;
        case 4: // fechamento caixa
            if (toupper(vValidaAberturaCaixa) == 'N')
            {
                printf("por gentileza abra o caixa!\n");
                fGetcharParaSubstituirPause();
                break;
            }
            if (vStatusVenda == 'A')
            {
                printf("Há uma venda em aberto, proceda o fechamnto antes de fechar o caixa\n");
                fGetcharParaSubstituirPause();
                break;
            }
            fFechamentoCaixa(&vsaldosVendas, vIndiceVenda);
            fGetcharParaSubstituirPause();
            vValidaAberturaCaixa = 'N';
            break;
        case 5: // Relatórios
            do
            {
                fMenuRelatorios();
                scanf("%d", &vMenu);

                switch (vMenu)
                {
                case 1: // Relatório de produtos cadastrados
                    fRetornaCadastrosProdutos(produto, vAlocacaoMemoriaProdutos);
                    fGetcharParaSubstituirPause();
                    break;

                case 2: // Relatório de clientes cadastrados
                    fRetornaClientesCadastrados(cliente, vAlocacaoMemoriaCliente);
                    fGetcharParaSubstituirPause();
                    break;

                case 3: // Relatório de vendas do dia
                    fImprimeVendas(vIndiceVenda, vVendasDia);
                    fGetcharParaSubstituirPause();
                    break;

                case 4: // Escolheu sair
                    printf("Retornando ao menu principal\n");
                    fGetcharParaSubstituirPause();
                    break;

                default: // Opção inválida
                    printf("Opção inválida! Selecione uma das opções do menu, entre:\n1 Produtos Cadastrados\n2 Clientes Cadastrados\n3 Vendas Dia\n4 Sair\n");
                    scanf("%d", &vMenu);
                    break;
                }
            } while (vMenu != 4);
            break;
        case 7: // Encerra o programa.
            printf("Obrigado por usar o deadlocks PDV!\n");
            exit(0);
        default:
            fMenuPrincipal();
            printf("Opção inválida!\n");
            scanf("%d", &vMenu);
            break;
        }
        fMenuPrincipal();
        scanf("%d", &vMenu);
    } while (vMenu != 7);
    printf("Obrigado por usar o deadlocks PDV!\n");

    free(cliente);
    cliente = NULL;
    free(produto);
    produto = NULL;
    free(vVendaAtual);
    vVendaAtual = NULL;
}