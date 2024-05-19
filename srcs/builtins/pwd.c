/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/19 21:06:41 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(t_cmd *cmd, char *name)
{
	int	i;

	i = 0;
	while (cmd->data->env[i])
	{
		if (ft_strncmp(cmd->data->env[i], name,
				ft_strchr(cmd->data->env[i], '=') - cmd->data->env[i]) == 0)
		{
			printf("%s\n", ft_strchr(cmd->data->env[i], '=') + 1);
			return ;
		}
		i++;
	}
	return ;
}

int	ft_pwd(t_cmd *cmd)
{
	print_pwd(cmd, "PWD");
	return (1);
}
