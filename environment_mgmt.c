#include "shell.h"

/**
 * env_getin_key - function that gets  value of environment variable.
 *
 * @key: environment variable of interest.
 * @data: program data.
 *
 * Return: a pointer to the value of  variable or NULL otherwise.
 */

char *env_getin_key(char *key, data_of_programm *data)
{
        int i, key_leng = 0;

        if (key == NULL || data->env == NULL)
                return (NULL);

        key_leng = str_leng(key);

        for (i = 0; data->env[i]; i++)
        {
                if (string_compare(key, data->env[i], key_leng) &&
                 data->env[i][key_leng] == '=')
                {
                        return (data->env[i] + key_leng + 1);
                }
        }

        return (NULL);
}


/**
 * envrmnt_set_key - function that overwrite the value of the env variable.
 *
 * @key: name of  variable set.
 * @value: value.
 * @data: program data.
 *
 * Return: 1 if  parameters are NULL, 2 if there is  erroror and 0 if sucess.
 */

int envrmnt_set_key(char *key, char *value, data_of_programm *data)
{
        int i, key_leng = 0, is_newer_key = 1;

        if (key == NULL || value == NULL || data->env == NULL)
                return (1);
        key_leng = str_leng(key);

        for (i = 0; data->env[i]; i++)
        {
                if (string_compare(key, data->env[i], key_leng) &&
                 data->env[i][key_leng] == '=')
                {
                        is_newer_key = 0;

                        free(data->env[i]);
                        break;
                }
        }

        data->env[i] = str_concating(str_dupl(key), "=");
        data->env[i] = str_concating(data->env[i], value);

        if (is_newer_key)
        {

                data->env[i + 1] = NULL;
        }

        return (0);
}


/**
 * env_remove_key - function created to remove a key from the env.
 *
 * @key: the main key to remove.
 * @data: the program data.
 *
 * Return: 1 if key was removed, 0 if the key does not exist.
 */
int env_remove_key(char *key, data_of_programm *data)
{
        int i, key_leng = 0;

        if (key == NULL || data->env == NULL)
                return (0);
        key_leng = str_leng(key);

        for (i = 0; data->env[i]; i++)
        {
                if (string_compare(key, data->env[i], key_leng) &&
                 data->env[i][key_leng] == '=')
                {
                        free(data->env[i]);

                        i++;
                        for (; data->env[i]; i++)
                        {
                                data->env[i - 1] = data->env[i];
                        }
                        data->env[i - 1] = NULL;
                        return (1);
                }
        }

        return (0);
}


/**
 * print_envrmt - function that prints the current env.
 *
 * @data: program data.
 *
 * Return: void.
 */

void print_envrmt(data_of_programm *data)
{
        int x;

        for (x = 0; data->env[x]; x++)
        {
                _print(data->env[x]);
                _print("\n");
        }
}
