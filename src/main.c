#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <arguments>\n", argv[0]);
        return 1;
    }

    // Construct the command to call parafrasemain.c
    char command[1024] = "gcc parafrasemain.c -o parafrasemain && ./parafrasemain";
    for (int i = 1; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    // Execute the command
    int result = system(command);
    if (result == -1) {
        perror("system");
        return 1;
    }

    return 0;
}