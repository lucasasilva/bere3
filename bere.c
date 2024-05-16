#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Bibliotecas personalizadas*/
#include "./bibliotecas/menus.h"

int main () {
    system("chcp 65001");//Muda a págica de código dos consoles windows para UTF-8, fazendo com que o nosso idioma seja compreendido com seus acentos;
    fMenuPrincipal();
}