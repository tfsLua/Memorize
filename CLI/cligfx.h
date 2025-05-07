#ifndef CLIGFX_H
#define CLIGFX_H

#include <stdio.h>

#define FG_BLACK   30
#define FG_RED     31
#define FG_GREEN   32
#define FG_YELLOW  33
#define FG_BLUE    34
#define FG_MAGENTA 35
#define FG_CYAN    36
#define FG_WHITE   37

static void clearScreen() {
    printf("\033[2J\033[H");
}

static void setFgColor(int color) {
    printf("\033[%dm", color);
}

static void resetColors() {
    printf("\033[0m");
}

#endif
