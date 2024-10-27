#include <stdio.h>
#include <file.h>
#include <string.h>
#include <stdlib.h>

enum {ERROR_INPUT_ARGS = 101, ERROR_OPEN_INPUT_FILE,
      ERROR_OPEN_OUTPUT_FILE, ERROR_READ_INPUT_FILE,
      ERROR_WRITE_OUTPUT_FILE, ERROR_CLOSE_INPUT_FILE,
      ERROR_CLOSE_OUTPUT_FILE, ERROR_DELETE_INPUT_FILE,
      ERROR_DELETE_OUTPUT_FILE};

size_t bufsize = 1024;

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect input arguments!\n");
        return ERROR_INPUT_ARGS;
    }

    FILE *input, *output;

    if ((input = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Open input file failed!\n");
        if (remove(argv[2]) != 0) {
            fprintf(stderr, "Removing output file failed!\n");
            return ERROR_DELETE_OUTPUT_FILE;
        };
        return ERROR_OPEN_INPUT_FILE;
    };

    if ((output = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Open output file failed!\n");
        return ERROR_OPEN_OUTPUT_FILE;
    };

    char* buf = (char*)malloc(sizeof(char) * bufsize);
    long unsigned int c = 0;

    while ((c = getline(&buf, &bufsize, input)) != -1) {
        if (ferror(input) != 0) {
            fprintf(stderr, "Read from input error!\n");
            free(buf);
            if (remove(argv[2]) != 0) {
                fprintf(stderr, "Removing output file failed!\n");
                return ERROR_DELETE_OUTPUT_FILE;
            };
            return ERROR_READ_INPUT_FILE;
        }

        //printf("%s", buf);
        //int count = fwrite(buf, sizeof(char), c, output);
        if (write(fileno(output), buf, sizeof(char) * c) == -1) {
        //if (count == 0) {
            fprintf(stderr, "Write to output error!\n");
            free(buf);
            if (remove(argv[2]) != 0) {
                fprintf(stderr, "Removing output file failed!\n");
                return ERROR_DELETE_OUTPUT_FILE;
            };
            return ERROR_WRITE_OUTPUT_FILE;
        }
    }

    if (ferror(input) != 0) {
        fprintf(stderr, "Read from input error!\n");
        free(buf);
        if (remove(argv[2]) != 0) {
            fprintf(stderr, "Removing output file failed!\n");
            return ERROR_DELETE_OUTPUT_FILE;
        };
        return ERROR_READ_INPUT_FILE;
    }

    if (fclose(input) != 0) {
        fprintf(stderr, "Closing input file failed!\n");
        free(buf);
        if (remove(argv[2]) != 0) {
            fprintf(stderr, "Removing output file failed!\n");
            return ERROR_DELETE_OUTPUT_FILE;
        };
        return ERROR_CLOSE_INPUT_FILE;
    }

    if (fclose(output) != 0) {
        fprintf(stderr, "Closing output file failed!\n");
        free(buf);
        if (remove(argv[2]) != 0) {
            fprintf(stderr, "Removing output file failed!\n");
            return ERROR_DELETE_OUTPUT_FILE;
        };
        return ERROR_CLOSE_OUTPUT_FILE;
    }

    free(buf);

    if (remove(argv[1]) != 0) {
        fprintf(stderr, "Removing input file failed!\n");
        if (remove(argv[2]) != 0) {
            fprintf(stderr, "Removing output file failed!\n");
            return ERROR_DELETE_OUTPUT_FILE;
        };
        return ERROR_DELETE_INPUT_FILE;
    };

    return 0;
}