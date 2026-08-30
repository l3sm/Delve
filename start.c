#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char rockBuffer[100] = "\033[90mR\033[0m";
  char *rock = strdup(rockBuffer);
  // So instead of using malloc to strlen of rockbuffer+1 I opted for this
  // strdup method that does the exact same. It also copies the contents of
  // rockbuffer to the place in memory pointed by rock. So now rock points to
  // the gray R.
  char *rockArr[20][50];
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 50; j++) {
      rockArr[i][j] = rock;
      printf("%s", rockArr[i][j]);
    }
    printf("\n");
  }
  free(rock);
  rock = NULL;
  return 0;
}
