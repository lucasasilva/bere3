#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"
#include "./bibliotecas/calculaTotaisVendas.h"
#include "./bibliotecas/structsCadastros.h"
#include "./bibliotecas/utilidades.h"


int main () {
    system("chcp 65001");//Muda a págica de código dos consoles windows para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
    int vMenu;
    Terceiros *cliente= (Terceiros *) calloc(1, sizeof(Terceiros));
    SaldosVendas *saldosVendas= (SaldosVendas *) calloc(1, sizeof(SaldosVendas));
    Produtos *produto= (Produtos *) calloc(3, sizeof(Produtos));//alocando espaço para 3 produtos, porque é o que teremos visível para teste
    produto[0].codigoProduto = 1000;
    strcpy(produto[0].nomeProduto, "Pão Francês");
    produto[0].categoria = 1;
    produto[0].custoProduto = 0.80;
    produto[0].margemLucro = 80.00;

    fRetornaProdutosCadastros(produto, 3, fREtornaCategoria(produto->categoria));
    fMenuPrincipal();
    scanf("%d", &vMenu);
    switch (vMenu)
    {
    case 1:
        fMenuCadastros();
        break;
    case 2:
        fMenuVendas();
        break;
    
    default:
        break;
    }

    free(cliente);
    free(produto);
    free(saldosVendas);
}