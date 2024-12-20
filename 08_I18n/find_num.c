#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <libgen.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "./po"
#define MIN 1
#define MAX 100
#define STR_MAX 32

#define YES 'y'
#define NO 'n'

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("find_num", LOCALE_PATH);
    textdomain("find_num");

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