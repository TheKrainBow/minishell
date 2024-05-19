/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/16 16:59:51 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we can add one more int in ft_echo to track option position in args
//if we need in case of " | "

int	check_echo_opt(char *option)
{
	int i;

	i = 2;
	if (option[0] != '-' || option[1] != 'n')
		return (0);
	while(option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}	

int	print_env(t_cmd *cmd, char *name)
{
	int	i;

	i = 0;
	if (name[0] != '$')
		return (0);
	name++;
	while (cmd->data->env[i])
	{
		if (ft_strncmp(cmd->data->env[i], name,
					ft_strchr(cmd->data->env[i], '=') - cmd->data->env[i]) == 0)
		{
			printf("%s", ft_strchr(cmd->data->env[i], '=') + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(t_cmd *cmd) 
{
	int	i;
	int	n_opt;

	i = 1;
	if (cmd->args[i] == NULL)
	{
		printf("\n");
		return (1);
	}
	n_opt = check_echo_opt(cmd->args[i]);
	if (n_opt == 1 && cmd->args[i + 1] == NULL)
		return (1);
	while (check_echo_opt(cmd->args[i]))
		i++;
	while (cmd->args[i] != NULL)
	{
		if (!print_env(cmd, cmd->args[i]))
			printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_opt == 0)
		printf("\n");
	return (1);
}