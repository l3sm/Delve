#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Borrowed snippet to prevent having to press Enter each time:
//----------------------------------------------------------------------------------
struct termios originalTerminal;

// This function restores the terminal settings we saved earlier.
// atexit() will automatically call this when main ends normally.
void restoreTerminal(void) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminal);
}

// Configure the terminal so getchar() receives a single key immediately,
// instead of waiting for the user to press Enter.
void enableImmediateInput(void) {
  // This will become our changed copy of the original terminal settings.
  struct termios gameTerminal;

  // Read and save the terminal's current settings.
  tcgetattr(STDIN_FILENO, &originalTerminal);

  // On a normal exit, automatically restore the saved terminal settings.
  atexit(restoreTerminal);

  // Start from the normal terminal settings rather than inventing all settings.
  gameTerminal = originalTerminal;

  // Turn off:
  // ICANON = canonical/line mode, which waits for Enter.
  // ECHO   = terminal automatically printing each pressed key.
  gameTerminal.c_lflag &= ~(ICANON | ECHO);

  // Wait until at least one character is available before getchar() continues.
  gameTerminal.c_cc[VMIN] = 1;

  // Do not use a timeout while waiting for input.
  gameTerminal.c_cc[VTIME] = 0;

  // Apply our game-specific terminal settings.
  // TCSAFLUSH also discards any input that was typed before this setting
  // applied.
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &gameTerminal);
}
//------------------------------------------------------------------------------------------
// End of borrowed code snippet.
