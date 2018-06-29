#include <stdio.h>
#include <string.h>

const char *reservada[11] =
{
    "while",
    "if",
    "else",
    "return",
    "int",
    "bool",
    "double",
    "void",
    "string"
}

public bool ehReservada(char id){
    char str = id;

    for(int j = 0; str[j], j++)
    {
        str[j] = tolower(str[j]);
    }

    for (int i = 0; i < 11; i++)
    {
        if (strcmp(str,reservada[i]) == 0)
            return true;
    }

    return false;
}
