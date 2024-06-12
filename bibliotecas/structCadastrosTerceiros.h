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
    char  ruaNumero[20];
} Endereco;

typedef struct 
{
   int codigo;
   char nomeRegistro[150];
   char nomeSocial[150];
   char cpf[14];
   Endereco Endereco;
} Terceiros;


/*Libera memória para o cadastro de uma ou mais clientes, retornando o novo endereço de memória, com tamanho ajustado;*/
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
/*função para cadastro de clientes, auto explicativa*/
void fCadastraClientes (int tamanhoAtual, int inputUsuario, Terceiros *cliente){
    char clientePossuiNomeSocial;
    char temporaria[150];//armazena tudo o que for integer para posterior conversão; para eviter de por getchar() em todo canto;
    for (int i = (tamanhoAtual-inputUsuario); i < tamanhoAtual; i++)
    {
        system("cls");
        getchar();
        printf("Entre com o código do novo cliente\n"); 
        fgets(temporaria, 150, stdin);
        sscanf(temporaria, "%d", &cliente[i].codigo); //converte o código do cliente de char para integer

        printf("Entre com o nome de registro/batismo do novo cliente\n"); 
        fgets(cliente[i].nomeRegistro, 150, stdin);

        printf("Cliente possui nome social?\n"); 
        scanf(" %c", &clientePossuiNomeSocial);
        getchar();
        if (toupper(clientePossuiNomeSocial) =='S')
        {
            printf("Entre com o nome social do cliente \n"); 
            fgets(cliente[i].nomeSocial, 150, stdin);
        }else 
        {
            /*strcpy() copia a string usada no segundo argumetno, para o primeiro
            como estamos usando ponteiro, não dá para fazer cliente[i].nome = "texto", porque um ponteiro não é uma variável
            em vez disso, dizemos que a posição na memória para onde cliente[i].nomeSocial está apontando vai receber "texto"*/
            strcpy(cliente[i].nomeSocial, "Não Possui");
        }

        printf("Entre com o CPF do cliente (somente Numeros):\n"); 
        fgets(cliente[i].cpf, 14, stdin);

        printf("Entre com a UF do Cliente\n"); 
        fImprimeEstadosTela();
        fgets(temporaria, sizeof(temporaria), stdin);
        sscanf(temporaria,"%d", &cliente[i].Endereco.UFCliente);

        printf("Entre com o CEP e ou ZIP Code do cliente\n"); 
        fgets(cliente[i].Endereco.CEP_ZIPCODE, 20, stdin);

        printf("Entre com cidade do cliente\n"); 
        fgets(cliente[i].Endereco.cidade, 50, stdin);

        printf("Entre com o bairro do cliente\n"); 
        fgets(cliente[i].Endereco.bairro, 50, stdin);

        printf("Entre com a rua do cliente\n"); 
        fgets(cliente[i].Endereco.rua, 100, stdin);

        printf("Entre com o número da casa\n"); 
        fgets(cliente[i].Endereco.ruaNumero, 20, stdin);
    }
}

/*Para o relatório de clientes cadastrados. strtok() serve para que o enter (\n) que o C captura quando digitamos o nome do cliente, cidade, enfim,
todo tipo de string, não seja printado junto na exibição, quebrando o leiaute que já não é lá essa coca-cola toda*/
void fRetornaClientesCadastrados(Terceiros* cliente, int tamanhoAlocado) {
    system("cls");
    printf("%-15s %-20s %-20s %-15s %-10s %-10s %-15s %-15s %-20s %-10s\n", 
           "Cod. Cliente", "Nome Registro", "Nome Social", "CPF", "Estado(UF)", 
           "CEP", "Cidade", "Bairro", "Rua", "Numero");

    for (int i = 0; i < tamanhoAlocado; i++) {

        char* nomeRegistro = strtok(cliente[i].nomeRegistro, "\n");
        char* nomeSocial = strtok(cliente[i].nomeSocial, "\n");
        char* cpf = strtok(cliente[i].cpf, "\n");
        char* cep = strtok(cliente[i].Endereco.CEP_ZIPCODE, "\n");
        char* cidade = strtok(cliente[i].Endereco.cidade, "\n");
        char* bairro = strtok(cliente[i].Endereco.bairro, "\n");
        char* rua = strtok(cliente[i].Endereco.rua, "\n");
        /*Basicametne, se houve um erro no preenchimento, memória desalocada ou qualquer outra coisa que
        faça com que a variável criada acim a(que recebe a versão sem o \n) esteja como NULL, ele imprime uma 
        string vazia*/
        printf("%-15d %-20s %-20s %-15s %-10s %-10s %-15s %-15s %-20s %-10s\n", 
               cliente[i].codigo, 
               nomeRegistro ? nomeRegistro : "", 
               nomeSocial ? nomeSocial : "", 
               cpf ? cpf : "", 
               fRetornaEstadoCliente(cliente[i].Endereco.UFCliente), 
               cep ? cep : "", 
               cidade ? cidade : "", 
               bairro ? bairro : "", 
               rua ? rua : "", 
               cliente[i].Endereco.ruaNumero);
    }
}


#endif