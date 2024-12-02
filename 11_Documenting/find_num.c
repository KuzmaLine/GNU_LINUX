#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <libgen.h>
#include <unistd.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "./po"
#define MIN 1
#define MAX 100
#define STR_MAX 32

#define YES 'y'
#define NO 'n'

opterr = 0;
#define R_SIZE 13

const char *ROMAN_NUMBERS[R_SIZE] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int ROMAN_VALUES[R_SIZE] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

void to_roman(int num, char res[]) {
    int index = 0;
    for (int i = 0; i < R_SIZE; i++) {
        while(num >= ROMAN_VALUES[i]) {
            num -= ROMAN_VALUES[i];
            
            for (int j = 0; j < strlen(ROMAN_NUMBERS[i]); j++) {
                res[index++] = ROMAN_NUMBERS[i][j];
            }
        }
    }
}

int from_roman(char number[]) {
    int res = 0;
    char buf[3];

    int index = 0;
    for (int i = 0; i < 13; i++) {
        strncpy(buf, number + index, strlen(ROMAN_NUMBERS[i]));
        while(strcmp(buf, ROMAN_NUMBERS[i]) == 0 && index < strlen(number)) {
            res += ROMAN_VALUES[i];
            index += strlen(ROMAN_NUMBERS[i]);
            strncpy(buf, number + index, strlen(ROMAN_NUMBERS[i]));
        }
    }

    return res;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("find_num", LOCALE_PATH);
    textdomain("find_num");
    int opt;

    if ((opt = getopt(argc, argv, "r")) != -1 && opt != '?') {
        printf("-r is given!\n");
    }

    int cur_max = MAX;
    int cur_min = MIN;
    int cur = cur_min + (cur_max - cur_min) / 2;
    int target;
    char answer[STR_MAX];
    printf(_("Is your number equal %d?\n"), cur);
    fgets(answer, STR_MAX, stdin);

    while(answer[0] != YES) {
        if (cur_max - cur_min == 1) {
            cur = cur_max;
            printf(_("Is your number equal %d?\n"), cur);
            fgets(answer, STR_MAX, stdin);
            continue;
        }

        int flag_correct_answer = 0;

        while (!flag_correct_answer) {
            printf(_("Is your number less than %d?\n"), cur);
            fgets(answer, STR_MAX, stdin);
            printf("%s\n", answer);
            if (answer[0] == YES) {
                cur_max = cur;
                flag_correct_answer = 1;
            } else if (answer[0] == NO) {
                cur_min = cur;
                flag_correct_answer = 1;
            } else {
                printf(_("Incorrect answer. Please say y (YES) or n (NO)\n"));
            }
        }

        cur = cur_min + (cur_max - cur_min) / 2;
        printf(_("Is your number equal %d?\n"), cur);
    }

    printf(_("Number is %d\n"), cur);
    return 0;
}