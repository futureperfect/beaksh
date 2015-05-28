#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include "linenoise.h"

#define HISTORY_FILE ".beaksh_history"

char* findPrompt();
char* getHistoryPath();
void executeCommand(const char *text);

int main() {
  int childPid;
  int child_status;
  char *line;
  char *prompt;

  prompt = findPrompt();

  char *historyPath = getHistoryPath();
  linenoiseHistoryLoad(historyPath);

  while((line = linenoise(prompt)) != NULL) {
    if (line[0] != '\0') {
      linenoiseHistoryAdd(line);
      linenoiseHistorySave(historyPath);
      childPid = fork();
      if(childPid == 0) {
        executeCommand(line);
      } else {
        wait(&child_status);
      }
    }
    free(line);
  }

  if(historyPath)
    free(historyPath);

  return EXIT_SUCCESS;
}

char*  findPrompt() {
  return "$ ";
}

/*
  Resolve dotfile path for history. Returns NULL if file can't be resolved.
*/
char* getHistoryPath() {
  char *home = getenv("HOME");

  if(!home)
    return NULL;

  int home_path_len = strnlen(home, MAXPATHLEN);
  int history_path_len = home_path_len + strlen(HISTORY_FILE) + 1;

  char *result;

  if((result = malloc(history_path_len + 1)) == NULL) {
    fprintf(stderr, "Problem resolving path for history file, no history will be recorded\n");
    return NULL;
  }

  strncpy(result, home, home_path_len);
  strncat(result, "/", 1);
  strncat(result, HISTORY_FILE, strlen(HISTORY_FILE));

  return result;
}

void executeCommand(const char *text) {
  execlp(text, text, NULL);
}
