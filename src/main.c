#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Error: Please specify a .catgm file.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Failed to open file\n");
        return 1;
    }

    char line[256];
while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    if (line[0] == 'o' && line[1] == '(') {
        char *start = line + 2;
        char *end = line + strlen(line) - 1;
        if (*end == ')') {
            *end = '\0';
        }
        printf("%s\n", start);
    }
}

    fclose(file);
    printf("\nPress Enter to exit...");
    getchar();
    return 0;
}