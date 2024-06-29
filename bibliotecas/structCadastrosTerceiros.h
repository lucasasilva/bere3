#ifndef structsCadastrosTerceiros_h
#define structsCadastrosTerceiros_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Personalizadas*/


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

#include "utilidades.h"

void fOrdenaClientes(Terceiros *cliente, int n) {
    int i, j;
    Terceiros temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (cliente[j].nomeRegistro[0] > cliente[j+1].nomeRegistro[0]) {
                temp = cliente[j];
                cliente[j] = cliente[j+1];
                cliente[j+1] = temp;
            } 
        }
    }
}


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
/*Leitura dos cadastros no arquivo*/
void fAlocaTerceirosLidosArquivo(Terceiros *cliente, char* vCaminhoArquivoCliente)
{
    FILE *fptr = fopen(vCaminhoArquivoCliente, "r");
    int vLinhasLidas = 0;
    int vColunasLidas = 0;
    if (fptr == NULL)
    {
        perror("Erro ao abrir o arquivo");
        fGetcharParaSubstituirPause();
    }
    do 
    {
        //produto = (Produtos *)fAlocaMemoria(produto, vLinhasLidas + 1, sizeof(Produtos));
        vColunasLidas = fscanf(fptr, "%d,%149[^,],%149[^,],%13[^,],%d,%19[^,],%49[^,],%49[^,],%99[^,],%19[^\n]\n",
                  &cliente[vLinhasLidas].codigo,
                  cliente[vLinhasLidas].nomeRegistro,
                  cliente[vLinhasLidas].nomeSocial,
                  cliente[vLinhasLidas].cpf,
                  &cliente[vLinhasLidas].Endereco.UFCliente,
                  cliente[vLinhasLidas].Endereco.CEP_ZIPCODE,
                  cliente[vLinhasLidas].Endereco.cidade,
                  cliente[vLinhasLidas].Endereco.bairro,
                  cliente[vLinhasLidas].Endereco.rua,
                  cliente[vLinhasLidas].Endereco.ruaNumero) == 10;
        if (vColunasLidas != 10 && !feof(fptr))
        {
            printf("Erro de formatação do arquivo na linha %d - Coluna %d\n", (vLinhasLidas + 1), vColunasLidas);
            free(cliente);
            cliente = NULL;
            exit(1);
        }
        if (vColunasLidas == 10)
        {
            vLinhasLidas++;
        }
    } while (!feof(fptr));
    fOrdenaClientes(cliente,vLinhasLidas);
}


