#include "shell.h"

/**
 * builtin_environement - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_environement(data_program *data)
{
	int i;
	char cp_name[50] = {'\0'};
	char *variable_cop = NULL;

	/* if not arguments */
	if (data->tknz[1] == NULL)
		print_environement(data);
	else
	{
		for (i = 0; data->tknz[1][i]; i++)
		{/* checks if exists a char = */
			if (data->tknz[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				variable_cop = string_duplicate(env_getkey(cp_name, data));
				if (variable_cop != NULL)
					env_setkey(cp_name, data->tknz[1] + i + 1, data);

				/* print the environ */
				print_environement(data);
				if (env_getkey(cp_name, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tknz[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_setkey(cp_name, variable_cop, data);
					free(variable_cop);
				}
				return (0);
			}
			cp_name[i] = data->tknz[1][i];
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_setenv - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_setenv(data_program *data)
{
	/* validate args */
	if (data->tknz[1] == NULL || data->tknz[2] == NULL)
		return (0);
	if (data->tknz[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	env_setkey(data->tknz[1], data->tknz[2], data);

	return (0);
}

/**
 * builtin_unset_environ - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int builtin_unset_environ(data_program *data)
{
	/* validate args */
	if (data->tknz[1] == NULL)
		return (0);
	if (data->tknz[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	env_rmv_key(data->tknz[1], data);

	return (0);
}
