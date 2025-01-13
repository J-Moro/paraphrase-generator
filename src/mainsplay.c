#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "splay.c"
#include "abp.c"
#include "my_strtok.c"

/*
Programa gerador de par�frases por �rvore Splay.
Deve ser chamado na linha de comando como:
mainsplay --dict --text --output
onde:
--dict � o nome do arquivo contendo pares de sin�nimos
--text � o nome do arquivo de entrada, a ser parafraseado
--output � o nome do arquivo de sa�da gerado
*/


int main(int argc, char *argv[])
{
    // Inicializa��es
    setlocale(LC_ALL,"");
    FILE * dicionario;
    FILE * entrada;
    FILE * saida;
    char *palavra, linha[1000];
    char *sinonimo;
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    char separa_dict[] = {" \t\n"};
    char separa_achado[20];
    char *resto_linha;
    int tam_separador;
    int n_linhas, n_palavras;
    int comp_anterior;
    pNodoA *arvoreSplay;
    arvoreSplay = NULL;


    if (argc!=4)  // programa espera 4 par�metros
    {
        printf ("N�mero incorreto de par�metros.\n"
                "Para chamar o programa digite: mainsplay <arq_dicionario> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    // else, chamada do programa ok

    // Abertura de Arquivos
    dicionario = fopen (argv[1], "r"); // abre o dicionario para leitura
    if (dicionario == NULL)
    {
        printf ("Erro ao abrir o arquivo %s",argv[1]);
        return 1;
    }
    // else, arquivo dicionario OK
    entrada = fopen (argv[2], "r"); // abre o arquivo para leitura
    if (entrada == NULL)
    {
        printf ("Erro ao abrir o arquivo %s",argv[2]);
        fclose(dicionario);
        return 1;
    }
    // else, arquivo de entrada OK
    saida = fopen (argv[3], "w"); // cria o arquivo para saida
    if (saida == NULL)
    {
        printf ("Erro ao criar o arquivo %s",argv[3]);
        fclose(entrada);
        fclose(dicionario);
        return 1;
    }
    // else, arquivo de sa�da OK

    // Cria��o da �rvore
    while (fgets(linha,1000,dicionario))
    {   //percorre todo o dicionario, lendo linha por linha
        palavra = strtok (linha, separa_dict);
        sinonimo = strtok (NULL, separa_dict);
        while (palavra != NULL)
        {   // insere palavra e sin�nimo na �rvore e procura pr�ximos pares
            arvoreSplay = insereSplay(arvoreSplay, palavra, sinonimo);
            //printf("Inserindo palavra: %s, sinonimo: %s\n", palavra, sinonimo);
            palavra = strtok (NULL, separa_dict);
            sinonimo = strtok (NULL, separa_dict);
        }
    }
    printf("nodos arvore splay: %d\n", Nodos(arvoreSplay));
    

    // Parafraseamento do texto
    n_linhas = 0;
    n_palavras = 0;
    comp_anterior = 0;
    // percorre toda a entrada, lendo linha por linha
    // parafraseando e escrevendo no arquivo de sa�da
    while (fgets(linha,1000,entrada))
    {
        n_linhas++;
        // imprime poss�vel separador antes da primeira palavra
        tam_separador = strspn(linha, separador);
        strncpy(separa_achado, linha, tam_separador);
        separa_achado[tam_separador] = '\0';
        fprintf(saida, "%s", separa_achado);
        resto_linha = linha + tam_separador;


        palavra = my_strtok(NULL, separador, separa_achado, &resto_linha); // pega primeira token
        while (palavra != NULL)
        {
            n_palavras++;
            palavra = strlwr(palavra);
            sinonimo = buscaSinonimo(arvoreSplay, palavra); // procura a palavra (min�cula)
            if(sinonimo == NULL)
                sinonimo = palavra;
            // escreve no arquivo o sin�nimo, seguido pelo separador
            fprintf(saida,"%s%s", sinonimo, separa_achado);
            comp_anterior = comp;
            palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        }
    }

    // Impress�o das estat�sticas
    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
    printf("Compara��es Splay: %d\n", comp);
    printf("N�mero de nodos Splay: %d\n", Nodos(arvoreSplay));
    printf("Altura Splay: %d\n", Altura(arvoreSplay));
    printf("N�mero de linhas: %d\n", n_linhas);
    printf("Numero de palavras: %d\n", n_palavras);

    // Fechamento dos arquivos
    fclose (dicionario);
    fclose (entrada);
    fclose (saida);
    return 0;

}
