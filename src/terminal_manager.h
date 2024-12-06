#ifndef TERMINAL_MANAGER_H
#define TERMINAL_MANAGER_H

class TerminalManager {
public:
    static void clearScreen();
    static int getTerminalWidth();
    static int getTerminalHeight();
};

#endif // TERMINAL_MANAGER_H