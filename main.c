#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Token{
    int tipo;
    int linha, coluna;
    char lexema[100];
};


const char* reservada[11] =
{
    "while",
    "if",
    "else",
    "return",
    "int",
    "boo",
    "double",
    "void",
    "string"
};

//  Tipo
//	Novo = 0
//  Inteiro = 1,
//  PontoFlutuante = 2,
//  String = 3,
//  Bool = 4,
//  Identificador = 5,
//  PalavraReservada = 6,
//  PontoVirgula = 7,
//  AbreParenteses = 8,
//  FechaParenteses = 9,
//  AbreChaves = 10,
//  FechaChaves = 11,
//  Virgula = 12,
//  Atribuicao = 13,
//  Operador = 14,
//  OperadorRelacional = 15,
//  Incremento = 16,
//  Erro = 17,


int main()
{
    struct Token tk;
    tk.coluna = 1;
    tk.linha = 1;
    tk.tipo = 1;
    strcpy( tk.lexema, "TESTE");

    printf("TOKEN@LEXEMA@LINHA@COLUNA\n");

    imprimeTokens(tk);

    return 0;
    scanf("Teste");
}

void imprimeTokens(struct Token tk)
{
    switch(tk.tipo)
    {
        case 1:
            printf("INTEIRO");
            break;
        case 2:
            printf("PONTO_FLUTUANTE");
            break;
        case 3:
            printf("STRING");
            break;
        case 4:
            printf("BOOL");
            break;
        case 5:
            printf("IDENTIFICADOR");
            break;
        case 6:
            printf("PALAVRA_RESERVADA");
            break;
        case 7:
            printf("PONTO_VIRGULA");
            break;
        case 8:
            printf("ABRE_PARENTESES");
            break;
        case 9:
            printf("FECHA_PARENTESES");
            break;
        case 10:
            printf("ABRE_CHAVES");
            break;
        case 11:
            printf("FECHA_CHAVES");
            break;
        case 12:
            printf("VIRGULA");
            break;
        case 13:
            printf("ATRIBUICAO");
            break;
        case 14:
            printf("OPERADOR");
            break;
        case 15:
            printf("OPERADOR_RELACIONAL");
            break;
        case 16:
            printf("INCREMENTO");
            break;
        case 17:
            printf("ERRO");
            break;
    }
    printf("@");
    printf("%s", tk.lexema);
    printf("@");
    printf("%i", tk.linha);
    printf("@");
    printf("%i", tk.coluna);
    printf("\n");
}


int ehReservada(char* id)
{
    for (int i = 0; i < 11; i++)
    {
        if (strcmp(id,  reservada[i]) == 0){
            return 1;
        }
    }

    return 0;
}
