#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"

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