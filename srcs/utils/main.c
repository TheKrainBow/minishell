/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/21 02:03:49 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	pipe_prev(t_list *node)
{
	t_cmd	*prev_cmd;
	t_cmd		*cmd;

	cmd = node->content;
	if (node->prev)
	{
		prev_cmd = node->prev->content;
		dup2(prev_cmd->pipe[0], STDIN_FILENO);
		close(prev_cmd->pipe[0]);
	}
	if (!get_cmd(cmd->name)(cmd))
		printf("minishell: command not found: %s\n", cmd->name);
}

void	pipe_next(t_list *node)
{
	t_cmd	*cmd;

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
		if (!get_cmd(cmd->name)(cmd))
			printf("minishell: command not found: %s\n", cmd->name);
		exit(1);
	}
	close(1);
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
	int			ret;
	node = data->cmds;
	while (node)
	{
		waitpid(((t_cmd *)node->content)->pid, &ret, 0);
		node = node->next;
	}
}

int	main(int ac, char **av, char **environ)
{
	t_data	*data;

	if (ac == 1)
	{
		printf("Add arguments\n");
		return (0);
	}
	data = init_data(environ);
	if (parse_input(data, av[1]) != 1)
		return (free_data(data), 0);
	start_cmds(data);
	ft_lstclear(&data->cmds, &free_cmd);
}
