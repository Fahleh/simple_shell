#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>


#define BUFFER_SIZE 1024
#define INPUT_BUFFER 128
#define DELIM " \t\n"

/* MAIN FUNCTIONS */
void _prompt(void);
void read_cmd(char **cmd);
void executeCommand(char *cmd, char **av, char **env);


/* BUILT_IN FUNCTION */
char *_getPath(char *command);
void _fork(char *path, char **args, char **av, char **env);
void _printEnv(char **env);
int _setEnv(const char *var, const char *val);
int _unsetEnv(const char *var);



/* CUSTOM FUNCTIONS */
void _printf(const char *fmt, ...);
void _handleSignal(int sig);
ssize_t _getLine(char **line, size_t *s, FILE *stream);
char *_strTok(char *str, const char *delim);
void _exitCmd(char **args, char **av, char *cmd);


/* HELPER FUNCTIONS */
void _tokenize(char *cmd, char **args);
void _freedptr(char **args);
bool _testCommand(char *path);
char **_readFLines(FILE *file);
int _checkKeyword(char **args, char *cmd, char **av, char **env);


#endif
