/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:00 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/16 17:35:04 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fake_cmd(char **args, char **env)
{
	t_cmd	*dest;

	dest = ft_calloc(1, sizeof(t_cmd));
	dest->args = args;
	dest->env = env;
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

int	main(int ac, char **av, char **environ)
{
	t_data	*data;
	t_cmd	*cmd;

	data = init_data(environ);
	cmd = fake_cmd(ft_strs_to_tab(3, "export", "TEST=maagosti", "TOTO=tata"), data->env);
	ft_export(cmd);
	(void)ac;
	(void)av;
	free_data(data);
	ft_free_tab(cmd->args);
	free(cmd);
	return (1);
}
