#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 6
#define SPACE '.'
#define WALL '#'
#define TARGET '!'
#define INDX(i, j, n) ((i) * n + (j))

int gen_num(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// -1 - Везде должны быть стены.
// 0 - сверху 1 - справа 2 - снизу 3 - слева
int check_room(int* lab, int size, int i, int j, int to) {
    int from = (to + 2) % 4;
    int empty[4] = {0, 0, 0, 0};
    if (to != -1) {
        empty[from] = 1;
    }

    int additions_corner[4][4] = {{-1, -1, -1, 1},
                                {-1, 1, 1, 1},
                                {1, 1, 1, -1},
                                {1, -1, -1, -1}};
    int additions_way[] = {-1, 0, 0, 1, 1, 0, 0, -1};

    if (to != -1) {
        i += additions_way[to * 2];
        j += additions_way[to * 2 + 1];

        if (i == 0 || i == size - 1 || j == 0 || j == size - 1 || lab[INDX(i, j, size)] == 1) {
            return 0;
        }

        //if (lab[INDX(i, j, size)] == 2) {
        //    return 1;
        //}
    }

    /*
    for (int p = 0; p < 8; p++) {
        if (p % 2) {
            if (lab[INDX(i + additions_corner[p - 1], j + additions_corner[p], size)] != 0) {
                return 0;
            }
        } else {
            if (empty[p / 2] != lab[INDX(i + additions_way[p], j + additions_way[p + 1], size)]) {
                return 0;
            }
        }
    }
    */

    for (int p = 0; p < 4; p++) {
        if (lab[INDX(i + additions_way[2*p], j + additions_way[2*p + 1], size)] == 2) {
            return 1;
        }

        if (empty[p] != lab[INDX(i + additions_way[2*p], j + additions_way[2*p + 1], size)]) {
            return 0;
        }
    }

    if (to != -1) {
        for (int p = 0; p < 2; p++) {
            if (lab[INDX(i + additions_corner[to][p*2], j + additions_corner[to][p*2 + 1], size)] != 0 || 
                lab[INDX(i + additions_corner[to][p*2], j + additions_corner[to][p * 2 + 1], size)] != 0) {
                return 0;
            }
        }
    }

    return 1;
}

/*
int check_gen_lab(int lab[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (lab[INDX(i, j)] == 1) {
                
            }
        }
    }
}
*/

void print_lab(int* lab, int size) {
    char symbols[] = {WALL, SPACE, TARGET};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", symbols[lab[INDX(i,j, size)]]);
        }

        printf("\n");
    }
}

int check_all_ways(int* lab, int size, int i, int j) {
    for (int p = 0; p < 4; p++) {
        if(check_room(lab, size, i, j, p)) {
            return 1;
        }
    }
    return 0;
}

int check_free_path(int* lab, int lab_size, int path[], int* path_size) {
    for (int p = (*path_size) - 1; (*path_size) != 0; p--) {
        if (check_all_ways(lab, lab_size, path[p * 2], path[p * 2 + 1])) {
            return 1;
        }

        (*path_size)--;
    }

    return 0;
}

void check_target_cells(int *lab, int size, int i, int j, int* way) {
    int additions_way[] = {-1, 0, 0, 1, 1, 0, 0, -1};

    for (int p = 0; p < 4; p++) {
        if (lab[INDX(i + additions_way[p*2], j + additions_way[p*2 + 1], size)] == 2 && check_room(lab, size, i, j, p)) {
            *way = p;

            /*
            p = (p + 2) % 4;
            if (lab[INDX(i + additions_way[p*2], j + additions_way[p*2 + 1], size)] == 2 && check_room(lab, size, i, j, p)) {
                *second_way = p;
            }
            */

            return;
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int actual_size = SIZE * 2 + 1;
    int* lab = (int*)malloc(sizeof(int) * actual_size * actual_size);
    memset(lab, 0, sizeof(int) * actual_size * actual_size);
    // Создание начальных комнат

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            lab[INDX(2*i + 1, 2*j + 1, actual_size)] = 2;
        }
    }

    int rooms_count = SIZE * SIZE;

    int start_i = gen_num(1, actual_size - 2);
    int start_j = gen_num(1, actual_size - 2);

    int is_success = 0;
    while(!is_success) {
        is_success = 1;
        if (lab[INDX(start_i, start_j, actual_size)] == 2) {
            rooms_count--;
            lab[INDX(start_i, start_j, actual_size)] = 1;
        } else {
            if (lab[INDX(start_i - 1, start_j, actual_size)] == 2) {
                lab[INDX(start_i, start_j, actual_size)] = 1;
                lab[INDX(start_i - 1, start_j, actual_size)] = 1;
                lab[INDX(start_i + 1, start_j, actual_size)] = 1;
                start_i++;
            } else if (lab[INDX(start_i, start_j - 1, actual_size)] == 2) {
                lab[INDX(start_i, start_j, actual_size)] = 1;
                lab[INDX(start_i, start_j - 1, actual_size)] = 1;
                lab[INDX(start_i, start_j + 1, actual_size)] = 1;
                start_j++;
            } else {
                start_i = gen_num(1, actual_size - 2);
                start_j = gen_num(1, actual_size - 2);
                is_success = 0;
            }
        }
    }

    int path_size = 1;
    int path[2 * actual_size * actual_size];
    path[0] = start_i;
    path[1] = start_j;
    int additions_ways[] = {-1, 0, 0, 1, 1, 0, 0, -1};
    while(check_free_path(lab, actual_size, path, &path_size) && rooms_count != 0) {
        int i = path[(path_size - 1) * 2];
        int j = path[(path_size - 1) * 2 + 1];
        while(check_all_ways(lab, actual_size, i, j)) {
            int way = gen_num(0, 3);
            //int second_way = -1;

            check_target_cells(lab, actual_size, i, j, &way);
            while(!check_room(lab, actual_size, i, j, way)) {
                way = gen_num(0, 3);
            }

           // printf("%d\n", way);

            /*
            if (second_way != -1) {
                int new_i = i + additions_ways[second_way * 2];
                int new_j = j + additions_ways[second_way * 2 + 1];
                rooms_count--;
                lab[INDX(new_i, new_j, actual_size)] = 1;
            }
            */

            i += additions_ways[way * 2];
            j += additions_ways[way * 2 + 1];
            if (lab[INDX(i, j, actual_size)] == 2) {
                rooms_count--;
            }
            lab[INDX(i, j, actual_size)] = 1;
            path[path_size*2] = i;
            path[path_size*2 + 1] = j;
            path_size++;

            //print_lab(lab, actual_size);
            //printf("\n");
        }
    }

    print_lab(lab, actual_size);

    free(lab);
    return 0;
}