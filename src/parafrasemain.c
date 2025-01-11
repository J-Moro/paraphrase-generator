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




int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    FILE * dicionario;
    FILE * entrada;
    FILE * saida;

    char *palavra, linha[1000]; // buffer de linha de 999 bytes
    char *sinonimo;
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    char separa_dict[] = {" \t\n"};

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

    // percorre toda a entrada, lendo linha por linha
    // traduzindo e escrevendo no arquivo de saída
    while (fgets(linha,1000,entrada))
    {
        palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
        while (palavra != NULL)
        {
            sinonimo = BuscaArvore(arvoreABP, palavra);
            if(sinonimo == NULL)
                sinonimo = palavra;
            fprintf(saida,"%s ", sinonimo); //strlwr � a fun��o que converte palavras para min�sculo
            palavra = strtok (NULL, separador);
        }
    }

    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);

    printf("Comparacoes ABP: %d\n", comp);
    printf("Numero de nodos ABP: %d\n", Nodos(arvoreABP));
    printf("Altura ABP: %d\n", Altura(arvoreABP));

    fclose (entrada); //fecha os arquivos
    fclose (saida);
    return 0;

}
