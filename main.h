#ifndef MAIN_H
#define MAIN_H

#define BUFSIZE 1024
#define TOKEN_BUFSIZE 128
#define TOKEN_DELIMITERS " \t\r\n\a"

/* environ - pointer to an array of strings */
extern char **environ;


/**
 * line_listPtr - Typedef for struct lineList
 */
typedef struct lineList *line_listPtr;

/**
 * struct lineList - single linked list
 *
 * @line: string
 * @next: next node of linked list
 * Description: single linked list that stores command lines (strings)
 */
typedef struct lineList
{
	char *line;
	line_listPtr next;
} line_list;


/**
 * sep_listPtr - Typedef for struct sepList
 */
typedef struct sepList *sep_listPtr;

/**
 * struct sepList - single linked list
 *
 * @separator: can be ';', '|' or '&'
 * @next: next node of list
 * Description: single linked list that stores separators
 */
typedef struct sepList
{
	char separator;
	sep_listPtr next;
} sep_list;


/**
 * struct shell_data - contains all relevant shell data on runtime
 *
 * @argv: argument vector
 * @user_input: command line user input
 * @tokens: command line tokens
 * @status: last status of the shell
 * @counter: counts lines
 * @_environ: environment variable
 * @pid: current process ID of the shell
 */

typedef struct shell_data
{
	char **argv;
	char *user_input;
	char **tokens;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_t;


/**
 * var_listPtr - Typedef for struct varList
 */
typedef struct varList *var_listPtr;

/**
 * struct varList - single linked list
 *
 * @var_len: length of the variable
 * @value: variable value
 * @value_len: length of the value
 * @next: next node of list
 * Description: single linked list that stores variables
 */

typedef struct varList
{
	int var_len;
	char *value;
	int value_len;
	var_listPtr next;
} var_list;


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


/* separator functions */
sep_list *add_sep_nodeend(sep_list **head, char separator);
void free_sep_list(sep_list **head);


/* variable functions */
var_list *add_var_node(var_list **head, int varLen, char *value, int valueLen);
void free_var_list(var_list **head);


/* switches non logical '|' and '&' for non-printed characters */
char *swap_non_ops(char *s, int type);


/* handle variable replacements */
int check_for_vars(var_list **head, char *s, char *status, data_t *data);
void check_for_env(var_list **head, char *s, data_t *data);


/* handle comments */
char *handle_comment(char *s);
#endif