/*função para cadastro de clientes, auto explicativa*/                          
void fCadastraClientes (int tamanhoAtual, int inputUsuario, Terceiros *cliente, char *vCaminhoArquivoTerc){
    char clientePossuiNomeSocial;
    char temporaria[150];//armazena tudo o que for integer para posterior conversão; para eviter de por getchar() em todo canto;
    for (int i = (tamanhoAtual-inputUsuario); i < tamanhoAtual; i++)
    {
        system("clear || cls");
        printf("Entre com o código do novo cliente\n");
        fgets(temporaria, 150, stdin);
        sscanf(temporaria, "%d", &cliente[i].codigo); // Converte o código do cliente de char para integer

        printf("Entre com o nome de registro/batismo do novo cliente\n");
        fgets(cliente[i].nomeRegistro, 150, stdin);
        cliente[i].nomeRegistro[strcspn(cliente[i].nomeRegistro, "\n")] = '\0';

        printf("Cliente possui nome social? (S/N)\n");
        scanf(" %c", &clientePossuiNomeSocial);
        getchar();
        if (toupper(clientePossuiNomeSocial) == 'S')
        {
            printf("Entre com o nome social do cliente \n");
            fgets(cliente[i].nomeSocial, 150, stdin);
            cliente[i].nomeSocial[strcspn(cliente[i].nomeSocial, "\n")] = '\0';
        }
        else
        {
            strcpy(cliente[i].nomeSocial, "Não Possui");
        }

        printf("Entre com o CPF do cliente (somente Numeros):\n");
        fgets(cliente[i].cpf, 14, stdin);
        cliente[i].cpf[strcspn(cliente[i].cpf, "\n")] = '\0';

        printf("Entre com a UF do Cliente\n");
        fImprimeEstadosTela();
        fgets(temporaria, sizeof(temporaria), stdin);
        sscanf(temporaria, "%d", &cliente[i].Endereco.UFCliente);

        printf("Entre com o CEP e ou ZIP Code do cliente\n");
        fgets(cliente[i].Endereco.CEP_ZIPCODE, 20, stdin);
        cliente[i].Endereco.CEP_ZIPCODE[strcspn(cliente[i].Endereco.CEP_ZIPCODE, "\n")] = '\0';

        printf("Entre com cidade do cliente\n");
        fgets(cliente[i].Endereco.cidade, 50, stdin);
        cliente[i].Endereco.cidade[strcspn(cliente[i].Endereco.cidade, "\n")] = '\0';

        printf("Entre com o bairro do cliente\n");
        fgets(cliente[i].Endereco.bairro, 50, stdin);
        cliente[i].Endereco.bairro[strcspn(cliente[i].Endereco.bairro, "\n")] = '\0';

        printf("Entre com a rua do cliente\n");
        fgets(cliente[i].Endereco.rua, 100, stdin);
        cliente[i].Endereco.rua[strcspn(cliente[i].Endereco.rua, "\n")] = '\0';

        printf("Entre com o número da casa\n");
        fgets(cliente[i].Endereco.ruaNumero, 20, stdin);
        cliente[i].Endereco.ruaNumero[strcspn(cliente[i].Endereco.ruaNumero, "\n")] = '\0';

        FILE *fptr = fopen(vCaminhoArquivoTerc, "a");
        if (fptr == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita\n");
            free(cliente);
            exit(1);
        }

        fprintf(fptr, "%d,%s,%s,%s,%d,%s,%s,%s,%s,%s\n",
                cliente[i].codigo,
                cliente[i].nomeRegistro,
                cliente[i].nomeSocial,
                cliente[i].cpf,
                cliente[i].Endereco.UFCliente,
                cliente[i].Endereco.CEP_ZIPCODE,
                cliente[i].Endereco.cidade,
                cliente[i].Endereco.bairro,
                cliente[i].Endereco.rua,
                cliente[i].Endereco.ruaNumero);

        fclose(fptr);
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


int fRetornaQTDTercArquivo( char vCaminhoArquivo[100], char* vTipoArquivoProdTerc)
{
    FILE *fptr = fopen(vCaminhoArquivo, "r");
    int vColunasLidas = 0;
    int vLinhasLidas=0;
    Terceiros *cliente = NULL;
    if (fptr == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    if (vTipoArquivoProdTerc == "T")
    {
        do
        {
            printf("chegou aqui dentro\n"); 
            cliente = (Terceiros *)fAlocaMemoria(cliente, vLinhasLidas + 1, sizeof(Terceiros));
            vColunasLidas =  fscanf(fptr, "%d,%149[^,],%149[^,],%13[^,],%d,%19[^,],%49[^,],%49[^,],%99[^,],%19[^,\n]",
                  &cliente[vLinhasLidas].codigo,
                  cliente[vLinhasLidas].nomeRegistro,
                  cliente[vLinhasLidas].nomeSocial,
                  cliente[vLinhasLidas].cpf,
                  &cliente[vLinhasLidas].Endereco.UFCliente,
                  cliente[vLinhasLidas].Endereco.CEP_ZIPCODE,
                  cliente[vLinhasLidas].Endereco.cidade,
                  cliente[vLinhasLidas].Endereco.bairro,
                  cliente[vLinhasLidas].Endereco.rua,
                  cliente[vLinhasLidas].Endereco.ruaNumero);
            if (vColunasLidas != 10 && !feof(fptr))
            {
                printf("Erro de formatação do arquivo na linha %d - Coluna %d\n", (vLinhasLidas + 1), vColunasLidas);
                free(cliente);
                cliente = NULL;
                return 1;
            }
            if (vColunasLidas == 10)
            {
                vLinhasLidas++;
            }
        } while (!feof(fptr));   
    }
    fclose(fptr);
    return vLinhasLidas;
}

#endif