#ifndef MAIN_H
#define MAIN_H




/**
 * struct data - contains all relevant shell data on runtime
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
} shell_data_t;


/**
 * var_listPtr - Typedef for var_list node
 */

typedef struct var_list *var_listPtr;

/**
 * struct var_list - single linked list
 * 
 * @var_len: length of the variable
 * @value: variable value
 * @value_len: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */

typedef struct var_list
{
	int var_len;
	char *value;
	int value_len;
	var_listPtr next;
} var_list_t;


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

/* handle variable replacements */
int check_for_variables(var_list_t **head, char *s, char *status, shell_data_t *data);
void check_environ(var_list_t **head, char *s, shell_data_t *data);

/* handle comments */
char *handle_comment(char *s);
#endif
