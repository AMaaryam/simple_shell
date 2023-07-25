#include "shell.h"

/**
 * builtins_env -  function that shows the environment
 *                 where the shell runs in program.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int builtins_env(data_of_programm *data)
{
        int i;
        char cpnam[50] = {'\0'};
        char *var_cop = NULL;

        if (data->tokens[1] == NULL)
                print_envrmt(data);
        else
        {
                for (i = 0; data->tokens[1][i]; i++)
                {
                        if (data->tokens[1][i] == '=')
                        {
                                var_cop = str_dupl(env_getin_key(cpnam, data));
                                if (var_cop != NULL)
                                        envrmnt_set_key(cpnam, data->tokens[1] + i + 1, data);
                                print_envrmt(data);

                                if (env_getin_key(cpnam, data) == NULL)
                                {
                                        _print(data->tokens[1]);
                                        _print("\n");
                                }
                                else
                                {
                                        envrmnt_set_key(cpnam, var_cop, data);
                                        free(var_cop);
                                }
                                return (0);
                        }
                        cpnam[i] = data->tokens[1][i];
                }
                errno = 2;
                perror(data->command_name);
                errno = 127;
        }
        return (0);
}


/**
 * builtins_sett_env - function.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */
int builtins_sett_env(data_of_programm *data)
{
        if (data->tokens[1] == NULL || data->tokens[2] == NULL)
                return (0);

        if (data->tokens[3] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }

        envrmnt_set_key(data->tokens[1], data->tokens[2], data);
        return (0);
}

/**
 * builtin_unset_env - function .
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int builtin_unset_env(data_of_programm *data)
{
        if (data->tokens[1] == NULL)
                return (0);

        if (data->tokens[2] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }
        env_remove_key(data->tokens[1], data);

        return (0);
}
