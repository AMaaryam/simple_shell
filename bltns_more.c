#include "shell.h"

/**
 * builtin_exiting - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exiting(data_program *data)
{
	int i;

	if (data->tknz[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (i = 0; data->tknz[1][i]; i++)
			if ((data->tknz[1][i] < '0' || data->tknz[1][i] > '9')
				&& data->tknz[1][i] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tknz[1]);
	}
	free_data(data);
	exit(errno);
}

/**
 * builtin_cdir - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cdir(data_program *data)
{
	char *directory_home = env_getkey("HOME", data), *dir_old = NULL;
	char old_directory[128] = {0};
	int error_code = 0;

	if (data->tknz[1])
	{
		if (str_comp(data->tknz[1], "-", 0))
		{
			dir_old = env_getkey("OLDPWD", data);
			if (dir_old)
				error_code = set_work_dir(data, dir_old);
			_print(env_getkey("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_dir(data, data->tknz[1]));
		}
	}
	else
	{
		if (!directory_home)
			directory_home = getcwd(old_directory, 128);

		return (set_work_dir(data, directory_home));
	}
	return (0);
}

/**
 * set_work_dir - set the work directory
 * @data: struct for the program's data
 * @new_directory: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_work_dir(data_program *data, char *new_directory)
{
	char old_directory[128] = {0};
	int error_code = 0;

	getcwd(old_directory, 128);

	if (!str_comp(old_directory, new_directory, 0))
	{
		error_code = chdir(new_directory);
		if (error_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_setkey("PWD", new_directory, data);
	}
	env_setkey("OLDPWD", old_directory, data);
	return (0);
}

/**
 * builtin_hlp - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_hlp(data_program *data)
{
	int i, length = 0;
	char *msg[6] = {NULL};

	msg[0] = HELP_MSG;

	/* validate args */
	if (data->tknz[1] == NULL)
	{
		_print(msg[0] + 6);
		return (1);
	}
	if (data->tknz[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	msg[1] = HELP_EXIT_MSG;
	msg[2] = HELP_ENV_MSG;
	msg[3] = HELP_SETENV_MSG;
	msg[4] = HELP_UNSETENV_MSG;
	msg[5] = HELP_CD_MSG;

	for (i = 0; msg[i]; i++)
	{
		/*print the length of string */
		length = string_length(data->tknz[1]);
		if (str_comp(data->tknz[1], msg[i], length))
		{
			_print(msg[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * builtin_al - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_al(data_program *data)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (data->tknz[1] == NULL)
		return (print_al(data, NULL));

	while (data->tknz[++i])
	{/* if there are arguments, set or print each environ variable*/
		if (cnt_characters(data->tknz[i], "="))
			set_al(data->tknz[i], data);
		else
			print_al(data, data->tknz[i]);
	}

	return (0);
}
