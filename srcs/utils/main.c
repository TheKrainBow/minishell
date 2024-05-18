/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 03:54:02 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fake_cmd(t_data *data, char **args)
{
	t_cmd	*dest;

	dest = ft_calloc(1, sizeof(t_cmd));
	dest->args = args;
	dest->data = data;
	dest->name = args[0];
	return (dest);
}

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
	return (NULL);
}

void	start_cmd(void *ptr)
{
	t_cmd		*cmd;
	t_func_cmd	execute;

	cmd = ptr;
	execute = get_cmd(cmd->name);
	if (execute != NULL)
		execute(cmd);
	else
		printf("minishell: command not found: %s\n", cmd->name);
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
	if (parse_input(data, av[1]) == 1)
	{
		ft_lstiter(data->cmds, &start_cmd);
		ft_lstclear(&data->cmds, &free_cmd);
	}
	free_data(data);
	return (0);
}
