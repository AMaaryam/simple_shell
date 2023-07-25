#include "shell.h"

/**
 * bltns_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int bltns_list(data_of_program *data)
{
	int iterator;
	bltns options[] = {
		{"exit", builtin_exiting},
		{"help", builtin_hlp},
		{"cd", builtin_cdir},
		{"alias", builtin_al},
		{"environ", builtin_environement},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unset_environ},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (itera = 0; options[itera].nbuiltin != NULL; itera++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_comp(options[itera].nbuiltin, data->cmd_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[itera].fonction(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
