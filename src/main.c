#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <arguments>\n", argv[0]);
        return 1;
    }

    // Construct the command to call mainABP.c
    char commandABP[1024] = "gcc -o mainABP mainABP.c && C:\\Users\\moron\\OneDrive\\Documentos\\EstDados\\src\\mainABP.exe";
    for (int i = 1; i < argc; i++) {
        strcat(commandABP, " ");
        strcat(commandABP, argv[i]);
    }

    // Execute the command for mainABP.c
    int resultABP = system(commandABP);
    if (resultABP == -1) {
        perror("system");
        return 1;
    }

    // Construct the command to call mainsplay.c
    char commandSplay[1024] = "gcc -o mainsplay mainsplay.c && C:\\Users\\moron\\OneDrive\\Documentos\\EstDados\\src\\mainsplay.exe";
    for (int i = 1; i < argc; i++) {
        strcat(commandSplay, " ");
        strcat(commandSplay, argv[i]);
    }

    // Execute the command for mainsplay.c
    int resultSplay = system(commandSplay);
    if (resultSplay == -1) {
        perror("system");
        return 1;
    }

    return 0;
}