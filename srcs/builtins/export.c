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

int	count_env_lines(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

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
	int	size;
	char	**new_env;
	int	i;

	i = 0;
	size = count_env_lines(cmd->data->env);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return ; // must be handled better..
	
	while (cmd->data->env[i] != NULL)
	{
		new_env[i] = ft_strdup(cmd->data->env[i]);
		if (new_env[i] == NULL)
		{
			ft_free_tab(new_env);
			printf("alloc faild");
			return ; // must be handled
		}
		i++;
	}
	
	new_env[i] = ft_strdup(cmd->args[n]);
	if (!new_env[i])
	{
		printf(" alloc faild");
		return;
	}
	new_env[i + 1] = NULL;
	ft_free_tab(cmd->data->env);
	cmd->data->env = new_env;
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
