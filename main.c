#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "draw.h"

#define TERMINAL_H 24
#define TERMINAL_W 80
#define TEXTCOLOR COLOR_CYAN
#define BACKGROUNDCOLOR COLOR_BLACK
#define FILE_ENTRIES 50
#define WRONGANSWERS 8

void initCurses() {
    initscr();
    cbreak();
    noecho();
    start_color();
    init_pair(1, TEXTCOLOR, BACKGROUNDCOLOR); // default colors
    init_pair(2, COLOR_RED, BACKGROUNDCOLOR); // red head
    init_pair(10, COLOR_BLACK, COLOR_CYAN); // win
    init_pair(11, COLOR_BLACK, COLOR_RED); // lose
    curs_set(0);
}
int initStartPage() {
    WINDOW *startPage = newwin(TERMINAL_H, TERMINAL_W, 0, 0);
    drawTitle(startPage);
    wattron(startPage, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(startPage, 8, 5, "Choose the category from which you would like to receive a word from:");
    mvwprintw(startPage, 10, 33, "1. Animals");
    mvwprintw(startPage, 11, 33, "2. Plants");
    mvwprintw(startPage, 12, 33, "3. Countries");
    mvwprintw(startPage, 13, 33, "4. Names");
    mvwprintw(startPage, 15, 30, "=Type your option= ");
    wrefresh(startPage);
    int buffer;
    do {
        buffer = wgetch(startPage);
    }
    while(buffer < '1' || buffer > '4');
    wattroff(startPage, COLOR_PAIR(1) | A_BOLD);
    delwin(startPage);
    return buffer - '0';
}
char *pickWord(char fileName[]) {
    char *word = malloc(50 * sizeof(char));
    srand(time(0));
    int randomInt = rand() % FILE_ENTRIES + 1;
    FILE *file = fopen(fileName, "rt");
    for(int i = 0; i < randomInt; i++) {
        fgets(word, 50, file);
    }
    fclose(file);
    word[strlen(word) - 1] = '\0';
    return word;
}
char *createWord(int option) {
    switch (option) {
        case 1:
            return pickWord("text files/animals.txt");
        case 2:
            return pickWord("text files/plants.txt");
        case 3:
            return pickWord("text files/countries.txt");
        case 4:
            return pickWord("text files/names.txt");
    }
}
void initGamePage(char word[]) {
    WINDOW *gamePage = newwin(TERMINAL_H, TERMINAL_W, 0, 0);
    drawTitle(gamePage);
    drawLetters(gamePage);
    drawHang(gamePage);
    char *wordCopy = malloc((strlen(word) + 1) * sizeof(char));
    for(int i = 0; i < strlen(word); i++) {
        if(word[i] == ' ') {
            wordCopy[i] = ' ';
        } else {
            wordCopy[i] = '-';
        }
    }
    wordCopy[strlen(word)] = '\0';
    int failedAttempts = 0;
    int solved = 0;
    while(failedAttempts < WRONGANSWERS && solved == 0) {
        drawWord(gamePage, wordCopy);
        char buffer = wgetch(gamePage);
        if(buffer >= 'a' && buffer <= 'z') {
            highlightLetter(gamePage, buffer);
            int modified = 0;
            for(int i = 0; i < strlen(word); i++) {
                if(word[i] == buffer || word[i] == buffer - 32) {
                    wordCopy[i] = word[i];
                    modified = 1;
                }
            }
            if(modified == 0) {
                failedAttempts++;
                drawMan(gamePage, failedAttempts);
            }
            if(strcmp(word, wordCopy) == 0) {
                solved = 1;
                drawWord(gamePage, wordCopy);
            }
        }
    }
    if(failedAttempts == WRONGANSWERS) {
        drawMan(gamePage, failedAttempts);
        drawScreenEffectLose(gamePage, word);
    }
    if(solved == 1) {
        drawScreenEffectWin(gamePage);
    }
    wgetch(gamePage);
    delwin(gamePage);
    free(word);
    free(wordCopy);
}
int main() {
    initCurses();
    int option = initStartPage();
    initGamePage(createWord(option));
    endwin();
    return 0;
}
