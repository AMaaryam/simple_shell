#include "shell.h"

/**
 * builtin_lists - a function to search for match and execute the builtins.
 *
 * @data: program data.
 *
 * Return: the executed func , -1 otherwise.
 */
int builtin_lists(data_of_programm *data)
{
        int iterator;
        builtins options[] = {
                {"exit", builtin_exxit},
                {"help", builtin_helper},
                {"cd", builtinn_cd},
                {"alias", builtinns_alias},
                {"env", builtins_env},
                {"setenv", builtins_sett_env},
                {"unsetenv", builtin_unset_env},
                {NULL, NULL}
        };

        for (iterator = 0; options[iterator].builtin != NULL; iterator++)
        {
                if (string_compare(options[iterator].builtin, data->command_name, 0))
                {
                        return (options[iterator].function(data));
                }
        }

        return (-1);
}
