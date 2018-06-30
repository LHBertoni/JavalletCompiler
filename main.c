#include <stdio.h>
#include <stdlib.h>
#include <Token.h>

int main()
{
	
    printf("TOKEN@LEXEMA@LINHA@COLUNA");
	
    struct Token tk[1];
    tk[0].coluna = 1;
    tk[0].linha = 1;
    tk[0].tipo = Erro;
    tk[0].lexema = "Teste de Desenvolvimento"

    imprimeTokens(tk);

    return 0;
}
