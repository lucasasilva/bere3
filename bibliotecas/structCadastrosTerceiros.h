#ifndef structsCadastrosTerceiros_h
#define structsCadastrosTerceiros_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


/*Libera memória para o cadastro de uma ou mais clientes*/
Terceiros* fRealocaClientes (int novoTamanho, Terceiros *clientes){
    Terceiros *retornaRealloc =(Terceiros *) realloc(clientes, novoTamanho*sizeof(Terceiros));
    if (retornaRealloc == NULL)
    {
        printf("Falha ao realocar memoria\n"); 
        system("pause");
        return NULL;
    } else{
        return retornaRealloc;
    }
    
}

#endif