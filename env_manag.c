#include "shell.h"

/**
 * 
env_getkey - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_getkey(char *key, data_of_program *data)
{
	int i, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->environ == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_len = string_length(key);

	for (i = 0; data->environ[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_comp(key, data->environ[i], key_len) &&
		 data->environ[i][key_len] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->envion[i] + key_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_setkey - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_setkey(char *key, char *value, data_of_program *data)
{
	int i, key_len = 0, new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->environ == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_len = string_length(key);

	for (i = 0; data->environ[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_comp(key, data->environ[i], key_len) &&
		 data->environ[i][key_len] == '=')
		{/* If key already exists */
			new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->environ[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->environ[i] = str_concat(string_duplicate(key), "=");
	data->environ[i] = str_concat(data->environ[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->environ[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_rmv_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_rmv_key(char *key, data_of_program *data)
{
	int i, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->environ
 == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_len = string_length(key);

	for (i = 0; data->environ[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_comp(key, data->environ[i], key_len) &&
		 data->environ[i][key_len] == '=')
		{/* if key already exists, remove them */
			free(data->environ[i]);

			/* move the others keys one position down */
			i++;
			for (; data->environ[i]; i++)
			{
				data->environ[i - 1] = data->environ[i];
			}
			/* put the NULL value at the new end of the list */
			data->environ[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environnement - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->environ[j]; j++)
	{
		_print(data->environ[j]);
		_print("\n");
	}
}
