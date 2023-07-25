#ifndef HELPERS_H
#define HELPERS_H

#define PROMPT_MG "Tay<3 "
#define UNUSED __attribute__((unused))
#define BUFFER_SZE 1024

/************* FORMATTED STRING  BUILT IN **************/


#define HELP_CD_MG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Changes the shells working dire.\n\n"\
"	si no argument is given to cd the command will be interpreted\n"\
"	if cd $HOME.\n"\
"	as the argumenthelp is - (cd -), the command will be interpreted\n"\
"	if cd $OLDPWD.\n\n"


#define HELP_EXIT_MG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	the Exit of the simple-shell.\n\n"\
"	the Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	the is that of the last command executed.\n\n"


#define HELP_ENV_MG "env=\n"\
"env:\tenv \n\n"\
"	to Print environment.\n\n"\
"	env command will be print a complete list of enviroment variables.\n\n"


#define HELP_SETENV_MG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	to Change or add an environment variable.\n\n"\
"	the initialize a new environment variable, or modify an existing one\n"\
"	to When there are not correct numbers of arguments print error message.\n\n"


#define HELP_UNSETENV_MG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	unsetenv function deletes one variable from the environment.\n\n"\
"	there are not correct numbers of arguments print error message.\n\n"

#define HELP_MG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	to Display information about builtin commands.\n\n"\
"	to Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
