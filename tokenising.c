#include "shell.h"

/**
 * tokenizeing - function that separate the string using a delimiter.
 *
 * @data: pointer to the program data.
 *
 * Return: array of the different parts of the string
 */
void tokenizeing(data_of_programm *data)
{
        char *delimit = " \t";
        int i, x, counterrr = 2, length;

        length = str_leng(data->input_line);
        if (length)
        {
                if (data->input_line[length - 1] == '\n')
                        data->input_line[length - 1] = '\0';
        }

        for (i = 0; data->input_line[i]; i++)
        {
                for (x = 0; delimit[x]; x++)
                {
                        if (data->input_line[i] == delimit[x])
                                counterrr++;
                }
        }
        data->tokens = malloc(counterrr * sizeof(char *));
        if (data->tokens == NULL)
        {
                perror(data->program_name);
                exit(errno);
        }
        i = 0;
        data->tokens[i] = str_dupl(_stringtok(data->input_line, delimit));
        data->command_name = str_dupl(data->tokens[0]);

        while (data->tokens[i++])
        {
                data->tokens[i] = str_dupl(_stringtok(NULL, delimit));
        }
}
