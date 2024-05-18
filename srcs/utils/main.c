/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 03:03:59 by maagosti         ###   ########.fr       */
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

t_data	*init_data(char **environ)
{
	t_data	*dest;

	dest = ft_calloc(1, sizeof(t_data));
	dest->env = ft_tabcpy(environ);
	return (dest);
}

void	free_data(t_data *data)
{
	ft_free_tab(data->env);
	free(data);
}

void	print_cmd(void *ptr)
{
	t_cmd *lexer = ptr;
	printf("Command '%s':\n -> Args:\n", lexer->name);
	for (int i = 0; lexer->args[i]; i++)
		printf("  -> [%s]\n", lexer->args[i]);
}

int	main(int ac, char **av, char **environ)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(environ);
	parse_input(data, "echo test > toto < hihi | \"th'\"'<is is a\"n '\"exempletest\"\"\"");

	ft_lstiter(data->cmds, &print_cmd);
	ft_lstclear(&data->cmds, &free_cmd);

	free_data(data);
	return (1);
}
