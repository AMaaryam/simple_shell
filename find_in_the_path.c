#include "shell.h"

int checker_file(char *full_path);


/**
 * find_programm - a function that find a program in path
 *
 * @data: a pointer to the program's data
 *
 * Return: 0 if success error otherwise.
 */


int find_programm(data_of_programm *data)
{
	int i = 0, re_code = 0;
	char **direct;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (cchecker_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	direct = tokenizing_path(data);

	if (!direct || !direct[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; direct[i]; i++)
	{
		direct[i] = str_concat(direct[i], data->tokens[0]);
		re_code = checker_file(direct[i]);
		if (re_code == 0 || re_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(direct[i]);
			free_array_of_pointers(direct);
			return (re_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(direct);
	return (re_code);
}


/**
 * tokenizing_path - a function that tokenizes the path of direc.
 *
 * @data: the pointer to program data.
 *
 * Return: the path directories.
 */

char **tokenizing_path(data_of_programm *data)
{
	int i = 0;
	int count_dirc = 2;
	char **tkn = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirc++;
	}

	tkn = malloc(sizeof(char *) * count_dirc);
	i = 0;
	tkn[i] = str_duplicate(_strtok(PATH, ":"));

	while (tkn[i++])
	{
		tkn[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tkn);
}


/**
 * checker_file -  afunction that checks if exists file or not a dairectory
 *                 if it has excecution permisions for permisions.
 *
 * @full_path: the main pointer to full file name.
 *
 * Return: 0 on success or error otherwise.
 */


int checker_file(char *full_path)
{
	struct stat ssb;

	if (stat(full_path, &ssb) != -1)
	{
		if (S_ISDIR(ssb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
