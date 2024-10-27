#define _GNU_SOURCE
#include <dlfcn.h>
#include <regex.h>

typedef int (*remove_type)(char* filename);

int remove(char* filename) {
    regex_t regex;
    regmatch_t bags[1];
    regcomp(&regex, "(.*?)PROTECT(.*?)", REG_EXTENDED);
    regexec(&regex, filename, 1, bags, 0);

    int errnum = 0;
    if (bags[0].rm_so < 0) {
        errnum = ((remove_type)(dlsym(RTLD_NEXT, "remove")))(filename);
    }

    return errnum;
}