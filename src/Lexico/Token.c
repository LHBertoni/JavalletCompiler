
#include <stdlib.h>

enum typeToken
{
    Inteiro,
    PontoFlutuante,
    String,
    Bool,
    Identificador,
    PalavraReservada,
    PontoVirgula,
    AbreParenteses,
    FechaParenteses,
    AbreChaves,
    FechaChaves,
    Virgula,
    Atribuicao,
    Operador,
    OperadorRelacional,
    Incremento,
    Erro
}

typedef struct Token* Token;

struct Token{
    typeToken tipo;
    int linha, coluna;
    char lexema;
}
