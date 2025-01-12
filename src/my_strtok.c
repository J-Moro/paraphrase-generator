#include <string.h>

char* my_strtok(char* str, char* separa, char* out_separa, char** resto)
{   // tokenizador customizado baseado em strtok_r()
    // str: string a ser tokenizada
    // separa: string que contém caracteres separadores
    // out_separa: string onde serão guardados os separadores encontrados
    // resto: endereço de string que indica onde começa a próxima token
    char *end, *start;
    int tam_separador;
    int i;

    if (str == NULL & *resto == NULL) // erro: string inválida
        return NULL;

    if (str != NULL)    // str contém início da string
        start = str;

    if(str == NULL && *resto != NULL)   // *resto contém ínicio da próxima token
        start = *resto;

    start += strspn(start, separa); // pula possíveis separadores iniciais

    end = start + strcspn(start, separa);   // endereço de fim da token, onde vai estar o \0

    tam_separador = strspn(end, separa); // tamanho do separador depois da token

    strncpy(out_separa, end, tam_separador);    // guarda o separador
    out_separa[tam_separador] = '\0';

    if (end == start) // não tem mais tokens, só possíveis separadores
        return NULL;

    end[0] = '\0';    // fim da token

    *resto = end + tam_separador;   // começo da próxima token

    return start;   // começo dessa token, agora terminada em \0
}
