#include "shell.h"

/**
 * str_leng - function that returns the length of string.
 *
 * @string: thr pointer to the string.
 *
 * Return: the leng of string.
 */

int str_leng(char *string)
{
	int leng = 0;

	if (string == NULL)
		return (0);

	while (string[leng++] != '\0')
	{
	}
	return (--leng);
}

/**
 * str_dupl - function to duplicate a string.
 *
 * @string: String.
 *
 * Return: the pointer to array.
 */

char *str_dupl(char *string)
{
	char *r;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_leng(string) + 1;

	r = malloc(sizeof(char) * len);

	if (r == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		r[i] = string[i];
	}

	return (r);
}

/**
 * string_compare - a function that Compares two strings.
 *
 * @string1: String the shorter.
 * @string2: String the longer.
 * @number: number of characters to be compared..
 *
 * Return: 1 if  strings  equals,0 if  strings  are not equal.
 */

int string_compare(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);
	if (string1 == NULL || string2 == NULL)
		return (0);
	if (number == 0) /* infinite longitud */
	{
		if (str_leng(string1) != str_leng(string2))
			return (0);
		for (i = 0; string1[i]; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < number ; i++)
		{
			if (string1[i] != string2[i])
			return (0);
		}		
		return (1);
	}
}

/**
 * str_concating - function that concatenates two strings.
 *
 * @string1: String .
 * @string2: String 2.
 *
 * Return: the pointer to the array.
 */

char *str_concating(char *string1, char *string2)
{
	char *r;
	int leng1 = 0, leng2 = 0;

	if (string1 == NULL)
		string1 = "";
	leng1 = str_leng(string1);

	if (string2 == NULL)
		string2 = "";
	leng2 = str_leng(string2);

	r = malloc(sizeof(char) * (leng1 + leng2 + 1));
	if (r == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (leng1 = 0; string1[leng1] != '\0'; leng1++)
		r[leng1] = string1[leng1];
	free(string1);
	for (leng2 = 0; string2[leng2] != '\0'; leng2++)
	{
		r[leng1] = string2[leng2];
		leng1++;
	}

	r[leng1] = '\0';
	return (r);
}


/**
 * str_rev - a function that reverses a string.
 *
 * @string: the pointer to string.
 *
 * Return: void.
 */
void str_rev(char *string)
{

	int i = 0, leng = str_leng(string) - 1;
	char hold;

	while (i < leng)
	{
		hold = string[i];
		string[i++] = string[leng];
		string[leng--] = hold;
	}
}
