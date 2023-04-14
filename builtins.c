/**
 * get_builtin - shellby builtin function.
 * @command: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
	{ "exit", shellby_exit },
	{ "cd", shellby_cd },
	{ "help", shellby_help },
	{ NULL, NULL }
	};

	for (int i = 0; funcs[i].name != NULL; i++)
	{
	if (_strcmp(funcs[i].name, command) == 0)
	return (funcs[i].f);
	}
	return (NULL);
}

/**
 * shellby_exit - Causes normal process termination
 * @args: An array of arguments
 * * @front: A double pointer at the start of an args.
 * Return: 0
 */
int shellby_exit(char **args, char **front)
{
	if (!args[0])
	return (-3);

	char *endptr;
	int status = (int)strtol(args[0], &endptr, 10);

	if (*endptr != '\0' || endptr == args[0])
	return (2);

	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(status);
}

/**
 * shellby_cd - Changes the current directory.
 * @args: argument of an array.
 * @front: A double pointer at the start of an args.
 * Return: 0
 */
int shellby_cd(char **args, char **front)
{
	char *dir;

	if (args[1] != NULL)
		return (create_error(args, 2));

	if (args[0] == NULL || _strcmp(args[0], "~") == 0)
		dir = _getenv("HOME");

	else if (_strcmp(args[0], "-") == 0)
	{
		dir = _getenv("OLDPWD");
		if (dir == NULL)
			return (create_error(args, 2));
	}
	else
		dir = args[0];

	int ret = chdir(dir);

	if (ret == -1)
		return (create_error(args, 2));

	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (create_error(args, -1));

	char *pwd[3] = { "OLDPWD", _getenv("PWD"), NULL };

	_setenv(pwd, front);
	pwd[0] = "PWD";
	pwd[1] = cwd;
	_setenv(pwd, front);

	return (0);
}

/**
 * shellby_help - shows the shellby builtin commands.
 * @args: argument of an array.
 * @front: A double pointer at the start of an args.
 * Return: 0 if no errors occur.
 */
int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	char *builtin_cmds[] = {"alias", "cd", "exit", "env",
	"setenv", "unsetenv", "help", NULL};
	void (*builtin_help_funcs[])(void) = {help_alias, help_cd, help_exit,
	help_env, help_setenv, help_unsetenv, help_help};

	if (!args[0])
	{
		help_all();
		return (0);
	}
	for (int i = 0; builtin_cmds[i]; i++)
	{
		if (_strcmp(args[0], builtin_cmds[i]) == 0)
		{
			builtin_help_funcs[i]();
			return (0);
		}
	}
	write(STDERR_FILENO, name, _strlen(name));
	return (0);
}
