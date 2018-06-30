#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buffer = NULL;
int string_size;

struct Token{
    int tipo;
    int linha, coluna;
    char lexema[100];
    int finalizado; // 0 false - 1 true
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

int main()
{
    struct Token tk;
    int colArq = 1;
    int linArq = 1;

    printf("TOKEN@LEXEMA@LINHA@COLUNA\n");

    LerArquivo("D:\UFABC\COMPILADORES\JavaletteCompiler\casos_teste\teste1.jl");

    for(int i = 0; i <= string_size; i++)
    {
        colArq++;

        if(buffer[i] == 10){
            tk.finalizado = 1;
            linArq++;
            colArq = 1;
        }

        if(tk.finalizado == 1){
            imprimeToken(tk);
            tk.linha = linArq;
            tk.coluna = colArq;
            tk.tipo = 0;
            strcmp(tk.lexema, "");
        }
    }

    return 0;
}

void LerArquivo(char *nomeArquivo)
{
   int read_size;
   FILE *handler = fopen(nomeArquivo, "r");

   if (handler)
   {
       // Pega o �ltimo byte do Arquivo
       fseek(handler, 0, SEEK_END);
       // Desloca por todo arquivo, para pegar o Tamanho do arquivo
       string_size = ftell(handler);
       // Volta para o in�cio do arquivo
       rewind(handler);

       // Aloca uma string que possa conter todo o arquivo
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Le todo o arquivo de uma vez
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // Gambs para que o buffer seja oficialmente uma string
       // Colocamos o \0 para finalizar a string por o fread n�o adiciona
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Se der merda, setamos o buffer para null e jogamos fora a memoria
           free(buffer);
           buffer = NULL;
           string_size = 0;
       }

       // Fecha o arquivo
       fclose(handler);
    }
}

void imprimeToken(struct Token tk)
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
