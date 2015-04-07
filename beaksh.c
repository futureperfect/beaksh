#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "linenoise.h"

char* findPrompt();
void executeCommand(const char *text);

int main() {
  int childPid;
  int child_status;
  char *line;
  char *prompt;

  prompt = findPrompt();

  while((line = linenoise(prompt)) != NULL) {
    if (line[0] != '\0') {
      linenoiseHistoryAdd(line);
      childPid = fork();
      if(childPid == 0) {
        executeCommand(line);
      } else {
        wait(&child_status);
      }
    }
    free(line);
  }
  return 0;
}

char*  findPrompt() {
  return "$ ";
}

void executeCommand(const char *text) {
  execlp(text, text, NULL);
}
