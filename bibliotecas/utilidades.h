#ifndef utilidades_h
#define utilidades_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*Personalizadas*/
//#include "structCadastrosTerceiros.h"
#include "structsCadastrosProdutos.h"


/*Retorna uma string com o nome do UF do cliente no relatório de clientes
e na exibição em tela, no momento do cadastro, assim padroniza o código da UF
e evita um cliente do "Paraná" e outro do "Parná"*/
char *fRetornaEstadoCliente(int numero)
{
    switch (numero)
    {
    case 1:
        return "Acre";
    case 2:
        return "Alagoas";
    case 3:
        return "Amapá";
    case 4:
        return "Amazonas";
    case 5:
        return "Bahia";
    case 6:
        return "Ceará";
    case 7:
        return "Distrito Federal";
    case 8:
        return "Espírito Santo";
    case 9:
        return "Goiás";
    case 10:
        return "Maranhão";
    case 11:
        return "Mato Grosso";
    case 12:
        return "Mato Grosso do Sul";
    case 13:
        return "Minas Gerais";
    case 14:
        return "Pará";
    case 15:
        return "Paraíba";
    case 16:
        return "Paraná";
    case 17:
        return "Pernambuco";
    case 18:
        return "Piauí";
    case 19:
        return "Rio de Janeiro";
    case 20:
        return "Rio Grande do Norte";
    case 21:
        return "Rio Grande do Sul";
    case 22:
        return "Rondônia";
    case 23:
        return "Roraima";
    case 24:
        return "Santa Catarina";
    case 25:
        return "São Paulo";
    case 26:
        return "Sergipe";
    case 27:
        return "Tocantins";
    default:
        return "Não Cadastrado/Estrangeiro.";
    }
}
/*imprime a lista de estados acima, na tela, no momento do cadastro;*/
void fImprimeEstadosTela()
{
    for (int i = 0; i < 28; i++)
    {
        printf("%d. %-9s\t", i, fRetornaEstadoCliente(i));
        if (i == 8)
        {
            printf("\n");
        }
        if (i == 16)
        {
            printf("\n");
        }
        if (i == 24)
        {
            printf("\n");
        }
    }
    printf("\n");
}

/*Valida se o produto apontado pelo usuário existe na lista de produtos cadastrados
se sim, retona true, se não, bom, retorna false*/
bool fValidaProdutoCadastrado(int produtoInput, int qtdProdutosCadastrados, Produtos *produtosCadastrados)
{
    for (int i = 0; i < qtdProdutosCadastrados; i++)
    {
        if (produtosCadastrados[i].codigoProduto == produtoInput)
        {
            return true;
        }
    }
    return false;
}

/*Substitui system("pause")
1. Não é boa prática;
2. Pode quebrar gravação e ou leitura dos arquivos se isso for chamado
   na tela enquanto um arquivo está aberto, pois "pause" interrompe
   a execução do programa;
3. O comando não é reconhecido no computador do amiguinho que usa linux hehe :) */
void fGetcharParaSubstituirPause()
{
    getchar();
    getchar();
}

void* fAlocaMemoria(void *vPonteiro, int vTotalAlocar, size_t vTamanhoaAlocar)
{   
    if (vTotalAlocar == 1)
    {    
        vPonteiro = calloc(1, vTamanhoaAlocar);
        return vPonteiro;
    }
    else if (vTotalAlocar > 1)
    {
        vPonteiro = realloc(vPonteiro, ((vTotalAlocar)*vTamanhoaAlocar));
        return vPonteiro;
    }
    else
    {
        return NULL;
    }
}

/*Retorna a quantidade de itens dentro do arquivo
para usar este valor e alocar espaço o suficiente para o ponteiro que guardará os produtos*/
int fRetornaQTDItensArquivo( char vCaminhoArquivo[100], char* vTipoArquivoProdTerc)
{
    FILE *fptr = fopen(vCaminhoArquivo, "r");
    int vColunasLidas = 0;
    int vLinhasLidas=0;
    Produtos *produto= NULL;
    if (fptr == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    if (vTipoArquivoProdTerc == "P")
    {
        do
        {
            produto = (Produtos *)fAlocaMemoria(produto, vLinhasLidas + 1, sizeof(Produtos));
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
                return 1;
            }
            if (vColunasLidas == 8)
            {
                vLinhasLidas++;
            }
        } while (!feof(fptr));
    }
    fclose(fptr);
    return vLinhasLidas;
}


void fOrdenaProdutos(Produtos *produtos, int vTotalProdutosCadastrados) {
    int i, j;
    Produtos temp;
    for (i = 0; i < vTotalProdutosCadastrados-1; i++) {
        for (j = 0; j < vTotalProdutosCadastrados-i-1; j++) {
            if (produtos[j].nomeProduto[0] > produtos[j+1].nomeProduto[0]) {
                temp = produtos[j];
                produtos[j] = produtos[j+1];
                produtos[j+1] = temp;
            }
        }
    }
}


#endif
