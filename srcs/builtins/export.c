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
	if (!is_alpha(env_name[0]) && env_name[0] != '_')
		return (0);
	while (env_name[i] != '=')
	{
		if (!is_alpha(env_name[i]) && !is_digit(env_name[i]))
		{
			if (env_name[i] != ' ')
				return (0);
		}
	}
}

int 	ft_export(t_cmd *cmd)
{
	(void)cmd;
	int	i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (!check_env_name(cmd->args[i]))
			return (0);
		
	}
	return (1);
}