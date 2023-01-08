#include <ncurses.h>
#include <string.h>

#include "draw.h"

void drawTitle(WINDOW *window) {
    wattron(window, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(window, 0, 13, "    __  __ ___     _   __ ______ __  ___ ___     _   __");
    mvwprintw(window, 1, 13, "   / / / //   |   / | / // ____//  |/  //   |   / | / /");
    mvwprintw(window, 2, 13, "  / /_/ // /| |  /  |/ // / __ / /|_/ // /| |  /  |/ /");
    mvwprintw(window, 3, 13, " / __  // ___ | / /|  // /_/ // /  / // ___ | / /|  /");
    mvwprintw(window, 4, 13, "/_/ /_//_/  |_|/_/ |_/ \\____//_/  /_//_/  |_|/_/ |_/");
    wattroff(window, COLOR_PAIR(1) | A_BOLD);
    wrefresh(window);
}
void drawLetters(WINDOW *window) {
    int row, col;
    getmaxyx(window, row, col);
    wattron(window, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(window, 9, 50, "Letters");
    char buffer = 'A';
    for(int i = 0; i < 4; i += 2) {
        for(int j = 0; j < 26; j += 2) {
            mvwprintw(window, 11 + i, 42 + j, "%c", buffer++);
        }
    }
    wattroff(window, COLOR_PAIR(1) | A_BOLD);
    wrefresh(window);
}
void highlightLetter(WINDOW *window, char buffer) {
    wattron(window, COLOR_PAIR(1) | A_UNDERLINE | A_BOLD);
    if(buffer == 'a') {
        mvwprintw(window, 11, 42, "A");
    } else if(buffer == 'b') {
        mvwprintw(window, 11, 44, "B");
    } else if(buffer == 'c') {
        mvwprintw(window, 11, 46, "C");
    } else if(buffer == 'd') {
        mvwprintw(window, 11, 48, "D");
    } else if(buffer == 'e') {
        mvwprintw(window, 11, 50, "E");
    } else if(buffer == 'f') {
        mvwprintw(window, 11, 52, "F");
    } else if(buffer == 'g') {
        mvwprintw(window, 11, 54, "G");
    } else if(buffer == 'h') {
        mvwprintw(window, 11, 56, "H");
    } else if(buffer == 'i') {
        mvwprintw(window, 11, 58, "I");
    } else if(buffer == 'j') {
        mvwprintw(window, 11, 60, "J");
    } else if(buffer == 'k') {
        mvwprintw(window, 11, 62, "K");
    } else if(buffer == 'l') {
        mvwprintw(window, 11, 64, "L");
    } else if(buffer == 'm') {
        mvwprintw(window, 11, 66, "M");
    } else if(buffer == 'n') {
        mvwprintw(window, 13, 42, "N");
    } else if(buffer == 'o') {
        mvwprintw(window, 13, 44, "O");
    } else if(buffer == 'p') {
        mvwprintw(window, 13, 46, "P");
    } else if(buffer == 'q') {
        mvwprintw(window, 13, 48, "Q");
    } else if(buffer == 'r') {
        mvwprintw(window, 13, 50, "R");
    } else if(buffer == 's') {
        mvwprintw(window, 13, 52, "S");
    } else if(buffer == 't') {
        mvwprintw(window, 13, 54, "T");
    } else if(buffer == 'u') {
        mvwprintw(window, 13, 56, "U");
    } else if(buffer == 'v') {
        mvwprintw(window, 13, 58, "V");
    } else if(buffer == 'w') {
        mvwprintw(window, 13, 60, "W");
    } else if(buffer == 'x') {
        mvwprintw(window, 13, 62, "X");
    } else if(buffer == 'y') {
        mvwprintw(window, 13, 64, "Y");
    } else if(buffer == 'z') {
        mvwprintw(window, 13, 66, "Z");
    }
    wattroff(window, COLOR_PAIR(1) | A_UNDERLINE | A_BOLD);
    wrefresh(window);
}
void drawWord(WINDOW *window, char word[]) {
    int row, col;
    getmaxyx(window, row, col);
    wattron(window, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(window, row - 4, 13, "Word: ");
    wprintw(window, "%s", word);
    wattroff(window, COLOR_PAIR(1) | A_BOLD);
    wrefresh(window);
}
void drawHang(WINDOW *window) {
    wattron(window, COLOR_PAIR(1) | A_BOLD);
    wmove(window, 8, 14);
    for(int i = 0; i < 4; i++) {
        wprintw(window, "_");
    }
    for(int i = 0; i < 6; i++) {
        mvwprintw(window, 9 + i, 14, "|");
    }
    wprintw(window, "_");
    mvwprintw(window, 14, 13, "_");
    wattroff(window, COLOR_PAIR(1) | A_BOLD);
    wrefresh(window);
}
void drawMan(WINDOW *window, int level) {
    wattron(window, COLOR_PAIR(1) | A_BOLD);
    switch (level) {
        case 1:
            mvwprintw(window, 10, 17, "O");
            break;
        case 2:
            mvwprintw(window, 11, 17, "|");
            break;
        case 3:
            mvwprintw(window, 12, 17, "|");
            break;
        case 4:
            mvwprintw(window, 11, 16, "/");
            break;
        case 5:
            mvwprintw(window, 11, 18, "\\");
            break;
        case 6:
            mvwprintw(window, 13, 16, "/");
            break;
        case 7:
            mvwprintw(window, 13, 18, "\\");
            break;
        case 8:
            mvwprintw(window, 9, 17, "|");
            wattron(window, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(window, 10, 17, "O");
            wattroff(window, COLOR_PAIR(2) | A_BOLD);
            break;
    }
    wattroff(window, COLOR_PAIR(1) | A_BOLD);
    wrefresh(window);
}
void drawScreenEffectLose(WINDOW *window, char word[]) {
    int row, col;
    getmaxyx(window, row, col);
    wattron(window, COLOR_PAIR(11));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mvwprintw(window, i, j, " ");
            wrefresh(window);
            napms(0.1);
        }
    }
    int middlecol = col / 2 - (strlen(word) + 13) / 2;
    mvwprintw(window, 9, middlecol, "The word was %s", word);
    wattroff(window, COLOR_PAIR(11));
    wrefresh(window);
}
void drawScreenEffectWin(WINDOW *window) {
    int row, col;
    getmaxyx(window, row, col);
    wattron(window, COLOR_PAIR(10));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mvwprintw(window, i, j, " ");
            wrefresh(window);
            napms(0.1);
        }
    }
    int middlecol = col / 2 - 14;
    mvwprintw(window, 9, middlecol, "You saved the little man! :D");
    wattroff(window, COLOR_PAIR(10));
    wrefresh(window);
}
