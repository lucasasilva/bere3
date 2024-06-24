#ifndef structsCadastrosProdutos_h
#define structsCadastrosProdutos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigoProduto;
    char nomeProduto[80];
    int categoria;
    float custoProduto;
    float margemLucro;
    int qtdEstoque;
    int qtdEstoqueMin;
    char statusItem;
} Produtos;
#include "utilidades.h"

/*libera para preencher um número no cadastro, em vez de digitar "material de limpeza"
No momento de imprimir na tela, busca o retorno aqui para saber qual é*/
char *fREtornaCategoria(int categoria)
{
    switch (categoria)
    {
    case 1:
        return "Material de Limpeza";
        break;
    case 2:
        return "Alimentos & Bebidas";
        break;
    case 3:
        return "Padaria";
        break;
    default:
        return "Não cadastrada";
        break;
    }
}

/*Libera memória para o cadastro de um ou mais novos Produtos, retornando o novo endereço de memória, com tamanho ajustado;*/
Produtos *fRealocaProdutos(int novoTamanho, Produtos *produto)
{
    Produtos *retornaRealloc = (Produtos *)realloc(produto, novoTamanho * sizeof(Produtos));
    if (retornaRealloc == NULL)
    {
        printf("Falha ao realocar memoria\n");
        system("pause");
        return NULL;
    }
    else
    {
        return retornaRealloc;
    }
}
// lê os produtos de um arquivo e os aloca na memória;
// Aceita como argumentos variável(ponteiro), o controlador de produtos alocados e ponteiro para arquivo de produtos;
void fAlocaProdutosLidosArquivo(Produtos *produto,  FILE *fptr)
{
    int vLinhasLidas= 0;
    int vColunasLidas = 0;
    fptr = fopen("./data/Produtos.csv", "r");
    if (fptr == NULL)
    {
        perror("Erro ao abrir o arquivo");
        fGetcharParaSubstituirPause();
    }
    do
    {
        //produto = (Produtos *)fAlocaMemoria(produto, vLinhasLidas + 1, sizeof(Produtos));
        vColunasLidas = fscanf(fptr, "%d, %79[^,],%d, %f, %f, %d,%d,%c",
                               &produto[vLinhasLidas].codigoProduto,
                               produto[vLinhasLidas].nomeProduto,
                               &produto[vLinhasLidas].categoria,
                               &produto[vLinhasLidas].custoProduto,
                               &produto[vLinhasLidas].margemLucro,
                               &produto[vLinhasLidas].qtdEstoque,
                               &produto[vLinhasLidas].qtdEstoqueMin,
                               &produto[vLinhasLidas].statusItem);
        if (vColunasLidas != 8 && !feof(fptr))
        {
            printf("Erro de formatação do arquivo na linha %d - Coluna %d\n", (vLinhasLidas + 1), vColunasLidas);
            free(produto);
            produto = NULL;
            exit(1);
        }
        if (vColunasLidas == 8)
        {
            vLinhasLidas++;
        }
    } while (!feof(fptr));
}

/*"cadastra" os produtos no espaço de memória alocada*/
void fCadastraProdutos(int tamanhoAtual, int inputUsuario, Produtos *novoProduto, FILE *arquivoProduto)
{
    for (int i = (tamanhoAtual - inputUsuario); i < (tamanhoAtual); i++)
    {
        system("clear || cls");
        printf("Informe o código do novo produto\n");
        scanf("%d", &novoProduto[i].codigoProduto);
        getchar();
        printf("Informe o nome do produtos\n");
        fgets(novoProduto[i].nomeProduto, 80, stdin);
        novoProduto[i].nomeProduto[strcspn(novoProduto[i].nomeProduto, "\n")] = '\0';
        printf("Informe a categoria:\n1. Material de Limpeza\t2. Alimentos e Bebidas\t3. Padaria\n");
        scanf("%d", &novoProduto[i].categoria);
        printf("Informe o custo do produto\n");
        scanf("%f", &novoProduto[i].custoProduto);
        printf("Informe a margem de lucro\n");
        scanf("%f", &novoProduto[i].margemLucro);
        printf("Informe a quantidade em estoque\n");
        scanf("%d", &novoProduto[i].qtdEstoque);
        printf("Informe o estoque mínimo do produto\n");
        scanf("%d", &novoProduto[i].qtdEstoqueMin);
        strcpy(&novoProduto[i].statusItem, "S");

        /*Gravação dos produtos no arquivo*/
        arquivoProduto = fopen("./data/Produtos.csv", "a");
        if (arquivoProduto == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return;
        }
        fprintf(arquivoProduto, "%d,%s,%d,%.2f,%.2f,%d,%d,%c\n",
                novoProduto[i].codigoProduto,
                novoProduto[i].nomeProduto,
                novoProduto[i].categoria,
                novoProduto[i].custoProduto,
                novoProduto[i].margemLucro,
                novoProduto[i].qtdEstoque,
                novoProduto[i].qtdEstoqueMin,
                novoProduto[i].statusItem);
        fclose(arquivoProduto);
    }
}

