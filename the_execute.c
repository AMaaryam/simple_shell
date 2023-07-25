#include "shell.h"
/**
 * executeer - function executeing a command with the entire path variables.
 *
 * @data: program data.
 *
 * Return: 0 if success or -1 otherwise.
 */

int executeer(data_of_programm *data)
{
        int retvaling = 0, status;
        pid_t piddd;

        retvaling = builtin_lists(data);

        if (retvaling != -1)
                return (retvaling);

        retvaling = find_programm(data);
        if (retvaling)
        {
                return (retvaling);
        }
        else
        {
                piddd = fork();
                if (piddd == -1)
                {
                        perror(data->command_name);
                        exit(EXIT_FAILURE);
                }
                if (piddd == 0)
                {
                        retvaling = execve(data->tokens[0], data->tokens, data->env);
                        if (retvaling == -1)
                                perror(data->command_name), exit(EXIT_FAILURE);
                }
                else
                {
                        wait(&status);
                        if (WIFEXITED(status))
                                errno = WEXITSTATUS(status);
                        else if (WIFSIGNALED(status))
                                errno = 128 + WTERMSIG(status);
                }
        }

        return (0);
}
