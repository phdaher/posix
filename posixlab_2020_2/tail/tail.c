#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void tail(FILE *f, const size_t n) {
    char *queue[n];
    size_t queue_len = 0;
    // [X, X, X, X, X]
    // [X, X, X, X, a]
    // [X, X, X, b, a]
    // ...
    // [e, d, c, b, a]
    // [f, e, d, c, b]
    // [g, f, e, d, c]

    while (1) {
        char *line = NULL;
        size_t line_len = 0;
        ssize_t n_read = getline(&line, &line_len, f);
        if (n_read == -1) {
            if (line) free(line);
            break;
        }
        if (queue_len != n) {
            queue[n - 1 - queue_len] = line;
            queue_len++;
        } else {
            free(queue[n - 1]);
            for (size_t i = n - 1; i >= 1; i--) {
                queue[i] = queue[i - 1];
            }
            queue[0] = line;
        }
    }

    /* printf("qlen %ld\n", queue_len); */
    /* printf("n %ld\n", n); */
    for (ssize_t i = n - 1; i >= (ssize_t)(n - queue_len); i--) {
        printf("%s", queue[i]);
        /* printf("%ld - %s", i, queue[i]); */
        /* printf("free idx %ld\n", i); */
        fflush(stdout);
        free(queue[i]);
    }
}

static bool file_tail(const char *name, const size_t n, const bool print_name) {
    FILE *f;
    if ((f = fopen(name, "r")) == NULL) {
        fprintf(stderr, "tail: %s: Cannot open file\n", name);
        return 1;
    }
    if (print_name) printf("==> %s <==\n", name);
    tail(f, n);
    fclose(f);
    return 0;
}

int main(int argc, char *argv[]) {
    size_t n = 10;
    if (argc == 1) {
        tail(stdin, n);
    } else if (argc == 2) {
        if (strcmp(argv[1], "-") == 0) {
            tail(stdin, n);
        } else {
            if (file_tail(argv[1], n, 0)) return 1;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                printf("==> standard input <==\n");
                tail(stdin, n);
            } else {
                if (file_tail(argv[i], n, 1)) return 1;
            }
            if (i != argc - 1) printf("\n");
        }
    }
    return 0;
}
