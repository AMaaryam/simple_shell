#include "shell.h"

/**
 * print_al - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_al(data_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->al_list)
	{
		alias_length = string_length(alias);
		for (i = 0; data->al_list[i]; i++)
		{
			if (!alias || (str_comp(data->al_list[i], alias, alias_length)
				&&	data->al_list[i][alias_length] == '='))
			{
				for (j = 0; data->al_list[i][j]; j++)
				{
					buffer[j] = data->al_list[i][j];
					if (data->al_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buf_add(buffer, "'");
				buf_add(buffer, data->al_list[i] + j + 1);
				buf_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_al - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_al(data_program *data, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || data->al_list == NULL)
		return (NULL);

	alias_length = string_length(name);

	for (i = 0; data->al_list[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_comp(name, data->al_list[i], alias_length) &&
			data->al_list[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->al_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_al - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_al(char *alias_string, data_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->al_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_al(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->al
_list[j]; j++)
		if (str_comp(buffer, data->al_list[j], i) &&
			data->al_list[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->al_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buf_add(buffer, "=");
		buf_add(buffer, temp);
		data->al_list[j] = string_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->al_list[j] = string_duplicate(alias_string);
	return (0);
}
