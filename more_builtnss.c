#include "shell.h"

/**
 * builtin_exxit - function to exit the program with the status.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number iotherwise.
 */

int builtin_exxit(data_of_programm *data)
{
        int i;

        if (data->tokens[1] != NULL)
        {
                for (i = 0; data->tokens[1][i]; i++)
                        if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
                                && data->tokens[1][i] != '+')
                        {
                                errno = 2;
                                return (2);
                        }

                errno = str_int(data->tokens[1]);
        }

        free_all_the_data(data);
        exit(errno);
}

/**
 * builtinn_cd - function that will change the current directory.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int builtinn_cd(data_of_programm *data)
{
        char *dirk_home = env_getin_key("HOME", data), *dir_old = NULL;
        char old_dir[128] = {0};
        int eror_code = 0;

        if (data->tokens[1])
        {
                if (string_compare(data->tokens[1], "-", 0))
                {
                        dir_old = env_getin_key("OLDPWD", data);
                        if (dir_old)
                                eror_code = set_working_directory(data, dir_old);

                        _print(env_getin_key("PWD", data));
                        _print("\n");

                        return (eror_code);
                }
                else
                {
                        return (set_working_directory(data, data->tokens[1]));
                }
        }
        else
        {
                if (!dirk_home)
                        dirk_home = getcwd(old_dir, 128);

                return (set_working_directory(data, dirk_home));
        }
        return (0);
}

/**
 * set_working_directory - function that sets the work directory.
 *
 * @data: program data.
 * @new_dir: work directory.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int set_working_directory(data_of_programm *data, char *new_dir)
{
        char older_dir[128] = {0};
        int e_code = 0;

        getcwd(older_dir, 128);

        if (!string_compare(older_dir, new_dir, 0))
        {
                e_code = chdir(new_dir);

                if (e_code == -1)
                {
                        errno = 2;
                        return (3);
                }
                envrmnt_set_key("PWD", new_dir, data);
        }

        envrmnt_set_key("OLDPWD", older_dir, data);
        return (0);
}

/**
 * builtin_helper - function to show environment where shell is running.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int builtin_helper(data_of_programm *data)
{
        int i, len = 0;
        char *Menajes[6] = {NULL};

        Menajes[0] = HELP_MG;

        if (data->tokens[1] == NULL)
        {
                _print(Menajes[0] + 6);
                return (1);
        }

        if (data->tokens[2] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }
        Menajes[1] = HELP_EXIT_MG;
        Menajes[2] = HELP_ENV_MG;
        Menajes[3] = HELP_SETENV_MG;
        Menajes[4] = HELP_UNSETENV_MG;
        Menajes[5] = HELP_CD_MG;

        for (i = 0; Menajes[i]; i++)
        {
                len = str_leng(data->tokens[1]);
                if (string_compare(data->tokens[1], Menajes[i], len))
                {
                        _print(Menajes[i] + len + 1);
                        return (1);
                }
        }
        errno = EINVAL;
        perror(data->command_name);

        return (0);
}


/**
 * builtinns_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtinns_alias(data_of_programm *data)
{
        int i = 0;

        if (data->tokens[1] == NULL)
                return (p_alias(data, NULL));


        while (data->tokens[++i])
        {
                if (counter_char(data->tokens[i], "="))
                        seting_alias(data->tokens[i], data);
                else
                        p_alias(data, data->tokens[i]);
        }

        return (0);
}
