/**
 * @mainpage
 * 
 * @section intro_sec Introduction
 * This program lets you guess a number between 1 and 100 using binary search.
 * 
 * @section usage_sec Usage
 * The program supports the following options:
 * 
 * - `-r` : Output numbers in Roman numerals.
 * - `--help` : Display this help message.
 * 
 * @note Localization is supported using Gettext for multiple languages.
 *
 */

/**
 * @file find_num.c
 * @brief A program for guessing a number between MIN and MAX using binary search.
 * 
 * This program allows the user to guess a number between 1 and 100 using binary search.
 * It also provides an option to output the numbers in Roman numerals.
 * 
 * @note Localization is supported using Gettext for multiple languages.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <libgen.h>
#include <unistd.h>
#include <getopt.h>

#define _(STRING) gettext(STRING) /**< Macro for translation using gettext */
#define LOCALE_PATH "./po" /**< Path to the locale directory */
#define MIN 1 /**< Minimum value for the guess range */
#define MAX 100 /**< Maximum value for the guess range */
#define STR_MAX 32 /**< Maximum length of the output string for Roman numerals */

#define YES 'y' /**< Character representing a 'yes' answer */
#define NO 'n' /**< Character representing a 'no' answer */

opterr = 0;
#define R_SIZE 13 /**< The size of the ROMAN_NUMBERS array */

/** @brief Array containing Roman numeral symbols in decreasing order. */
const char *ROMAN_NUMBERS[R_SIZE] = {
    "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
};

/** @brief Array containing the corresponding decimal values for the Roman numerals. */
const int ROMAN_VALUES[R_SIZE] = {
    1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
};

/**
 * @brief Converts an integer to its Roman numeral representation.
 *
 * This function converts an integer between 1 and 100 to a string containing
 * the Roman numeral equivalent. The result is stored in the provided character
 * array `res`.
 *
 * @param num The integer to convert (should be between 1 and 100).
 * @param res A character array where the Roman numeral will be stored.
 *
 * @note The character array `res` should have enough space to store the result.
 *       The array will be null-terminated.
 * 
 * @see ROMAN_NUMBERS
 * @see ROMAN_VALUES
 */
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

    while (index < MAX) {
        res[index++] = '\0';
    }
}

/*
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
*/

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("find_num", LOCALE_PATH);
    textdomain("find_num");
    int opt;
    int is_roman = 0;

    // Определение длинных опций
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"roman", no_argument, 0, 'r'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    // Обработка опций
    while ((opt = getopt_long(argc, argv, "r", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                // Параметр --help
                printf(_("This program lets you guess a number between 0 and 100 using binary search.\n -r  Output numbers in Roman notation.\n --help  Display this help message.\n"));
                return 0;

            case 'r':
                // Параметр -r (римская нотация)
                is_roman = 1;
                break;

            case 'v':
                // Параметр -v
                printf("v1.0.0\n");
                return 0;

            case '?':
                // Обработка ошибок или неизвестных опций
                return 1;
        }
    }

    int cur_max = MAX;
    int cur_min = MIN;
    int cur = cur_min + (cur_max - cur_min) / 2;
    int target;
    char answer[STR_MAX];
    char romanBuf[100];

    if (!is_roman) printf(_("Is your number equal %d?\n"), cur);
    else {
        to_roman(cur, romanBuf);
        printf(_("Is your number equal %s?\n"), romanBuf);
    }
    fgets(answer, STR_MAX, stdin);

    while(answer[0] != YES) {
        if (cur_max - cur_min == 1) {
            cur = cur_max;
            if (!is_roman) printf(_("Is your number equal %d?\n"), cur);
            else {
                to_roman(cur, romanBuf);
                printf(_("Is your number equal %s?\n"), romanBuf);
            }
            fgets(answer, STR_MAX, stdin);
            continue;
        }

        int flag_correct_answer = 0;

        while (!flag_correct_answer) {
            if (!is_roman) printf(_("Is your number less than %d?\n"), cur);
            else {
                to_roman(cur, romanBuf);
                printf(_("Is your number less than %s?\n"), romanBuf);
            }
            fgets(answer, STR_MAX, stdin);
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
        if (!is_roman) printf(_("Is your number equal %d?\n"), cur);
        else {
            to_roman(cur, romanBuf);
            printf(_("Is your number equal %s?\n"), romanBuf);
        }
    }

    if (!is_roman) printf(_("Number is equal %d?\n"), cur);
    else {
        to_roman(cur, romanBuf);
        printf(_("Number is equal %s?\n"), romanBuf);
    }
    return 0;
}