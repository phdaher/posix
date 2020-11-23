#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        char c;
        while (read(STDIN_FILENO, &c, 1) > 0) {
            printf("%c", c);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                char c;
                while (read(STDIN_FILENO, &c, 1) > 0) {
                    printf("%c", c);
                }
            } else {
                FILE *f;
                if ((f = fopen(argv[i], "r")) == NULL) {
                    fprintf(stderr, "cat: %s: Cannot open file\n", argv[i]);
                    return 1;
                }
                int c;
                while ((c = fgetc(f)) != EOF) {
                    printf("%c", c);
                }
                fclose(f);
            }
        }
    }
    return 0;
}
