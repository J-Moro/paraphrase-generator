#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "abp.c"
/*
Programa lê um dicionário e imprime pares de palavras
ali na linha 73 a gente vai adicionar as funções de inserir na árvore
para chamar o programa, vai no prompt de comando, navega até essa pasta e digita
parafrasemain dict_1K.txt entrada.txt saida.txt
por enquanto entrada não faz nada e saída escreve um arquivo vazio
dict_1K.txt é o nome do dicionário (no moodle tem outros tamanhos)
*/

// ignora minha função no arquivo main, já já eu coloco em outro :)
char* my_strtok(char* str, char* separa, char* out_separa, char** resto);

int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    FILE * dicionario;
    FILE * entrada;
    FILE * saida;

    char *palavra, linha[1000]; // buffer de linha de 999 bytes
    char *sinonimo;
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    char separa_dict[] = {" \t\n"};
    char separa_achado[20];
    char *resto_linha;
    int tam_separador;
    int n_linhas, n_palavras;

    pNodoA *arvoreABP;
    arvoreABP = NULL;


    if (argc!=4)  //o numero de parametros esperado é 3: nome do programa (argv[0]),
        //nome do arq de dicionario (argv[1]), nome do arq de entrada(argv[2]), nome do arq de saida(argv[3])
    {
        printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_dicionario> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    // else chamada do programa ok

    dicionario = fopen (argv[1], "r"); // abre o dicionario para leitura
    if (dicionario == NULL) //se não conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo %s",argv[1]);
        return 1;
    }
    // else arquivo dicionario OK

    entrada = fopen (argv[2], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
    if (entrada == NULL) //se n�o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo %s",argv[2]);
        fclose(dicionario);
        return 1;
    }
    // else arquivo de entrada OK


    saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.
    if (saida == NULL)  // não conseguiu criar arquivo
    {
        printf ("Erro ao abrir o arquivo %s",argv[3]);
        fclose(entrada);
        fclose(dicionario);
        return 1;
    }

    //percorre todo o dicionario  lendo linha por linha
    while (fgets(linha,1000,dicionario))
    {
        palavra = strtok (linha, separa_dict); //considera espaço, tab ou quebra de linha como separador
        sinonimo = strtok (NULL, separa_dict); // já pega o sinônimo também
        while (palavra != NULL)
        {
            arvoreABP = Inserearvore(arvoreABP, palavra, sinonimo);
            //arvoreABP = Inserearvore(arvoreABP, sinonimo, palavra);
            //printf("%s -- %s\n", strlwr(palavra), strlwr(sinonimo)); //strlwr � a fun��o que converte palavras para min�sculo
            // printf("%s -- %s\n", strlwr(sinonimo), strlwr(palavra));
            palavra = strtok (NULL, separa_dict);
            sinonimo = strtok (NULL, separa_dict);
        }
    }

    n_linhas = 0;
    n_palavras = 0;
    // percorre toda a entrada, lendo linha por linha
    // traduzindo e escrevendo no arquivo de saída
    while (fgets(linha,1000,entrada))
    {
        n_linhas++;
        // imprime possível separador antes da primeira palavra
        tam_separador = strspn(linha, separador);   // tamanho do possível separador inicial
        strncpy(separa_achado, linha, tam_separador);
        separa_achado[tam_separador] = '\0';
        fprintf(saida, "%s", separa_achado);
        resto_linha = linha + tam_separador;


        //palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
        palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        //if (palavra == NULL)
        //{   // caso a linha comece com um separador, este é imprimido e procuramos próxima palavra
         //   fprintf(saida,"%s", separa_achado);
          //  palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        //}
        while (palavra != NULL)
        {
            n_palavras++;
            palavra = strlwr(palavra);
            sinonimo = BuscaArvore(arvoreABP, palavra); // procura a palavra (minúcula)
            if(sinonimo == NULL)
                sinonimo = palavra;
            fprintf(saida,"%s%s", sinonimo, separa_achado); //strlwr � a fun��o que converte palavras para min�sculo
            //printf("%d, %d, %d, %d:%s:%s:\n", l, p, comp - comp_ant, comp, palavra, sinonimo);
            //comp_ant = comp;
            //palavra = strtok (NULL, separador);
            palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        }
    }

    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);

    printf("Comparacoes ABP: %d\n", comp);
    printf("Numero de nodos ABP: %d\n", Nodos(arvoreABP));
    printf("Altura ABP: %d\n", Altura(arvoreABP));
    printf("Numero de linhas: %d\n", n_linhas);
    printf("Numero de palavras: %d\n", n_palavras);

    fclose (dicionario);
    fclose (entrada); //fecha os arquivos
    fclose (saida);
    return 0;

}


char* my_strtok(char* str, char* separa, char* out_separa, char** resto)
{   // retorna token de str, separada por caracteres de separa
    // guarda separadores entre palavras em out_separa
    // utiliza resto para avançar pela string
    // baseado em strtok_r()
    char *end, *start;
    int tam_separador;
    int i;

    if (str == NULL & *resto == NULL) // erro: string inválida
        return NULL;

    if (str != NULL)
        start = str;

    if(str == NULL && *resto != NULL)
        start = *resto;

    //start += strspn(start, separa); // pula separadores iniciais

    end = start + strcspn(start, separa);   // endereço de fim da token
    // é onde vai estar o \0
    tam_separador = strspn(end, separa); // tamanho do separador depois da token

    //for (i = 0; i < tam_separador; i++)
     //   out_separa[i] = end[i];
    strncpy(out_separa, end, tam_separador);
    out_separa[tam_separador] = '\0';
    // guarda o separador

    if(end == start) // não tem mais tokens, só possíveis separadores
        return NULL;

    end[0] = '\0';    // fim da token

    *resto = end + tam_separador;   // começo da próxima token

    return start;   // começo dessa token
}
