/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:28:10 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:39:10 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_flags(int type)
{
	if (type == REDIR_APPEND)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (O_CREAT | O_WRONLY | O_TRUNC);
}

void	redirect_in(int stdin, t_redirection *redirs, char *s)
{
	int	fd[2];

	if (stdin)
		dup2(stdin, 0);
	if (s)
	{
		pipe(fd);
		ft_putstr_fd(s, fd[1]);
		close(fd[1]);
	}
	while ((++redirs)->value)
	{
		if (*redirs->value && redirs->type == REDIR_INPUT)
		{
			redirs->fd = open(redirs->value + 1, O_RDONLY);
			if (redirs->fd == -1)
				break ;
			dup2(redirs->fd, STDIN_FILENO);
		}
		else if (s && *redirs->value && redirs->type == REDIR_HEREDOC)
			dup2(fd[0], STDIN_FILENO);
	}
}

int	redirect_out(t_redirection *redirs)
{
	while (redirs->value)
	{
		if (*redirs->value && (redirs->type == REDIR_OUTPUT
				|| redirs->type == REDIR_APPEND))
		{
			redirs->fd = open(redirs->value + 1, file_flags(redirs->type),
					S_IRWXU);
			if (redirs->fd == -1)
				return (error(SH, redirs->value + 1,
						"permission denied", 1));
			dup2(redirs->fd, 1);
		}
		redirs++;
	}
	return (0);
}

void	close_out(t_redirection *redirs)
{
	while (redirs->value)
	{
		if ((redirs->type == REDIR_OUTPUT || redirs->type == REDIR_APPEND
				|| redirs->type == REDIR_INPUT) && redirs->fd)
			close(redirs->fd);
		redirs++;
	}
}
