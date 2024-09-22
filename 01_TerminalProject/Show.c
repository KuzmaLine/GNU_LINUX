#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <file.h>
#include <math.h>

#define DX 2
#define DY 2
// Коды для клавиш
#define UP 259
#define RIGHT 261
#define LEFT 260
#define DOWN_SPACE 32
#define DOWN_ARROW 258

// Граница, дальше которой двигать окно нельзя (с момента, когда текст закончился)
#define BOUNDARY 15

#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

// Структура для хранения текста нашего файла и записи его в рамку
struct FILE_TEXT {
    char **text;
    int lines_count;
    int max_str_length;
    long unsigned int *str_lengths;
    int line;
    int col;
};

// Чтение текста в массив строк
struct FILE_TEXT* read_file(char* filename) {
    FILE* fd = fopen(filename, "r");
    int cur_size = 16;
    struct FILE_TEXT* text = (struct FILE_TEXT*)malloc(sizeof(struct FILE_TEXT));
    text->line = 0;
    text->col = 0;
    text->max_str_length = 0;
    text->text = (char**)malloc(cur_size * sizeof(char*));
    text->str_lengths = (long unsigned int*)malloc(cur_size * sizeof(long unsigned int));

    long unsigned int readed_size;
    size_t str_size = 0;
    int index = 0;
    while ((readed_size = getline(&text->text[index], &str_size, fd)) != -1) {
        text->str_lengths[index] = readed_size;
        text->max_str_length = max(text->max_str_length, readed_size);
        text->lines_count++;

        if (index == cur_size) {
            cur_size *= 2;
            text->text = (char**)realloc(text->text, cur_size * sizeof(char*));
            text->str_lengths = (long unsigned int*)realloc(text->str_lengths, cur_size * sizeof(long unsigned int));
        }

        index++;
    }

    fclose(fd);
    return text;
}

// Запись фрагмента текста в рамку со сдвигом
void write_file_text(WINDOW* win, struct FILE_TEXT* text, int key, int win_height, int win_width) {
    if (key == UP && text->line != 0) {
        text->line--;
    } else if (key == RIGHT && text->col + win_width < max(text->max_str_length, win_width) + BOUNDARY) {
        text->col++;
    } else if (key == LEFT && text->col != 0) {
        text->col--;
    } else if ((key == DOWN_SPACE || key == DOWN_ARROW) && (text->line + win_height) < max(text->lines_count, win_height) + BOUNDARY) {
        text->line++;
    }

    for (int i = 0; i < win_height; i++) {
        if ((text->line + i) < text->lines_count && text->col < text->str_lengths[i + text->line]) {
            mvwaddnstr(win, i, 0, text->text[i + text->line] + text->col, min(win_width, text->str_lengths[i + text->line] - text->col));
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("File is not given!\n");
        return 0;
    }

    struct FILE_TEXT* file_text = read_file(argv[1]);

    WINDOW *frame, *win;
    int c = 0;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw("FILE: %s\n", argv[1]);
    refresh();

    frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
    box(frame, 0, 0);
    wrefresh(frame);

    int win_width = COLS - 2*DX-2;
    int win_height = LINES - 2*DY-2;
    win = newwin(win_height, win_width, DY+1, DX+1);

    keypad(win, TRUE);
    scrollok(win, TRUE);
    write_file_text(win, file_text, -1, win_height, win_width);
    wrefresh(win);

    while((c = wgetch(win)) != 27) {
        werase(win);
        write_file_text(win, file_text, c, win_height, win_width);
        wrefresh(win);
    }

    for (int i = 0; i < file_text->lines_count; i++) {
        free(file_text->text[i]);
    }

    free(file_text->text);
    free(file_text);

    delwin(win);
    delwin(frame);
    endwin();
    return 0;
}