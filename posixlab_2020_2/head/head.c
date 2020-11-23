#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void head(FILE *f, const size_t n) {
    for (size_t counter = 0; counter < n; counter++) {
        char *line;
        size_t line_len = 0;
        size_t n_read;
        if ((n_read = getline(&line, &line_len, f)) == -1) {
            if (line) free(line);
            break;
        }
        printf("%s", line);
        free(line);
    }
}

static bool file_head(const char *name, const size_t n, const bool print_name) {
    FILE *f;
    if ((f = fopen(name, "r")) == NULL) {
        fprintf(stderr, "head: %s: Cannot open file\n", name);
        return 1;
    }
    if (print_name) printf("==> %s <==\n", name);
    head(f, n);
    fclose(f);
    return 0;
}

int main(int argc, char *argv[]) {
    /* head(stdin, 10); */
    /* return 0; */
    size_t n = 10;
    if (argc == 1) {
        head(stdin, n);
    } else if (argc == 2) {
        if (strcmp(argv[1], "-") == 0) {
            head(stdin, n);
        } else {
            if (file_head(argv[1], n, 0)) return 1;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                printf("==> standard input <==\n");
                head(stdin, n);
            } else {
                if (file_head(argv[i], n, 1)) return 1;
            }
            if (i != argc - 1) printf("\n");
        }
    }
    return 0;
}
