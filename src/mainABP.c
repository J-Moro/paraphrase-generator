#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "abp.c"
#include "my_strtok.c"

/*
Programa gerador de paráfrases por árvore ABP.
Deve ser chamado na linha de comando como:
mainABP --dict --text --output
onde:
--dict é o nome do arquivo contendo pares de sinônimos
--text é o nome do arquivo de entrada, a ser parafraseado
--output é o nome do arquivo de saída gerado
*/


int main(int argc, char *argv[])
{
    // Inicializações
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
    pNodoA *arvoreABP;
    arvoreABP = NULL;


    if (argc!=4)  // programa espera 4 parâmetros
    {
        printf ("Número incorreto de parâmetros.\n"
                "Para chamar o programa digite: mainABP <arq_dicionario> <arq_entrada> <arq_saida>\n");
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
    // else, arquivo de saída OK

    // Criação da árvore
    while (fgets(linha,1000,dicionario))
    {   //percorre todo o dicionario, lendo linha por linha
        palavra = strtok (linha, separa_dict);
        sinonimo = strtok (NULL, separa_dict);
        while (palavra != NULL)
        {   // insere palavra e sinônimo na árvore e procura próximos pares
            arvoreABP = Inserearvore(arvoreABP, palavra, sinonimo);
            palavra = strtok (NULL, separa_dict);
            sinonimo = strtok (NULL, separa_dict);
        }
    }

    // Parafraseamento do texto
    n_linhas = 0;
    n_palavras = 0;
    comp_anterior = 0;
    // percorre toda a entrada, lendo linha por linha
    // parafraseando e escrevendo no arquivo de saída
    while (fgets(linha,1000,entrada))
    {
        n_linhas++;
        // imprime possível separador antes da primeira palavra
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
            sinonimo = BuscaArvore(arvoreABP, palavra); // procura a palavra (minúcula)
            if(sinonimo == NULL)
                sinonimo = palavra;
            // escreve no arquivo o sinônimo, seguido pelo separador
            fprintf(saida,"%s%s", sinonimo, separa_achado);
            comp_anterior = comp;
            palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        }
    }

    // Impressão das estatísticas
    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
    printf("Comparações ABP: %d\n", comp);
    printf("Número de nodos ABP: %d\n", Nodos(arvoreABP));
    printf("Altura ABP: %d\n", Altura(arvoreABP));
    printf("Número de linhas: %d\n", n_linhas);
    printf("Numero de palavras: %d\n", n_palavras);

    // Fechamento dos arquivos
    fclose (dicionario);
    fclose (entrada);
    fclose (saida);
    return 0;

}
