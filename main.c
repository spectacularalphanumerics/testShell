#include <iostream>


int main() {
    //      load config files, if existant

    //      run command loop
    lsh_loop();;

    //      perform shutdown/cleanup

    return EXIT_SUCCESS;
}

void lsh_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("~~");
        line = lsh_read_line();
        args = lsh_split_line();
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *lsh_read_line() {
    char *line = NULL;
    ssize_t bufsize = 0;    //      we will let getline allocate the buffer for us

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);     //      if we recieve EOF (user presses ctrl + d or file of commands at end)
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}