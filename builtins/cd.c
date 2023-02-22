
#include "minishell.h"

void	cd(t_env *env, char **argv)
{
	char	*pwd;
	char	buf[PATH_BUF];
	char	*status;

	if (*argv)
		status = *argv;
	else
		status = getenv("HOME");
	if (chdir(status) == -1)
		error("cd", strerror(errno), status, errno);
	else
	{
		pwd = ft_strjoin("OLDPWD=", g_process.pwd);
		env_set(&env->local, pwd);
		env_set(&env->exported, pwd);
		free(pwd);
		pwd = ft_strjoin("PWD=", getcwd(buf, PATH_BUF));
		env_set(&env->local, pwd);
		env_set(&env->exported, pwd);
		free(pwd);
		free(g_process.pwd);
		g_process.pwd = ft_strdup(getcwd(buf, PATH_BUF));
		g_process.code = 0;
	}
}