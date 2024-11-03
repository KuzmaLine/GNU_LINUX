#include <stdio.h>
#include <rhash.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <ctype.h>

#ifdef ENABLE_READLINE
#include <readline/readline.h>
#endif

int hash_file(const char* filename, int hash_type, int output_type, unsigned char* digest, char* output) {
    rhash_file(hash_type, filename, digest);
    rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), output_type);
    printf("%s\n", output);

    return 0;
}

int hash_string(const char* string, int hash_type, int output_type, unsigned char* digest, char* output) {
    rhash_msg(hash_type, string, strlen(string), digest);
    rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), output_type);
    printf("%s\n", output);

    return 0;
}


int main(int argc, char** argv) {
    char delim = ' ';
    unsigned char digest[64];
    char output[130];
    
    int hash_type, output_type;

    rhash_library_init();
    
    char* line;
#ifdef ENABLE_READLINE
    while((line = readline(NULL)) != NULL) {
#else
    size_t lenght = 0;
    ssize_t count;
    while((count = getline(&line, &lenght, stdin)) != -1) {
#endif
        
        char* cry_type_str = strtok(line, &delim);
        char* input = strtok(NULL, &delim);
        //printf("%s\n", input);

        if (cry_type_str == NULL || input == NULL) {
            fprintf(stderr, "Введите алгоритм шифрования (Доступны sha1, md5, tth) и через пробел имя файла или строку через \"\"!\n");
            continue;
        }

        if (strcasecmp(cry_type_str, "sha1") == 0) {
            hash_type = RHASH_SHA1;
        } else if (strcasecmp(cry_type_str, "md5") == 0) {
            hash_type = RHASH_MD5;
        } else if (strcasecmp(cry_type_str, "tth") == 0) {
            hash_type = RHASH_TTH;
        } else {
            fprintf(stderr, "Доступные алгоритмы шифрования - sha1, md5, tth!\n");
            continue;
        }

        if(isupper(cry_type_str[0])) {
            output_type = RHPR_HEX;
        } else {
            output_type = RHPR_BASE64;
        }

        if (input[0] == '"') {
            input[strlen(input) - 1] = '\0';
            input = input + 1;
            //printf("%s\n", input);
            hash_string(input, hash_type, output_type, digest, output);
        } else {
            hash_file(input, hash_type, output_type, digest, output);
        }

        free(line);
    }

    return 0;
}