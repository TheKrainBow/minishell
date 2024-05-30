/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giorgi <giorgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/30 21:29:38 by giorgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char **env, char *env_name, char *env_val, int p)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = ft_strlen(env_name) + ft_strlen(env_val) + 2;
	new = malloc(sizeof(char) * size);
	if (!new)
		return ;
	new[size - 1] = '\0';
	while (*env_name != '\0')
	{
		new[i] = *env_name++;
		i++;
	}
	new[i] = '=';
	i++;
	while (*env_val != '\0')
	{
		new[i] = *env_val++;
		i++;
	}
	free(env[p]);
	env[p] = new;
}

void	set_env_var(char **env, char *env_name, char *env_val)
{
	int	name_size;
	int	i;

	i = 0;
	name_size = ft_strlen(env_name);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], env_name, name_size) == 0)
		{
			set_env(env, env_name, env_val, i);
			return ;
		}
		i++;
	}
}

void	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->data->env[i])
	{
		ft_putstr(cmd->data->env[i]);
		ft_putchar('\n');
		i++;
	}
	cmd->data->last_error = 0;
	return ;
}
