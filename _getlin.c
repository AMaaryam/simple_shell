#include "shell.h"
/**
 * _getlin - function that reads one line from prompt.
 *
 * @data: struct for the program's data
 *
 * Return: the counting bytes.
*/

int _getlin(data_of_programm *data)
{
        char buff[BUFFER_SZE] = {'\0'};
        static char *array_comnd[10] = {NULL};
        static char array_op[10] = {'\0'};
        ssize_t bytes_read, i = 0;

        if (!array_comnd[0] || (array_op[0] == '&' && errno != 0) ||
                (array_op[0] == '|' && errno == 0))
        {
                for (i = 0; array_comnd[i]; i++)
                {
                        free(array_comnd[i]);
                        array_comnd[i] = NULL;
                }

                bytes_read = read(data->file_descriptor, &buff, BUFFER_SZE - 1);
                if (bytes_read == 0)
                        return (-1);

                i = 0;

                do {
                        array_comnd[i] = str_dupl(_stringtok(i ? NULL : buff, "\n;"));
                        i = check_ops(array_comnd, i, array_op);
                } while (array_comnd[i++]);
        }
        data->input_line = array_comnd[0];
        for (i = 0; array_comnd[i]; i++)
        {
                array_comnd[i] = array_comnd[i + 1];
                array_op[i] = array_op[i + 1];
        }
        return (str_leng(data->input_line));
}

/**
 * check_ops - function that checks and split for && and ||.
 *
 * @array_comnd: array of the commands.
 * @i: index in the array_comnd to be checked
 * @array_op: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_comnd.
 */

int check_ops(char *array_comnd[], int i, char array_op[])
{
        char *temm = NULL;
        int j;

        /* checks for the & char in the command line*/
        for (j = 0; array_comnd[i] != NULL  && array_comnd[i][j]; j++)
        {
                if (array_comnd[i][j] == '&' && array_comnd[i][j + 1] == '&')
                {
                        temm = array_comnd[i];
                        array_comnd[i][j] = '\0';
                        array_comnd[i] = str_dupl(array_comnd[i]);
                        array_comnd[i + 1] = str_dupl(temm + j + 2);
                        i++;
                        array_op[i] = '&';
                        free(temm);
                        j = 0;
                }
                if (array_comnd[i][j] == '|' && array_comnd[i][j + 1] == '|')
                {
                        temm = array_comnd[i];
                        array_comnd[i][j] = '\0';
                        array_comnd[i] = str_dupl(array_comnd[i]);
                        array_comnd[i + 1] = str_dupl(temm + j + 2);
                        i++;
                        array_op[i] = '|';
                        free(temm);
                        j = 0;
                }
        }
        return (i);
}
