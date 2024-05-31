#ifndef utilidades_h
#define utilidades_h

#include <stdio.h>
#include <string.h>
/*Retorna uma string com o nome do UF do cliente no relatório*/
char* fRetornaEstadoCliente(int numero) {
    switch (numero) {
        case 1: return "Acre";
        case 2: return "Alagoas";
        case 3: return "Amapá";
        case 4: return "Amazonas";
        case 5: return "Bahia";
        case 6: return "Ceará";
        case 7: return "Distrito Federal";
        case 8: return "Espírito Santo";
        case 9: return "Goiás";
        case 10: return "Maranhão";
        case 11: return "Mato Grosso";
        case 12: return "Mato Grosso do Sul";
        case 13: return "Minas Gerais";
        case 14: return "Pará";
        case 15: return "Paraíba";
        case 16: return "Paraná";
        case 17: return "Pernambuco";
        case 18: return "Piauí";
        case 19: return "Rio de Janeiro";
        case 20: return "Rio Grande do Norte";
        case 21: return "Rio Grande do Sul";
        case 22: return "Rondônia";
        case 23: return "Roraima";
        case 24: return "Santa Catarina";
        case 25: return "São Paulo";
        case 26: return "Sergipe";
        case 27: return "Tocantins";
        default: return "Não Cadastrado/Estrangeiro.";
    }
}
/*imprime a lista de estados acima na tela, no momento do cadastro;*/
void fImprimeEstadosTela (){
    for (int i = 0; i < 28; i++)
    {
        printf("%d. %-9s\t",i,fRetornaEstadoCliente(i)); 
        if (i ==8)
        {
            printf("\n"); 
        }
        if (i ==16)
        {
            printf("\n"); 
        } 
        if (i ==24)
        {
            printf("\n"); 
        }       
    }
    printf("\n"); 
}


#endif
