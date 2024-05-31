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
    int vMenu, vMenuRel;
    int vInputUsuario;
    /*Uma forma de manter controle sobre quanto temos alocado e quantos produtos temos "cadastrados", já que essa bosta dessa linguagem
    não permite o rastreio de quantos bytes uma variável tem alocada em memória.*/
    int vAlocacaoMemoriaCliente = 0;
    int vAlocacaoMemoriaVendas = 0;
    int vAlocacaoMemoriaProdutos = 3; // alocando espaço para 3 produtos, porque é o que teremos visível para teste

    Terceiros *cliente = (Terceiros *)calloc(vAlocacaoMemoriaCliente, sizeof(Terceiros));
    SaldosVendas *saldosVendas = (SaldosVendas *)calloc(vAlocacaoMemoriaVendas, sizeof(SaldosVendas));
    Produtos *produto = (Produtos *)calloc(vAlocacaoMemoriaProdutos, sizeof(Produtos));

    /*Produtos demonstração;*/
    produto[0].codigoProduto = 1000;
    strcpy(produto[0].nomeProduto, "Detergente");
    produto[0].categoria = 1;
    produto[0].custoProduto = 01.20;
    produto[0].margemLucro = 62.50;
    produto[0].qtdEstoque = 2;

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
            fMenuVendas();
            break;
        case 3: //abertura caixa
            break;
        case 4: //fechamento caixa
            break;
        case 5://Relatórios
            do
            {
                fMenuRelatorios();
                scanf("%d", &vMenu);
                if (vMenu==4)
                {
                    printf("Retornando ao menu principal\n"); 
                    system("pause");
                    break;
                }
                if (vMenu == 1)
                {
                    fRetornaCadastrosProdutos(produto, vAlocacaoMemoriaProdutos);
                    system("pause");
                }
                else if (vMenu ==2)
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
            scanf("%d", &vMenu);
            break;
        }
            fMenuPrincipal();
            scanf("%d", &vMenu);
    } while (vMenu != 7);

    free(cliente);
    cliente = NULL;
    free(produto);
    produto = NULL;
    free(saldosVendas);
    saldosVendas = NULL;
}