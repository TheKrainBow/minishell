/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:33:10 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 22:55:38 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_env(int index)
{
	int		i;
	int		j;
	char	**new_env;

	if (!(new_env = malloc(sizeof(char *) * (ft_env_size()))))
		return ;
	i = -1;
	j = 0;
	while (__environ[++i])
	{
		if (i != index)
			new_env[i - j] = ft_strdup(__environ[i]);
		else
			j++;
		free(__environ[i]);
	}
	new_env[i - j] = NULL;
	free(__environ);
	__environ = new_env;
}

int		ft_unset_name(char *name)
{
	int		index;

	if ((index = ft_find_in_env(name)) != -1)
		ft_delete_env(index);
	return (0);
}

int		ft_unset_env(t_cmd	*cmd, t_data *data)
{
	int			i;

	i = 0;
	while (cmd->args[++i])
		ft_unset_name(cmd->args[i]);
	ft_update_path(data);
	return (0);
}