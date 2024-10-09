#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int N;
    int M = 0, S = 1;
    switch(argc) {
        case 1:
            printf("range from Python.\n" \
                    "1 parameter (N) - show sequence of number [0, ..., N - 1]\n" \
                    "2 parameters (M, N) - show [M, M+1, ..., N-1]\n" \
                    "3 parameters (M, N, S) - show [M, M+S, M+2S, ..., N-1]\n.");
            return 0;
        case 2:
            N = atoi(argv[1]);
            break;
        case 4:
            S = atoi(argv[3]);
        case 3:
            M = atoi(argv[1]);
            N = atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "Incorrect parametrs!");
            return 1;
    };

    for (int i = M; i < N; i += S) {
        printf("%d\n", i);
    }

    return 0;
}