#pragma once

void drawLetters(WINDOW *window);

void drawWord(WINDOW *window, char word[]);

void highlightLetter(WINDOW *window, char buffer);

void drawMan(WINDOW *window, int level);

void drawHang(WINDOW *window);

void drawScreenEffectLose(WINDOW *window, char word[]);

void drawScreenEffectWin(WINDOW *window);

void drawTitle(WINDOW *window);