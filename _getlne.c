#include "shell.h"

/**
* _get_line - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int _get_line(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *arr_commands[10] = {NULL};
	static char arr_operators[10] = {'\0'};
	ssize_t byt_read, i = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!arr_commands[0] || (arr_operators[0] == '&' && errno != 0) ||
		(arr_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (i = 0; arr_commands[i]; i++)
		{
			free(arr_commands[i]);
			arr_commands[i] = NULL;
		}

		/* read from the file descriptor int to buff */
		byt_read = read(data->file_desc, &buff, BUFFER_SIZE - 1);
		if (byt_read == 0)
			return (-1);

		/* split lines for \n or ; */
		i = 0;
		do {
			arr_commands[i] = string_duplicate(_strtok(i ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			i = check_ops(arr_commands, i, arr_operators);
		} while (arr_commands[i++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	data->inpt_line = arr_commands[0];
	for (i = 0; arr_commands[i]; i++)
	{
		arr_commands[i] = arr_commands[i + 1];
		arr_operators[i] = arr_operators[i + 1];
	}

	return (str_length(data->inpt_line));
}


/**
* check_ops - checks and split for && and || operators
* @arr_commands: array of the commands.
* @i: index in the arr_commands to be checked
* @arr_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the arr_commands.
*/
int check_ops(char *arr_commands[], int i, char arr_operators[])
{
	char *temp = NULL;
	int j;

	/* checks for the & char in the command line*/
	for (j = 0; arr_commands[i] != NULL  && arr_commands[i][j]; j++)
	{
		if (arr_commands[i][j] == '&' && arr_commands[i][j + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = arr_commands[i];
			arr_commands[i][j] = '\0';
			arr_commands[i] = string_duplicate(arr_commands[i]);
			arr_commands[i + 1] = string_duplicate(temp + j + 2);
			i++;
			arr_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (arr_commands[i][j] == '|' && arr_commands[i][j + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = arr_commands[i];
			arr_commands[i][j] = '\0';
			arr_commands[i] = string_duplicate(arr_commands[i]);
			arr_commands[i + 1] = string_duplicate(temp + j + 2);
			i++;
			arr_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
