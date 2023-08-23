#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/types.h>
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
 * @line_string: string
 * @next: next node of linked list
 * Description: single linked list that stores command lines (strings)
 */
typedef struct lineList
{
	char *line_string;
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


/**
 * struct builtin - struct for command arguments.
 *
 * @name: name of the command builtin i.e cd, exit, env
 * @f: pointer to function.
 */
typedef struct builtin
{
	char *name;
	int (*f)(data_t *data);
} builtin_t;


/* main functions */
void get_sigint(int sign);
int (*get_builtin(char *command))(data_t *data);
void loop_shell_prompt(data_t *data);



/* data functions */
void set_data(data_t *data, char **argv);
void free_data(data_t *data);


/*  string functions  */
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strspn(char *s, char *accept);
char *_strdup(char *s);
void rev_string(char *s);
char *_itoa(int n);
int _isdigit(char *s);
int strcmp_to_delim(char *str, char *delim);


/* memory functions */
void _memcpy(void *dest, void *src, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **old, unsigned int old_size, unsigned int new_size);



/* env functions */
int cmpenv(const char *env_name, const char *name);
char *cpyinfo(char *name, char *value);


/* line functions */
line_list *add_line_nodeend(line_list **head, char *line_string);
void free_line_list(line_list **head);


/* separator functions */
sep_list *add_sep_nodeend(sep_list **head, char separator);
void free_sep_list(sep_list **head);


/* variable functions */
var_list *add_var_node(var_list **head, int varLen, char *value, int valueLen);
void free_var_list(var_list **head);
char *replace(var_list **head, char *s, char *new_s, int len);
char *replace_var(char *s, data_t *data);


/* error functions */
char *env_error(data_t *data);
char *path_error(data_t *data);
char *cd_error(data_t *data);
char *exit_error(data_t *data);
char *error_404(data_t *data);
int syntax_error(char *s, int idx, char last);
char *strcat_cd_error(data_t *data, char *msg, char *error, char *lines);
int get_error(data_t *data, int error_val);


/* help functions */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);
void help(void);
void help_alias(void);
void help_cd(void);
int get_help(data_t *data);


/* execute */
int is_executable(data_t *data);
int execute(data_t *data);


/* handle arguments */
int char_repetitions(char *s, int idx);
int first_char_index(char *s, int *idx);
void print_syntax_error(data_t *data, char *s, int idx, int boolean);
int check_syntax(data_t *data, char *s);


/* handle path */
char *_which(char *command, char **_environ);
int is_current_dir(char *path, int *i);
int check_permissions(char *directory, data_t *data);


/* handle exit */
int _exitsh(data_t *data);


/* handle env */
int _env(data_t *data);
char *get_env(const char *env_name, char **_environ);


/* get line */
void _line(char **line, size_t *line_size, char *buffer, size_t buf_size);
ssize_t _getline(char **line, size_t *line_size, FILE *stream);
char *_readline(int *i);


/* handle lib functions */
char *_strtok(char *str, char *delim);
int _getlen(int n);
int _atoi(char *s);


/* handle setenv unsetenv */
void _setenv(char *name, char *value, data_t *data);
int cmp_setenv(data_t *data);
int _unsetenv(data_t *data);


/* handle cd (change directory operations) */
void cd_parent(data_t *data);
void cd_dir(data_t *data);
void cd_back(data_t *data);
void cd_home(data_t *data);
int cd_current(data_t *data);


/* handle separators */
void add_nodes(sep_list **head_sep, line_list **head_line, char *s);
void next_line(sep_list **node_sep, line_list **node_line, data_t *data);
int split_command_lines(data_t *data, char *s);
char **tokenize_line(char *s);
int execute_line(data_t *data);


/* switches non logical '|' and '&' for non-printed characters */
char *swap_non_ops(char *s, int type);


/* handle variable replacements */
int check_for_vars(var_list **head, char *s, char *status, data_t *data);
void check_for_env(var_list **head, char *s, data_t *data);


/* handle comments */
char *handle_comment(char *s);
#endif
