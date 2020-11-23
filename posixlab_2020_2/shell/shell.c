#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    char *str;
    size_t len;
} string;

typedef struct {
    char **data;
    size_t len;
    size_t _alloclen;
} charp_vector;

charp_vector *charp_vector_create() {
    charp_vector *v = malloc(sizeof(charp_vector));
    v->data = malloc(10 * sizeof(char *));
    v->len = 0;
    v->_alloclen = 10;
    return v;
}
static void charp_vector_free(charp_vector *v) {
    free(v->data);
    free(v);
}

void charp_vector_add(charp_vector *v, char *data) {
    if (v->len == v->_alloclen) {
        v->_alloclen *= 2;
        v->data = realloc(v->data, v->_alloclen * sizeof(char *));
    }
    v->data[v->len] = data;
    v->len++;
}

/* int exitcode = 0; */
static char *prompt() {
    /* printf("[%d] $ ", exitcode); */
    printf("$ ");
    fflush(stdout);

    char *line = NULL;
    size_t line_len = 0;
    ssize_t n_read = getline(&line, &line_len, stdin);
    if (n_read == -1) {
        if (line) free(line);
        return NULL;
    }
    return line;
}

static charp_vector *parse_args(const char *s) {
    char *c = (char *)s;

    charp_vector *argsv = charp_vector_create();
    size_t n_args = 0;

    char *arg_start = c;
    for (; *c != '\0'; c++) {
        if (*c == ' ') {
            *c = '\0';
            charp_vector_add(argsv, arg_start);
            arg_start = c + 1;
        }
    }
    if (c != arg_start) {
        *(c - 1) = '\0';

        charp_vector_add(argsv, arg_start);
    }
    charp_vector_add(argsv, NULL);

    return argsv;
}

int main() {
    while (1) {
        char *cmd = prompt();
        if (!cmd) {
            printf("\n");
            break;
        }

        charp_vector *argsv = parse_args(cmd);
        char **args = argsv->data;
        /* for (int i = 0; i < argsv->len - 1; i++) { */
        /*     printf("arg %s\n", argsv->data[i]); */
        /* } */

        if (strcmp(cmd, "exit") == 0) {
            free(cmd);
            charp_vector_free(argsv);
            break;
        }

        if (strcmp(cmd, "cd") == 0) {
            if (argsv->len == 2) {
                char *home = getenv("HOME");
                if (home) {
                    if (chdir(home) != 0)
                        fprintf(stderr, "shell: cd: %s: cannot access directory\n", home);
                }
            } else if (argsv->len == 3) {
                if (chdir(argsv->data[1]))
                    fprintf(stderr, "shell: cd: %s: cannot access directory\n", argsv->data[1]);
            } else {
                fprintf(stderr, "shell: cd: too many arguments\n");
            }
        } else {
            pid_t filho;
            filho = fork();
            if (filho == 0) {
                return execvp(args[0], args);
            } else {
                int ws;
                wait(&ws);
                /* exitcode = WEXITSTATUS(ws); */
            }
        }

        free(cmd);
        charp_vector_free(argsv);
    }

    return 0;
}
