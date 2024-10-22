#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10
#define START_SIZE 64

void take_error(int regex_error, regex_t* regex) {
    size_t size = regerror(regex_error, regex, NULL, 0);
    char* errbuf = (char*)malloc(size * sizeof(char));
    regerror(regex_error, regex, errbuf, size);
    fprintf(stderr, "%s\n", errbuf);
    free(errbuf);
}

char* realloc_res(size_t* size, char* res, int cur_position) {
    if (cur_position == *size - 2) {
        while (*size < cur_position) {
            *size *= 2;
        }

        res = (char*)realloc(res, *size * sizeof(char));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Not enough arguments!\n");
        return 1;
    }

    int chars;
    regex_t regex;
    regmatch_t bags[MAXGR];
    int regex_error;

    if ((regex_error = regcomp(&regex, argv[1], REG_EXTENDED)) != 0) {
        take_error(regex_error, &regex);
        return 1;
    }

    if ((regex_error = regexec(&regex, argv[3], MAXGR, bags, 0)) != 0) {
        take_error(regex_error, &regex);
        return 1;
    }

    size_t res_size = ((START_SIZE < bags[0].rm_so) ? bags[0].rm_so : START_SIZE);
    char* res = (char*)malloc(res_size * sizeof(char));

    int res_index;
    if (bags[0].rm_so >= 0) {
        strncpy(res, argv[3], bags[0].rm_so);
        res_index = bags[0].rm_so;
    } else {
        res_size = strlen(argv[3]);
        realloc_res(&res_size, res, START_SIZE);
        res_index = 0;
    }

    int subs_index = -1;
    while (++subs_index < strlen(argv[2])) {
        if (argv[2][subs_index] == '\\') {
            subs_index++;
            if (subs_index == strlen(argv[2])) {
                fprintf(stderr, "Incorrect substitution!\n");
                free(res);
                return 1;
            }

            if (argv[2][subs_index] <= '9' && argv[2][subs_index] >= '0') {
                int bags_num = atoi(&argv[2][subs_index]);
                if (bags[bags_num].rm_so < 0) {
                    fprintf(stderr, "Not enough matches! \\%d\n", bags_num);
                    free(res);
                    return 1;
                }

                for (int i = 0; i < bags[bags_num].rm_eo - bags[bags_num].rm_so; i++) {
                    res[res_index++] = argv[3][bags[bags_num].rm_so + i];
                    realloc_res(&res_size, res, res_index);
                }
            } else if (argv[2][subs_index] == '\\') {
                res[res_index++] = argv[2][subs_index];
            } else {
                fprintf(stderr, "Incorrect \\!");
                free(res);
                return 1;
            }
        } else {
            res[res_index++] = argv[2][subs_index];
        }
    }

    if (bags[0].rm_so >= 0) {
        strncpy(res + res_index, argv[3] + bags[0].rm_eo, strlen(argv[3]) - bags[0].rm_eo);
        res[res_index + strlen(argv[3]) - bags[0].rm_eo] = '\0';
    }

    printf("%s\n", res);

    free(res);
    regfree(&regex);
    return 0;
}