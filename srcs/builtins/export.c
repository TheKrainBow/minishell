/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/16 17:35:26 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_name(char *env_name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(env_name[0]) && env_name[0] != '_')
		return (0);
	while (env_name[i] != '=')
	{
		if (!ft_isalpha(env_name[i]) && !ft_isdigit(env_name[i]))
		{
			if (env_name[i] != ' ' && env_name[i] != '_')
				return (0);
		}
		if (env_name[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

void	put_line_in_env(t_cmd *cmd, int n)
{
	int i;
	int	k;

	i = 0;
	k = 0;
	char **tmp = ft_tabjoin(cmd->data->env, &cmd->args[n]);
	ft_free_tab(cmd->data->env);
	cmd->data->env = tmp;
	// while (cmd->data->env[i] != NULL)
	// {
	// 	printf("%s\n", cmd->data->env[i]);
	// 	i++;
	// }
	// cmd->data->env[i] = malloc(sizeof(char) * ft_strlen(cmd->args[n]) + 1);
	// if (!cmd->data->env[i])
	// 	return ; //need to be handled better.
	// while (cmd->args[n][k])
	// {
	// 	cmd->data->env[i][k] = cmd->args[n][k];
	// 	k++;
	// }
	// cmd->data->env[i][k] = '\0';
	// cmd->data->env[i + 1] = NULL; 
}

int 	ft_export(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (!check_env_name(cmd->args[i]))
		{
			printf("name is not valid\n");
			return (0);
		}
		put_line_in_env(cmd, i);
		i++;
	}
	return (1);
}