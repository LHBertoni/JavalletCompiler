#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *buffer = NULL;
int string_size;

struct Token{
    int tipo;
    int linha, coluna;
    char lexema[200];
    int finalizado; // 0 false - 1 true
};

const char* reservada[11] =
{
    "while",
    "if",
    "else",
    "return",
    "int",
    "bool",
    "double",
    "void",
    "string",
    "printInt",
    "return"
};


void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void LerArquivo(char *nomeArquivo)
{
   int read_size;
   FILE *handler = fopen(nomeArquivo, "r");

   if (handler)
   {
       // Pega o último byte do Arquivo
       fseek(handler, 0, SEEK_END);
       // Desloca por todo arquivo, para pegar o Tamanho do arquivo
       string_size = ftell(handler);
       // Volta para o início do arquivo
       rewind(handler);

       // Aloca uma string que possa conter todo o arquivo
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Le todo o arquivo de uma vez
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // Gambs para que o buffer seja oficialmente uma string
       // Colocamos o \0 para finalizar a string por o fread não adiciona
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

int main(int argc, char *argv[])
{
    struct Token tk;
    int colArq = 0;
    int linArq = 1;


    LerArquivo(argv[1]);

    printf("TOKEN@LEXEMA@LINHA@COLUNA\n");

    tk.tipo = 0;
    tk.linha = linArq;
    tk.coluna = 1;
    strcpy(tk.lexema, "");

    for(int i = 0; i <= string_size; i++)
    {
        colArq++;

        char c = buffer[i];

        if(tk.finalizado == 1){

           if(tk.tipo == 5)
            {
                int reservada = ehReservada(tk.lexema);
                int itrue = strcmp(tk.lexema, "true");
                int ifalse = strcmp(tk.lexema, "false");

                if(reservada == 1)
                {
                    tk.tipo = 6;
                }
                else if(itrue == 0 || ifalse == 0)
                {
                    tk.tipo = 4;
                }
            }

            if(tk.tipo != 0 && tk.tipo != 18 && tk.tipo != 19)
            {
                imprimeToken(tk);
            }

            tk.linha = linArq;
            tk.coluna = colArq;
            tk.tipo = 0;
            tk.finalizado = 0;
            strcpy(tk.lexema, "");
        }

        if(c == '\n') // 10 em ascii é o \n
        {
            if(tk.tipo != 19){
                tk.finalizado = 1;
            }

            linArq++;
            colArq = 0; // 0 por que na proxima será setado 1

            if(tk.tipo == 3)
            {
                tk.tipo = 17;
            }
        }

        if(tk.tipo == 19)
        {
            int tam = strlen(tk.lexema);

            if(tk.lexema[tam - 1] == '*' && c == '/')
            {
                tk.finalizado = 1;
            }

            append(tk.lexema, c);
        }
        else if(tk.tipo == 18)
        {
            continue;
        }
        else if(c == '"') // "
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 3;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 3) // Se é string
            {
                tk.finalizado = 1;
            }
            else
            {
                tk.finalizado = 1;
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }
        }
        else if(tk.tipo == 3) // se for string
        {
            int tam = strlen(tk.lexema);

            if(tam == 200)
            {
                tk.tipo = 17;
                tk.finalizado = 0;

                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }
            else
            {
                append(tk.lexema, c);
            }
        }
        else if(c == '\0' || c == ' ' || c == '\t' || c == '\f') // Se for o ultimo char da string ou espaço
        {
            tk.finalizado = 1;
        }
        else if(c == ';') // (
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 7;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == '(')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 8;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == ')')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 9;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == '{')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 10;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == '}')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 11;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == ',')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 12;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == '=')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 13;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 13 || tk.tipo == 15 || tk.tipo == 17)
            {
                if(strlen(tk.lexema) == 1 && (tk.lexema[0] == '=' || tk.lexema[0] == '>' || tk.lexema[0] == '<' || tk.lexema[0] == '!'))
                {
                    tk.tipo = 15;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }
                }

                tk.finalizado = 1;
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '>')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 15;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '<')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 15;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '+')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 14;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 14)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '+')
                {
                    tk.tipo = 16;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }
                }

                tk.finalizado = 1;
            }
            else if(tk.tipo == 2)
            {
                int tam = strlen(tk.lexema);

                if(tk.lexema[tam - 1] == 'e' || tk.lexema[tam - 1] == 'E')
                {
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }

                    tk.finalizado = 1;
                }
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }
                tk.finalizado = 1;
            }
        }
        else if(c == '-')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 14;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 14)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '-')
                {
                    tk.tipo = 16;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }
                }

                tk.finalizado = 1;
            }
            else if(tk.tipo == 2)
            {
                int tam = strlen(tk.lexema);

                if(tk.lexema[tam - 1] == 'e' || tk.lexema[tam - 1] == 'E')
                {
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }

                    tk.finalizado = 1;
                }
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '*')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 14;
                append(tk.lexema, c);

                tk.finalizado = 1;
            }
            else if(tk.tipo == 14)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '/')
                {
                    tk.tipo = 19;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }

                    tk.finalizado = 1;
                }
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '/')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 14;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 14)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '/')
                {
                    tk.tipo = 18;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }

                    tk.finalizado = 1;
                }
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '%')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 14;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
        else if(c == '&')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 17)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '&')
                {
                    tk.tipo = 14;
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }
                }

                tk.finalizado = 1;
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }
                tk.finalizado = 1;
            }
        }
        else if(c == '|')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 17)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '|')
                {
                    tk.tipo = 14;
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }
                }

                tk.finalizado = 1;
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i + 1] == 10){
                    linArq --;
                }
                tk.finalizado = 1;
            }
        }
        else if(c == '.')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 1)
            {
                tk.tipo = 2;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '_')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
                tk.finalizado = 1;
            }
            else if(tk.tipo == 5)
            {
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c == '!')
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
                tk.finalizado = 1;
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(isdigit(c))
        {
            if(tk.tipo == 0)
            {
                tk.tipo = 1;
                tk.coluna = colArq;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 1 || tk.tipo == 2 || tk.tipo == 5)
            {
                append(tk.lexema, c);
            }
            else if(tk.tipo == 17)
            {
                if(strlen(tk.lexema) == 1 && tk.lexema[0] == '.')
                {
                    tk.tipo = 2;
                    append(tk.lexema, c);
                }
                else
                {
                    colArq--;
                    i--;

                    if(buffer[i] == '\n'){
                        linArq --;
                    }

                    tk.finalizado = 1;
                }
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(isalpha(c))
        {
            if(tk.tipo == 0)
            {
                tk.tipo = 5;
                tk.coluna = colArq;
                append(tk.lexema, c);
            }
            else if(tk.tipo == 5)
            {
                append(tk.lexema, c);
            }
            else if(tk.tipo == 2 && (c == 'e' || c == 'E'))
            {
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }

                tk.finalizado = 1;
            }
        }
        else if(c != 10)
        {
            if(tk.tipo == 0) // Se é novo
            {
                tk.coluna = colArq;
                tk.tipo = 17;
                append(tk.lexema, c);
            }
            else
            {
                colArq--;
                i--;

                if(buffer[i] == '\n'){
                    linArq --;
                }
            }

            tk.finalizado = 1;
        }
    }

    if((tk.finalizado = 1) && tk.tipo != 0 && tk.tipo != 18 && tk.tipo != 19)
    {
        imprimeToken(tk);
    }

    buffer = NULL;
    string_size = 0;

    scanf("Teste");
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
//  ComentarioLinha = 18,
//  ComentarioDeLinhas = 19,