/*Retorna os produtos cadastrados. strtok() serve para que  o enter (\n), que o C captura quando digitamos o nome do produto,
não seja printado junto na exibição, quebrando o leiaute que já não é lá essa coca-cola toda.
tem uma condição para cada categoria para ficar bonitinho na tela apenas*/
void fRetornaCadastrosProdutos(Produtos *produto, int tamanhoAlocado)
{
    system("clear || cls");
    printf("%-8s %-19s %-20s %-10s %-16s %-20s\n",
           "Código", "Nome", "Categoria", "Custo", "Margem de Lucro(%)", "Quantidade em Estoque");
    for (int i = 0; i < tamanhoAlocado; i++)
    {
        if (produto[i].categoria == 1)
        {
            printf("%-7d %-19s %-20s %-10.2f %-20.2f %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   produto[i].custoProduto,
                   produto[i].margemLucro,
                   produto[i].qtdEstoque);
        }
        else if (produto[i].categoria == 2)
        {
            printf("%-7d %-20s %-20s %-10.2f %-20.2f %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   produto[i].custoProduto,
                   produto[i].margemLucro,
                   produto[i].qtdEstoque);
        }
        else if (produto[i].categoria == 3)
        {
            printf("%-7d %-21s %-20s %-10.2f %-20.2f %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   produto[i].custoProduto,
                   produto[i].margemLucro,
                   produto[i].qtdEstoque);
        }
    }
}

void fExibeProdutosTelaVenda(Produtos *produto, int tamanhoAlocado)
{
    system("clear || cls");
    printf("%-8s %-19s %-20s %-10s %-16s\n",
           "Código", "Nome", "Categoria", "Preço Venda", "Quantidade em Estoque");
    for (int i = 0; i < tamanhoAlocado; i++)
    {
        if (produto[i].categoria == 1)
        {
            printf("%-7d %-19s %-20s %-10.2f  %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   (produto[i].custoProduto + (produto[i].custoProduto * (produto[i].margemLucro / 100))),
                   produto[i].qtdEstoque);
        }
        else if (produto[i].categoria == 2)
        {
            printf("%-7d %-20s %-20s %-10.2f %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   (produto[i].custoProduto + (produto[i].custoProduto * (produto[i].margemLucro / 100))),
                   produto[i].qtdEstoque);
        }
        else if (produto[i].categoria == 3)
        {
            printf("%-7d %-21s %-20s %-10.2f %-20d\n",
                   produto[i].codigoProduto,
                   strtok(produto[i].nomeProduto, "\n"),
                   fREtornaCategoria(produto[i].categoria),
                   (produto[i].custoProduto + (produto[i].custoProduto * (produto[i].margemLucro / 100))),
                   produto[i].qtdEstoque);
        }
    }
}

char *fRetornaNomeProduto(int produto, int qtdProdutosCadastrados, Produtos *vListaProdutos)
{

    for (int i = 0; i < qtdProdutosCadastrados; i++)
    {
        if (vListaProdutos[i].codigoProduto == produto)
        {
            return vListaProdutos[i].nomeProduto;
        }
    }
}
/*funções idiotas porque não pode gravar o preço de venda do produto no cadastro*/
float fRetornaPrecoVenda(int produto, int qtdProdutosCadastrados, Produtos *vListaProdutos)
{
    for (int i = 0; i < qtdProdutosCadastrados; i++)
    {
        if (vListaProdutos[i].codigoProduto == produto)
        {
            return (vListaProdutos[i].custoProduto + (vListaProdutos[i].custoProduto * (vListaProdutos[i].margemLucro / 100)));
        }
    }
}

#endif