#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

// Restores the terminal settings saved before immediate-input mode began.
void restoreTerminal(void);

// Configures the terminal so getchar() receives a key immediately,
// instead of waiting for Enter.
void enableImmediateInput(void);

#endif
