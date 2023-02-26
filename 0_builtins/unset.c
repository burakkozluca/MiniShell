
#include "minishell.h"

void	unset(char **argv, t_env *env)
{
	char	**found;

	while (*argv)
	{
		found = get_envs(env->local, *argv);
		if (found)
			**found = '\0';
		found = get_envs(env->exported, *argv++);
		if (found)
			**found = '\0';
	}
	g_process.code = 0;
}
