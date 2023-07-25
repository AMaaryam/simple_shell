#include "shell.h"

/**
 * main - function to initialize the variables of the program.
 *
 * @argc: numb ofvalues received from  command line.
 * @argv: num of values received from  command line.
 * @env: number of values received from  command line.
 *
 * Return: 0 succes.
 */

int main(int argc, char *argv[], char *env[])
{
	data_of_programm data_structure = {NULL}, *data = &data_structure;
	char *p = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrlc);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		p = PROMPT_MG;
	}
	errno = 0;
	loop_prpmpt(p, data);
	return (0);
}

/**
 * handle_ctrlc - function that print the prompt in a new line
 *                when typing(ctrl + c) is send to the program.
 *
 * @UNUSED: the option of prototype.
 */

void handle_ctrlc(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MG);
}

/**
 * init_data - function to inicialize the structure
 *             with the info of the program.
 *
 * @data: the pointer to structure of data.
 * @argv: the array of argument pased to the program execution.
 * @env: the environ pased to program execution.
 * @argc: number of values received from command line.
 */

void init_data(data_of_programm *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe_(data->program_name);
			_printe_(": 0: Can't open ");
			_printe_(argv[1]);
			_printe_("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_dupl(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * loop_prpmpt - function with an infinite loop that shows the prompt.
 *
 * @prompt: the main prompt to be printed.
 * @data:  the loop that shows the prompt.
 */
void loop_prpmpt(char *prompt, data_of_programm *data)
{
	int errorr_code = 0, string_leng = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		errorr_code = string_leng = _getlin(data);
		if (errorr_code == EOF)
		{
			free_all_the_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}

		if (string_leng >= 1)
		{
			alias_expension(data);
			variable_expension(data);
			tokenizeing(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				errorr_code = executeer(data);
				if (errorr_code != 0)
					_print_eror(errorr_code, data);
			}
			free_the_data(data);
		}
	}
}

