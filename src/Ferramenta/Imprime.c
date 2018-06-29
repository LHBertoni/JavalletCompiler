#include <stdio.h>
#include <string.h>

public void imprimeTokens(Token tokens[]){
    int n = sizeof(tokens)/sizeof(tokens[0]);

    printf("TOKEN@LEXEMA@LINHA@COLUNA")
    for(int i = 0; i < n; i++)
    {
        printf("%s@%s@%i@%i", pegaTipoToken(tokens[i].tipo), tokens[i].lexema, tokens[i].linha, tokens[i].coluna);
    }
}

private char pegaTipoToken(typeToken tipo)
{
    switch(tipo)
    {
        Inteiro: return "INTEIRO";
        PontoFlutuante: return "PONTO_FLUTUANTE";
        String: return "STRING";
        Bool: return "BOOL";
        Identificador: return "IDENTIFICADOR";
        PalavraReservada: return "PALAVRA_RESERVADA";
        PontoVirgula: return "PONTO_VIRGULA";
        AbreParenteses: return "ABRE_PARENTESES";
        FechaParenteses: return "FECHA_PARENTESES";
        AbreChaves: return "ABRE_CHAVES";
        FechaChaves: return "FECHA_CHAVES";
        Virgula: return "VIRGULA";
        Atribuicao: return "ATRIBUICAO";
        Operador: return "OPERADOR";
        OperadorRelacional: return "OPERADOR_RELACIONAL";
        Incremento: return "INCREMENTO";
        Erro: return "ERRO";
        default: return "";
    }
}
