#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"
#include "./bibliotecas/structsCadastrosProdutos.h"
#include "./bibliotecas/structCadastrosTerceiros.h"
#include "./bibliotecas/calculaTotaisVendas.h"
#include "./bibliotecas/utilidades.h"

int main()
{
    system("chcp 65001"); // Muda a págica de código dos consoles windows para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
    int vMenu;
    int vInputUsuario;
    int vProduto, vQuantidade;
    char vContinuaCompra = 'S';
    char vStatusVenda = 'F';//VERIFICA SE HÁ VENDA UMA VENDA EM ABERTO OU NÃO

    /*Uma forma de manter controle sobre quanto temos alocado e quantos produtos temos "cadastrados", já que essa bosta dessa linguagem
    não permite o rastreio de quantos bytes uma variável tem alocada em memória.*/
    int vAlocacaoMemoriaCliente = 0;
    int vAlocacaoMemoriaVendas = 0;
    int vAlocacaoMemoriaProdutos = 3; // alocando espaço para 3 produtos, porque é o que teremos visível para teste
    int vIndiceVenda = 0;
    int vIndiceProduto =0 ; //seve para adicionarmos mais itens a venda;
    float vTotalVendaAtual = 0;
    char vValidaAberturaCaixa = 'N';
    SaldosVendas vsaldosVendas;


    Terceiros *cliente = (Terceiros *)calloc(vAlocacaoMemoriaCliente, sizeof(Terceiros));
    Produtos *produto = (Produtos *)calloc(vAlocacaoMemoriaProdutos, sizeof(Produtos));
    VendaAtual* vVendaAtual = NULL;//Commo a pessoa pode entrar na tela mas NÃO escolher nada, melhor não alocar memória e nem deixar o ponteiro locaço apontando para qualquer coisa
    HistoricoVendas* vVendasDia = NULL;

    /*Produtos demonstração;*/
    produto[0].codigoProduto = 1000;
    strcpy(produto[0].nomeProduto, "Detergente");
    produto[0].categoria = 1;
    produto[0].custoProduto = 01.20;
    produto[0].margemLucro = 62.50;
    produto[0].qtdEstoque = 0;

    produto[1].codigoProduto = 1001;
    strcpy(produto[1].nomeProduto, "Café");
    produto[1].categoria = 2;
    produto[1].custoProduto = 14.80;
    produto[1].margemLucro = 40.00;
    produto[1].qtdEstoque = 5;

    produto[2].codigoProduto = 1002;
    strcpy(produto[2].nomeProduto, "Pão Francês");
    produto[2].categoria = 3;
    produto[2].custoProduto = 00.80;
    produto[2].margemLucro = 80.00;
    produto[2].qtdEstoque = 10;

    fMenuPrincipal();
    scanf("%d", &vMenu);

    do 
    {
        switch (vMenu)
        {
        case 1://cadastros
            do
            {
                fMenuCadastros();
                scanf("%d", &vMenu);
                if (vMenu == 3){
                    printf("Retornando ao menu principal\n");   
                    system("pause");
                    break;
                }
                if (vMenu ==1)
                {
                    printf("Quantos produtos deseja cadastrar?\n"); 
                    scanf("%d", &vInputUsuario);
                    vAlocacaoMemoriaProdutos += vInputUsuario;
                    produto= fRealocaProdutos((vAlocacaoMemoriaProdutos), produto);
                    fCadastraProdutos(vAlocacaoMemoriaProdutos, vInputUsuario, produto);
                    printf("Retornando ao menu!\n"); 
                    system("pause");
                }
                else if (vMenu==2)
                {
                    printf("Quantos clientes deseja cadastrar?\n");     
                    scanf("%d", &vInputUsuario);
                    vAlocacaoMemoriaCliente += vInputUsuario;
                    cliente = fRealocaClientes((vAlocacaoMemoriaCliente), cliente);
                    fCadastraClientes(vAlocacaoMemoriaCliente, vInputUsuario, cliente);
                    printf("Retornando ao menu\n"); 
                    system("pause");
                }
                else if ((vMenu!=1 || vMenu!= 2 || vMenu!=3))
                {
                    printf("Opção inválida! selecione uma das opções do menu, entre:\n1 Cadastrar produtos\n2 Cadastrar clientes\n3 Sair\n"); 
                    scanf("%d", &vMenu);
                }   
            } while (vMenu != 3);
            
            break;
        case 2://vendas
            if (toupper(vValidaAberturaCaixa) == 'N')
                {
                    printf("por gentileza abra o caixa!\n");
                    system("pause");
                    break;
                }
            do
            {
                fMenuVendas();
                scanf("%d", &vMenu);
                switch (vMenu)
                {
                case 1://nova venda
                    do
                    {
                        fExibeProdutosTelaVenda(produto, vAlocacaoMemoriaProdutos);
                        if (vIndiceProduto>0)
                        {
                            printf("\n"); 
                            printf("                         NO CARRINHO                  \n"); 
                            printf("\n"); 
                            fExibeTotaisVendaAtual(vIndiceProduto, vAlocacaoMemoriaProdutos, vVendaAtual, produto);
                            printf("\n"); 
                            printf("Total da venda atual: R$ %.2f",vTotalVendaAtual); 
                            printf("\n");
                        }
                        
                        printf("Qual produto deseja comprar ou 4 para sair: "); 
                        scanf("%d", &vProduto);
                        if (vProduto==4)
                        {
                            printf("Retornando ao menu principal\n"); 
                            system("pause");
                            break;
                        }
                        while (!fValidaProdutoCadastrado(vProduto, vAlocacaoMemoriaProdutos, produto))
                        {
                            printf("Produto não cadastrado, informe um produto válido da lista acima\n"); 
                            scanf("%d", &vProduto);
                        }
                        printf("Qual a quantidade que deseja comprar: "); 
                        scanf("%d", &vQuantidade);
                        vStatusVenda = 'A';
                        vVendaAtual = fAlocaMemoriaProdutos(vVendaAtual,vIndiceProduto);//Como foi colocada uma quantidade, agora sim aloca memória;
                        fRegistraprodutosVendaAtual(vProduto, vIndiceProduto, vAlocacaoMemoriaProdutos, vVendaAtual, vQuantidade, produto);
                        vTotalVendaAtual=fRetornaTotalVendaAtual(vVendaAtual, vIndiceProduto);
                        printf("Deseja continuar comprando? S/N\n"); 
                        scanf(" %c", &vContinuaCompra);    
                        if (toupper(vContinuaCompra)=='S')
                        {
                            //Se a pessoa escolhe continuar comprando, atualiza o índice do produto para que os produtos, nas chamadas acima, possam ser atualizados corretamente
                            vIndiceProduto+=1;
                        }
                                        
                    } while (toupper(vContinuaCompra)!='N');                  
                    break;
                case 2://SANGRIA
                    if (toupper(vValidaAberturaCaixa) == 'N')
                    {
                        printf("por gentileza abra o caixa!\n");
                        system("pause");
                        break;
                    }
                    if (vsaldosVendas.saldoDisponivelDinheiro <=50)
                    {
                        printf("Valor disponível no fundo de caixa menor que o mínimo, não é possível realizar sangria!\n"); 
                        system("pause");
                        break;
                    }
                    
                    break;
                case 3://PAGAMENTO
                    if (toupper(vValidaAberturaCaixa) == 'N')
                    {
                        printf("por gentileza abra o caixa!\n");
                        system("pause");
                        break;
                    }
                    break;
                case 4:
                    printf("Retornando ao menu principal\n"); 
                    system("pause");
                    break;
                default:
                    fMenuVendas();
                    printf("Opção inválida!\n"); 
                    scanf("%d", &vMenu);
                    break;
                }
            } while (vMenu!=4);            
            break;
        case 3: //abertura caixa
            break;
        case 4: //fechamento caixa
            if (toupper(vValidaAberturaCaixa) == 'N')
                {
                    printf("por gentileza abra o caixa!\n");
                    system("pause");
                    break;
                }
            if (vStatusVenda =='A')
            {
                printf("há uma venda em aberto, proceda o fechamnto antes de fechar o caixa\n"); 
                system("pause");
                break;
            }
            
            break;
        case 5://Relatórios
            do
            {
                fMenuRelatorios();
                scanf("%d", &vMenu);
                if (vMenu==4)//escolheu sair
                {
                    printf("Retornando ao menu principal\n"); 
                    system("pause");
                    break;
                }
                if (vMenu == 1)//relatório de produtos cadastrados
                {
                    fRetornaCadastrosProdutos(produto, vAlocacaoMemoriaProdutos);
                    system("pause");
                }
                else if (vMenu ==2)//relatório de clientes cadastrados
                {
                    fRetornaClientesCadastrados(cliente, vAlocacaoMemoriaCliente);
                    system("pause");
                }
                else if ((vMenu!=1 || vMenu!= 2 || vMenu!=4))
                {
                    printf("Opção inválida! selecione uma das opções do menu, entre:\n1 Produtos Cadastrados\n2 Clientes Cadastrados\n4 Sair\n"); 
                    scanf("%d", &vMenu);
                }    
            } while (vMenu != 4);            
            break;
        case 7://Encerra o programa.
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