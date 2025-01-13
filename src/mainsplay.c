#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
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
    int n_linhas, n_palavras, n_traduzidas, n_n_trad, n_dicionario;
    int comp_anterior, comp_traduzidas, comp_n_trad;
    double media_comp, desvio_comp, var_comp;
    double media_traduzidas, desvio_traduzidas, var_traduzidas;
    double media_n_trad, desvio_n_trad, var_n_trad;
    double media_rotacoes, desvio_rotacoes, var_rotacoes;
    double media_criacao;
    int rot_anterior, rotacoes_criacao;
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
    n_dicionario = 0;
    // Cria��o da �rvore
    while (fgets(linha,1000,dicionario))
    {   //percorre todo o dicionario, lendo linha por linha
        palavra = strtok (linha, separa_dict);
        sinonimo = strtok (NULL, separa_dict);
        while (palavra != NULL)
        {   // insere palavra e sin�nimo na �rvore e procura pr�ximos pares
            arvoreSplay = insereSplay(arvoreSplay, palavra, sinonimo);
            n_dicionario++;
            palavra = strtok (NULL, separa_dict);
            sinonimo = strtok (NULL, separa_dict);
        }
    }
    rotacoes_criacao = rotacoes;


    // Parafraseamento do texto
    n_linhas = 0;
    n_palavras = 0;
    comp_anterior = 0;
    rot_anterior = rotacoes;
    n_traduzidas = 0;
    var_comp = 0;
    comp_traduzidas = 0;
    var_traduzidas = 0;
    n_n_trad = 0;
    comp_n_trad = 0;
    var_n_trad = 0;
    var_rotacoes = 0;
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
            sinonimo = buscaSinonimo(&arvoreSplay, palavra); // procura a palavra (minúcula)
            if(sinonimo == NULL){
                sinonimo = palavra;
                comp_n_trad += comp - comp_anterior;
                var_n_trad += pow(comp - comp_anterior, 2);
            }
            else{
                comp_traduzidas += comp - comp_anterior;
                n_traduzidas++;
                var_traduzidas += pow(comp - comp_anterior, 2);
            }
            // escreve no arquivo o sinônimo, seguido pelo separador
            fprintf(saida,"%s%s", sinonimo, separa_achado);
            var_comp += pow(comp - comp_anterior, 2);
            var_rotacoes += pow(rotacoes - rot_anterior, 2);
            rot_anterior = rotacoes;
            comp_anterior = comp;
            palavra = my_strtok(NULL, separador, separa_achado, &resto_linha);
        }
    }

    media_comp = (double)comp / n_palavras;
    var_comp = (double) var_comp / n_palavras - pow(media_comp, 2);
    desvio_comp = sqrt(var_comp);

    media_rotacoes = (double) (rotacoes - rotacoes_criacao) / n_palavras;
    var_rotacoes = (double) var_rotacoes / n_palavras - pow(media_rotacoes,2);
    desvio_rotacoes = sqrt(var_rotacoes);
    media_criacao = (double) rotacoes_criacao / n_dicionario;

    media_traduzidas = (double) comp_traduzidas / n_traduzidas;
    var_traduzidas = (double) var_traduzidas / n_traduzidas - pow(media_traduzidas, 2);
    desvio_traduzidas = sqrt(var_traduzidas);

    n_n_trad = n_palavras - n_traduzidas;
    media_n_trad = (double) comp_n_trad / n_n_trad;
    var_n_trad = (double) var_n_trad / n_n_trad - pow(media_n_trad, 2);
    desvio_n_trad = sqrt(var_n_trad);


    // Impressão das estatísticas
    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
    printf("Comparacoes Splay: %d\n", comp);
    printf("Numero de sinonimos guardados: %d\n", n_dicionario);
    if (n_dicionario <= 35000){
        printf("Numero de nodos Splay: %d\n", Nodos(arvoreSplay));
        printf("Altura Splay: %d\n", Altura(arvoreSplay));
    }
    else
        printf("Numero de nodos muito grande: possivel erro de stack.\n"
               "Testar altura da arvore manualmente.\n");
    printf("Numero de linhas: %d\n", n_linhas);
    printf("\n");
    printf("Numero de rotacoes na criacao da Splay: %d\n", rotacoes_criacao);
    printf("Numero de rotacoes na consulta a Splay: %d\n", rotacoes - rotacoes_criacao);
    printf("Numero de rotacoes totais: %d\n", rotacoes);
    printf("Media de rotacoes na criacao: %f\n", media_criacao);
    printf("Media de rotacoes na consulta: %f\n", media_rotacoes);
    printf("Variancia de rotacoes na consulta: %f\n", var_rotacoes);
    printf("Desvio padrao de rotacoes na consulta: %f\n", desvio_rotacoes);
    printf("\n");
    printf("Numero de palavras: %d\n", n_palavras);
    printf("Media de comparacoes por palavra: %f\n", media_comp);
    printf("Variancia de comparacoes por palavra: %f\n", var_comp);
    printf("Desvio padrao de comparacoes por palavra: %f\n", desvio_comp);
    printf("\n");
    printf("Numero de palavras traduzidas: %d\n", n_traduzidas);
    printf("Comparacoes das palavras traduzidas: %d\n", comp_traduzidas);
    printf("Media das palavras traduzidas: %f\n", media_traduzidas);
    printf("Variancia das palavras traduzidas: %f\n", var_traduzidas);
    printf("Desvio padrao das palavras traduzidas: %f\n", desvio_traduzidas);
    printf("\n");
    printf("Numero de palavras nao traduzidas: %d\n", n_n_trad);
    printf("Comparacoes das palavras nao traduzidas: %d\n", comp_n_trad);
    printf("Media das palavras nao traduzidas: %f\n", media_n_trad);
    printf("Variancia das palavras nao traduzidas: %f\n", var_n_trad);
    printf("Desvio padrao das palavras nao traduzidas: %f\n", desvio_n_trad);


    // Fechamento dos arquivos
    fclose (dicionario);
    fclose (entrada);
    fclose (saida);
    return 0;

}
