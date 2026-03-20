#include <stdio.h>
#include <string.h>

// functions
int var_count = 0;

typedef struct {
    char name[64];
    char value[512];
} Variable;
Variable vars[100];
int find_var(const char* name) {
    for (int i = 0; i < var_count; i++)
        if (strcmp(vars[i].name, name) == 0)
            return i;
    return -1;
}

void extr(const char* line, const char* start_marker, const char* end_marker, char* out) {
    const char* start = strstr(line, start_marker);
    if (!start) { out[0] = '\0'; return; }
    start += strlen(start_marker);
    const char* end = strstr(start, end_marker);
    if (!end) { out[0] = '\0'; return; }
    int len = end - start;
    strncpy(out, start, len);
    out[len] = '\0';
}
void subst(char* str, int dash_mode) {
    char buffer[512] = "";
    char temp[64];
    int i = 0;
    while (str[i]) {
        if (dash_mode && strncmp(str + i, "-{", 2) == 0) {
            int j = i + 2;
            while (str[j] && !(str[j] == '}' && str[j+1] == '-')) j++;
            if (str[j] == '}' && str[j+1] == '-') {
                int len = j - (i + 2);
                strncpy(temp, str + i + 2, len);
                temp[len] = '\0';
                int idx = find_var(temp);
                if (idx >= 0) {
                    strcat(buffer, vars[idx].value);
                } else {
                    strcat(buffer, temp);
                }
                i = j + 2;
                continue;
            }
        }
        else if (!dash_mode && str[i] == '{') {
            int j = i + 1;
            while (str[j] && str[j] != '}') j++;
            if (str[j] == '}') {
                int len = j - i - 1;
                strncpy(temp, str + i + 1, len);
                temp[len] = '\0';
                int idx = find_var(temp);
                if (idx >= 0)
                    strcat(buffer, vars[idx].value);
                else
                    strcat(buffer, temp);
                i = j + 1;
                continue;
            }
        }
        int len = strlen(buffer);
        buffer[len] = str[i];
        buffer[len+1] = '\0';
        i++;
    }
    strcpy(str, buffer);
}
void input_dash(char* prompt) {
    char buffer[512];
    subst(prompt, 1);       
    printf("%s", prompt);
    fflush(stdout);          
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

// main
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
    char content[512];
    char input[512];
while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    // o(...)
    if (strncmp(line, "o(", 2) == 0) {
        extr(line, "o(", ")", content);
        subst(content, 0);
        printf("%s\n", content);
    }
    // o-(...)- 
    else if (strncmp(line, "o-(", 3) == 0) {
        extr(line, "o-(", ")-", content);
        subst(content, 1);
        printf("%s\n", content);
    }
    // i(...) 
    else if (strncmp(line, "i(", 2) == 0) {
        extr(line, "i(", ")", content); 
        subst(content, 0);
        printf("%s", content);
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }
    // i-(...)- 
    else if (strncmp(line, "i-(", 3) == 0) {
        extr(line, "i-(", ")-", content);   
        input_dash(content);               
    }
}

    fclose(file);
    printf("\nPress Enter to exit...");
    getchar();
    return 0;
}