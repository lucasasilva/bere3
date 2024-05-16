#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"

typedef struct 
{
    int codigoProduto;
    char nomeProduto[80];
    int categoria;
    float custoProduto;
    float margemLucro;
} Produtos;

typedef struct 
{
    char rua[100];
    int  ruaNumero;
    char bairro[50];
} Endereco;

typedef struct 
{
   int codigo;
   char nomeRegistro[150];
   char nomeSocial[150];
   char cpf[14];
   Endereco Endereco;
} Terceiros;

typedef struct 
{
    float totalVendaAtual;
    float totalVendaDinheiro;
    float totalVendaCartao;
    float totalVendidoDia;
} Vendas;



int main () {
    int vMenu;
    system("chcp 65001");//Muda a págica de código dos consoles windows para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
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
}