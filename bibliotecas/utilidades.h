#include <stdio.h>
#include <string.h>
char* fREtornaCategoria(int categoria);
/*Retorna o nome da categoria do produto, para fins de impressão no console*/
char* fREtornaCategoria(int categoria){
    switch (categoria)
    {
    case 1:
        return "Material de Limpeza";
        break;
    case 2:
        return "alimento";
        break;
    case 3:
        return "Padaria";
        break;
    default:
        break;
    }
}