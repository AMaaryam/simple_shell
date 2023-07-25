#include "shell.h"

/**
 * _print - functionn that writes arrays of char in the stdr output.
 *
 * @string: the pointer to the array of char.
 *
 * Return: numb of bytes writed, -1 on error.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_leng(string)));
}

/**
 * _printe_ - a function that writes array of char in standarerror.
 *
 * @string: the pointer to the array of char.
 *
 * Return: the numb of bytes writed or -1 otherwise.
 */

int _printe_(char *string)
{
	return (write(STDERR_FILENO, string, str_leng(string)));
}

/**
 * _print_eror -  function that writes an array of char
 *                in the standart error.
 *
 * @data: the main pointer to the program data.
 * @errorcode: the error code to print.
 *
 * Return: the number of bytes writed or -1 on error.
 */

int _print_eror(int errorcode, data_of_programm *data)
{
	char n_as_stg[10] = {'\0'};

	numb_to_string((long) data->exec_counter, n_as_stg, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe_(data->program_name);
		_printe_(": ");
		_printe_(n_as_stg);
		_printe_(": ");
		_printe_(data->tokens[0]);
		if (errorcode == 2)
			_printe_(": Illegal number: ");
		else
			_printe_(": can't cd to ");
		_printe_(data->tokens[1]);
		_printe_("\n");
	}
	else if (errorcode == 127)
	{
		_printe_(data->program_name);
		_printe_(": ");
		_printe_(n_as_stg);
		_printe_(": ");
		_printe_(data->command_name);
		_printe_(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe_(data->program_name);
		_printe_(": ");
		_printe_(n_as_stg);
		_printe_(": ");
		_printe_(data->command_name);
		_printe_(": Permission denied\n");
	}
	return (0);
}
