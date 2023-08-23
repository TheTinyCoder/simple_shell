#ifndef MAIN_H
#define MAIN_H
/*  string functions  */

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);

int _strlen(char *s);
int _strspn(char *s, char *accept);
char *_strdup(char *s);
void rev_string(char *s);

char *_strtok(char *str, char *delim);
int _isdigit(char *s);
int strcmp_to_delim(char *str, char *delim);

/* memory functions */
void _memcpy(void *dest, void *src, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


/* switches non logical '|' and '&' for non-printed characters */
char *swap_non_ops(char *s, int type);

/* handle comments */
char *handle_comment(char *s);
#endif
