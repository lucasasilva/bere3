#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"
#include "./bibliotecas/calculaTotaisVendas.h"
#include "./bibliotecas/structsCadastros.h"
#include "./bibliotecas/utilidades.h"

int main()
{
    system("chcp 65001"); // Muda a págica de código dos consoles windows para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
    int vMenu;
    int vInputUsuario;
    int vAlocacaoMemoriaCliente = 1;
    int vAlocacaoMemoriaVendas = 1;
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
        case 1://cadastro de produtos
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
                    fRetornaCadastrosProdutos(produto, vAlocacaoMemoriaProdutos);
                    system("pause");

                }
                
            } while (vMenu != 1 || vMenu != 2 || vMenu != 3);
            
            break;
        case 2:
            fMenuVendas();
            break;

        case 5:
            fRetornaCadastrosProdutos(produto, vAlocacaoMemoriaProdutos);
            system("pause");
            break;
        default:
            fMenuPrincipal();
            scanf("%d", &vMenu);
            break;
        }
        fMenuPrincipal();
        scanf("%d", &vMenu);
    } while (vMenu != 7);

    free(cliente);
    free(produto);
    free(saldosVendas);
}
