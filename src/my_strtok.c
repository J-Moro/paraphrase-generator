#include <string.h>

char* my_strtok(char* str, char* separa, char* out_separa, char** resto)
{   // tokenizador customizado baseado em strtok_r()
    // str: string a ser tokenizada
    // separa: string que cont�m caracteres separadores
    // out_separa: string onde ser�o guardados os separadores encontrados
    // resto: endere�o de string que indica onde come�a a pr�xima token
    char *end, *start;
    int tam_separador;
    int i;

    if (str == NULL & *resto == NULL) // erro: string inv�lida
        return NULL;

    if (str != NULL)    // str cont�m in�cio da string
        start = str;

    if(str == NULL && *resto != NULL)   // *resto cont�m �nicio da pr�xima token
        start = *resto;

    start += strspn(start, separa); // pula poss�veis separadores iniciais

    end = start + strcspn(start, separa);   // endere�o de fim da token, onde vai estar o \0

    tam_separador = strspn(end, separa); // tamanho do separador depois da token

    strncpy(out_separa, end, tam_separador);    // guarda o separador
    out_separa[tam_separador] = '\0';

    if (end == start) // n�o tem mais tokens, s� poss�veis separadores
        return NULL;

    end[0] = '\0';    // fim da token

    *resto = end + tam_separador;   // come�o da pr�xima token

    return start;   // come�o dessa token, agora terminada em \0
}
