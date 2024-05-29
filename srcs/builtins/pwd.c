/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giorgi <giorgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 23:56:43 by giorgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_var_from_env(cmd->data->env, "PWD");
	ft_putstr(pwd + 4);
	ft_putchar('\n');
	cmd->data->last_error = 0;
}
