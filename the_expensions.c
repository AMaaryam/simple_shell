#include "shell.h"

/**
 * variable_expension - a function that expands variables.
 *
 * @data: the pointer to structure of the program data.
 *
 * Return: void.
 */
void variable_expension(data_of_programm *data)
{
	int x, y;
	char line[BUFFER_SZE] = {0}, expansion[BUFFER_SZE] = {'\0'}, *tem;

	if (data->input_line == NULL)
		return;
	buffer_adding(line, data->input_line);
	for (x = 0; line[x]; x++)
		if (line[x] == '#')
			line[x--] = '\0';
		else if (line[x] == '$' && line[x + 1] == '?')
		{
			line[x] = '\0';
			numb_to_string(errno, expansion, 10);
			buffer_adding(line, expansion);
			buffer_adding(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && line[x + 1] == '$')
		{
			line[x] = '\0';
			numb_to_string(getpid(), expansion, 10);
			buffer_adding(line, expansion);
			buffer_adding(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && (line[x + 1] == ' ' || line[x + 1] == '\0'))
			continue;
		else if (line[x] == '$')
		{
			for (y = 1; line[x + y] && line[x + y] != ' '; y++)
				expansion[y - 1] = line[x + y];
			tem = env_getin_key(expansion, data);
			line[x] = '\0', expansion[0] = '\0';
			buffer_adding(expansion, line + x + y);
			tem ? buffer_adding(line, tem) : 1;
			buffer_adding(line, expansion);
		}
	if (!string_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_dupl(line);
	}
}
/**
 * alias_expension - a function that expan the  alias.
 *
 * @data: the pointer to struct of the program data.
 *
 * Return: void.
 */

void alias_expension(data_of_programm *data)
{
	int i, j, was_expnd = 0;

	char line[BUFFER_SZE] = {0}, expansion[BUFFER_SZE] = {'\0'}, *tem;

	if (data->input_line == NULL)
		return;

	buffer_adding(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		tem = bring_alias(data, expansion);
		if (tem)
		{
			expansion[0] = '\0';
			buffer_adding(expansion, line + i + j);
			line[i] = '\0';
			buffer_adding(line, tem);
			line[str_leng(line)] = '\0';
			buffer_adding(line, expansion);
			was_expnd = 1;
		}
		break;
	}

	if (was_expnd)
	{
		free(data->input_line);
		data->input_line = str_dupl(line);
	}
}


/**
 * buffer_adding - a function that append string at end of buffer.
 *
 * @buffer: the main buffer to be filled.
 * @str_to_add: the string copied in the buffer.
 *
 * Return: void.
 */

int buffer_adding(char *buffer, char *str_to_add)
{
	int leng, x;

	leng = str_leng(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[leng + x] = str_to_add[x];
	}

	buffer[leng + x] = '\0';
	return (leng + x);
}
