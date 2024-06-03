/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bul_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:03:05 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/25 00:03:05 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signum;

int	plus_in_name(char *env_name)
{
	int	i;

	i = -1;
	while (env_name[++i] && env_name[i] != '=')
		if (env_name[i] == '+')
			return (1);
	return (0);
}

void	remove_plus(char *str)
{
	char	*plus;

	plus = ft_strchr(str, '+');
	if (plus)
		ft_memmove(plus, plus + 1, ft_strlen(plus));
}

int	already_in_env(char *env_name, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], env_name,
				ft_strchr(env_name, '=') - env_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_env_name(char *env_name)
{
	int	i;

	if (!ft_isalpha(env_name[0]) && env_name[0] != '_')
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			env_name);
		return (!(g_signum = 1));
	}
	i = 0;
	while (env_name[++i] != '=' && env_name[i])
	{
		if (env_name[i + 1] == '=' && env_name[i] == '+')
			return (1);
		if (!ft_isalpha(env_name[i]) && !ft_isdigit(env_name[i]))
		{
			if (env_name[i] != ' ' && env_name[i] != '_')
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n",
					env_name);
				g_signum = 1;
				return (!(g_signum = 1));
			}
		}
	}
	return (env_name[i] == '=');
}
