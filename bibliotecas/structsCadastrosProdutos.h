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
} Produtos;


/*libera para preencher um número no cadastro, em vez de digitar
No momento de imprimir na tela, busca o retorno aqui para saber qual é*/
char* fREtornaCategoria(int categoria){
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
        return "Categoria não cadastrada";
        break;
    }
}

/*Libera memória para o cadastro de um ou mais novos Produtos*/
Produtos* fRealocaProdutos (int novoTamanho, Produtos *produto){
    Produtos *retornaRealloc = (Produtos *) realloc(produto, novoTamanho*sizeof(Produtos));
    if (retornaRealloc == NULL)
    {
        printf("Falha ao realocar memoria\n"); 
        system("pause");
        return NULL;
    } else{
        return retornaRealloc;
    }
    
}


/*"cadastra" os produtos no espaço de memória alocada*/
void fCadastraProdutos (int tamanhoAtual, int inputUsuario,Produtos *novoProduto){
    for (int i = (tamanhoAtual-inputUsuario); i <(tamanhoAtual); i++)
    {
        system("cls");
        printf("Informe o código do novo produto\n"); 
        scanf("%d", &novoProduto[i].codigoProduto);
        getchar();
        printf("Informe o nome do produtos\n"); 
        fgets(novoProduto[i].nomeProduto,80,stdin);
        printf("Informe a categoria:\n1. Material de Limpeza\t2. Alimentos e Bebidas\t3. Padaria\n"); 
        scanf("%d", &novoProduto[i].categoria);
        printf("Informe o custo do produto\n"); 
        scanf("%f", &novoProduto[i].custoProduto);
        printf("Informe a margem de lucro\n"); 
        scanf("%f", &novoProduto[i].margemLucro);
        printf("Informe a quantidade em estoque\n");   
        scanf("%d", &novoProduto[i].qtdEstoque);
    }
}

/*Retorna os produtos cadastrados*/
void fRetornaCadastrosProdutos (Produtos *produto, int tamanhoAlocado){    
    system("cls");
    printf("%-8s %-19s %-20s %-10s %-16s %-20s\n","Código", "Nome", "Categoria", "Custo", "Margem de Lucro(%)", "Quantidade em Estoque"); 
    for (int i = 0; i < tamanhoAlocado; i++) {
        if (produto[i].categoria== 1)
        {
            printf("%-7d %-19s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, strtok(produto[i].nomeProduto,"\n"), fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }
        else if (produto[i].categoria==2)
        {
            printf("%-7d %-20s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, strtok(produto[i].nomeProduto,"\n"), fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }
        else if (produto[i].categoria==3)
        {
            printf("%-7d %-21s %-20s %-10.2f %-20.2f %-20d\n",  produto[i].codigoProduto, strtok(produto[i].nomeProduto,"\n"), fREtornaCategoria(produto[i].categoria), produto[i].custoProduto, produto[i].margemLucro, produto[i].qtdEstoque);
        }      
    }
}



#endif