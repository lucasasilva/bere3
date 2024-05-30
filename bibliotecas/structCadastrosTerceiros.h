#ifndef structsCadastrosTerceiros_h
#define structsCadastrosTerceiros_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Personalizadas*/
#include "utilidades.h"

typedef struct 
{
    int UFCliente;
    char CEP_ZIPCODE[20];
    char cidade[50];
    char bairro[50];
    char rua[100];
    int  ruaNumero;
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

void fCadastraClientes (int tamanhoAtual, int inputUsuario, Terceiros *cliente){
    char clientePossuiNomeSocial;
    for (int i = (tamanhoAtual-inputUsuario); i < tamanhoAtual; i++)
    {
        system("cls");
        printf("Entre com o código do novo cliente\n"); 
        scanf("%d", &cliente[i].codigo);
        printf("Entre com o nome de registro/batismo do novo cliente\n"); 
        fgets(cliente[i].nomeRegistro, 150, stdin);
        printf("Cliente possui nome social?\n"); 
        scanf(" %c", &clientePossuiNomeSocial);
        if (toupper(clientePossuiNomeSocial =='S'))
        {
            printf("Entre com o nome social do cliente \n"); 
            fgets(cliente[i].nomeSocial, 150, stdin);
        }else
        {
            strcpy(cliente[i].nomeSocial, cliente[i].nomeRegistro);
        }
        printf("Entre com o CPF do cliente (somente Numeros):\n"); 
        fgets(cliente[i].cpf, 14, stdin);
        printf("Entre com a UF do Cliente\n"); 
        fImprimeEstadosTela();
        scanf("%d", cliente[i].Endereco.UFCliente); 
        printf("Entre com o CEP e ou ZIP Code do cliente\n"); 
        fgets(cliente[i].Endereco.CEP_ZIPCODE, 20, stdin);
        printf("Entre com cidade do cliente\n"); 
        fgets(cliente[i].Endereco.cidade, 50, stdin);
        printf("Entre com o bairro do cliente\n"); 
        fgets(cliente[i].Endereco.bairro, 50, stdin);
        printf("Entre com a rua do cliente\n"); 
        fgets(cliente[i].Endereco.rua, 100, stdin);
        printf("Entre com o número da casa\n"); 
        scanf("%d", &cliente[i].Endereco.ruaNumero);
    }
}

void fRetornaClientesCadastrados(){
    
}


#endif