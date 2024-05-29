/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 04:42:10 by maagosti         ###   ########.fr       */
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
