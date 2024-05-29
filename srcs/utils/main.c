/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 04:12:13 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pid;

void	print_cmd(void *ptr)
{
	t_cmd	*lexer;
	int		i;

	i = 0;
	lexer = ptr;
	printf("Command '%s':\n -> Args:\n", lexer->name);
	while (lexer->args[i])
		printf("  -> [%s]\n", lexer->args[i++]);
}

t_func_cmd	get_cmd(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (&ft_echo);
	if (!ft_strcmp(name, "cd"))
		return (&ft_cd);
	if (!ft_strcmp(name, "pwd"))
		return (&ft_pwd);
	if (!ft_strcmp(name, "unset"))
		return (&ft_unset);
	if (!ft_strcmp(name, "env"))
		return (&ft_env);
	if (!ft_strcmp(name, "export"))
		return (&ft_export);
	if (!ft_strcmp(name, "exit"))
		return (&ft_exit);
	return (&ft_execve);
}

int	open_options(t_token token)
{
	if (token == OUT_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (token == OUT_TRUNCATE)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (token == IN)
		return (O_RDONLY);
	return (0);
}

void	handle_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	content->fd = open(content->str, open_options(content->token), 0777);
	if (content->fd < 0)
	{
		dprintf(2, "minishell: no such file or directory: %s\n", content->str);
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

void	pipe_prev(t_list *node)
{
	t_cmd	*prev_cmd;
	t_cmd	*cmd;

	cmd = node->content;
	if (node->prev)
	{
		prev_cmd = node->prev->content;
		dup2(prev_cmd->pipe[0], STDIN_FILENO);
		close(prev_cmd->pipe[0]);
	}
	ft_lstiter(cmd->out, &handle_redirection);
	get_cmd(cmd->name)(cmd);
}

void	pipe_next(t_list *node)
{
	t_cmd	*cmd;
	int		ret;

	cmd = node->content;
	pipe(cmd->pipe);
	dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[1]);
	if (node->prev)
	{
		dup2(((t_cmd *)node->prev->content)->pipe[0], STDIN_FILENO);
		close(((t_cmd *)node->prev->content)->pipe[0]);
	}
	cmd->pid = fork();
	if (!cmd->pid)
	{
		ft_lstiter(cmd->out, &handle_redirection);
		get_cmd(cmd->name)(cmd);
		close(cmd->pipe[0]);
		dup2(cmd->data->std_in, STDIN_FILENO);
		dup2(cmd->data->std_out, STDOUT_FILENO);
		ret = cmd->data->last_error;
		free_data(cmd->data);
		exit(ret);
	}
}

void	wait_cmds(t_data *data)
{
	int		ret;
	t_list	*node;

	if (ft_lstsize(data->cmds) <= 1)
		return ;
	node = data->cmds->next;
	while (node)
	{
		waitpid(((t_cmd *)node->content)->pid, &ret, 0);
		ft_lstiter(((t_cmd *)node->content)->out, &close_redirection);
		node = node->next;
	}
	if (WIFEXITED(ret))
		data->last_error = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		data->last_error = 128 + WTERMSIG(ret);
	else if (WIFSTOPPED(ret))
		data->last_error = 128 + WSTOPSIG(ret);
}

void	start_cmds(t_data *data)
{
	t_list		*node;

	node = data->cmds;
	while (node)
	{
		if (node->next)
			pipe_next(node);
		else
			pipe_prev(node);
		dup2(data->std_in, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
		node = node->next;
	}
	wait_cmds(data);
}

void	minishell(t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		signals_main();
		dup2(data->std_in, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
		line = readline("minishell> ");
		signals_pipe();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (parse_input(data, line) != 1)
			continue ;
		add_history(line);
		start_cmds(data);
		ft_lstclear(&data->cmds, &free_cmd);
		data->cmds = NULL;
	}
}

int	main(int ac, char **av, char **environ)
{
	t_data	*data;

	(void)ac;
	(void)av;
	g_pid = 0;
	data = init_data(environ);
	minishell(data);
	free_data(data);
}
