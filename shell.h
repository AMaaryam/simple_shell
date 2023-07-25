#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
/*********** THE MACROS ************/
#include "macros.h" 
/*********** THE MAINSTRUCTURES ************/

/**
 * struct info-  the main struct for the program data
 * @program_name: name of the executable
 * @input_line: the pointer to the input read for _getlin
 * @command_name: the pointer to the first command typed by the user
 * @exec_counter: the number of excecuted comands
 * @file_descriptor: main file descriptor to the input of commands
 * @tokens: main pointer to array of tokenized input
 * @env:  the copy of the environ
 * @alias_list: an array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_programm;


/**
 * struct builtins - the mainstruct for the builtins.
 * @builtin:  name of the builtin.
 * @function:  associated function to be called for each builtin.
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_programm *data);
} builtins;


/*********** THE  MAIN FUNCTIONS ***********/



void init_data(data_of_programm *data, int arc, char *argv[], char **env);

void loop_prpmpt(char *prompt, data_of_programm *data);

void handle_ctrlc(int opr UNUSED);


int _getlin(data_of_programm *data);

int check_ops(char *array_comnd[], int i, char array_op[]);


void variable_expension(data_of_programm *data);

void alias_expension(data_of_programm *data);

int buffer_adding(char *buffer, char *str_to_add);



void tokenizeing(data_of_programm *data);

char *_stringtok(char *line, char *delim);



int executeer(data_of_programm *data);


int builtin_lists(data_of_programm *data);


char **tokenizing_path(data_of_programm *data);

int find_programm(data_of_programm *data);


/************ THe HELPERS FOR MEMORY MGMNT ************/


void free_array_pointers(char **directories);

void free_the_data(data_of_programm *data);

void free_all_the_data(data_of_programm *data);


/************ BUILTINS ************/

int builtin_exxit(data_of_programm *data);

int builtinn_cd(data_of_programm *data);

int set_working_directory(data_of_programm *data, char *new_dir);

int builtin_helper(data_of_programm *data);

int builtinns_alias(data_of_programm *data);


int builtins_env(data_of_programm *data);

int builtins_sett_env(data_of_programm *data);

int builtin_unset_env(data_of_programm *data);


/************ THE HELPERS FOR ENVIRONMENT VAR MANAGEMENT ************/

char *env_getin_key(char *name, data_of_programm *data);

int envrmnt_set_key(char *key, char *value, data_of_programm *data);

int env_remove_key(char *key, data_of_programm *data);

void print_envrmt(data_of_programm *data);


/************** THE HELPERS FOR PRINTING **************/

int _print(char *string);

int _printe_(char *string);

int _print_eror(int errorcode, data_of_programm *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/

int str_leng(char *string);

char *str_dupl(char *string);

int string_compare(char *string1, char *string2, int number);

char *str_concating(char *string1, char *string2);

void str_rev(char *string);

void numb_to_string(long number, char *string, int base);

int str_int(char *s);

int counter_char(char *string, char *character);

int p_alias(data_of_programm *data, char *alias);

char *bring_alias(data_of_programm *data, char *alias);

int seting_alias(char *alias_string, data_of_programm *data);

#endif
