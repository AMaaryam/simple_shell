#include "shell.h"
/**
 * _stringtok - function that separates strings with delimiters.
 *
 * @line: the pointer to array we receive getline.
 * @delim: the characters we mark off string parts.
 *
 * Return: created token.
*/

char *_stringtok(char *line, char *delim)
{
	int x;
	static char *str;
	char *copyy;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (x = 0; delim[x] != '\0'; x++)
		{
			if (*str == delim[x])
			break;
		}
		if (delim[x] == '\0')
			break;
	}
	copyy = str;
	if (*copyy == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (x = 0; delim[x] != '\0'; x++)
		{
			if (*str == delim[x])
			{
				*str = '\0';
				str++;
				return (copyy);
			}
		}
	}
	return (copyy);
}
