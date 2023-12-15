#ifndef MAIN_H
#define MAIN_H

extern char **environ;
int custom_setenv(const char *name, const char *value, int overwrite);
int custom_cd(const char *directory);

#endif /* MAIN_H */

