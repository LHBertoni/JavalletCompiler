#include <stdio.h>
#include <string.h>


public char* LerArquivo(char *nomeArquivo)
{
   char *buffer = NULL;
   int string_size, read_size;
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
       }

       // Fecha o arquivo
       fclose(handler);
    }

    return buffer;
}
