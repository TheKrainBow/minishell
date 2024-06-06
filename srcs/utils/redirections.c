/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:41:59 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/06 14:19:53 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_options(t_token token)
{
	if (token == OUT_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (token == OUT_TRUNCATE)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (token == IN)
		return (O_RDONLY);
	return (0);
}

void	handle_heredoc(t_lexer *content)
{
	char	*line;
	pid_t	pid;
	int		pipe_fd[2];
	int		i;

	pipe(pipe_fd);
	pid = fork();
	i = 0;
	if (!pid)
	{
		content->fd = pipe_fd[1];
		line = "";
		while (line)
		{
			line = readline("> ");
			if (!line)
			{
				printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", i, content->str);
				break ;
			}
			if (ft_strcmp(line, content->str) == 0)
				break ;
			ft_putstr_fd(line, content->fd);
			ft_putstr_fd("\n", content->fd);
			free(line);
			i++;
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	content->fd = pipe_fd[0];
	dup2(content->fd, STDIN_FILENO);
	close(content->fd);
}

void	handle_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	if (content->token == HERE_DOC)
		return (handle_heredoc(content));
	content->fd = open(content->str, open_options(content->token), 0777);
	if (content->fd < 0)
	{
		ft_printf("minishell: no such file or directory: %s\n", content->str);
		return ;
	}
	dup2(content->fd, content->token != IN);
}

void	close_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	close(content->fd);
}
