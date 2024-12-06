#include "terminal_manager.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

void TerminalManager::clearScreen() {
    std::cout << "\033[2J\033[H";
}

int TerminalManager::getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int TerminalManager::getTerminalHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}