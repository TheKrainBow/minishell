/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:33:10 by magostin          #+#    #+#             */
/*   Updated: 2021/02/08 18:43:04 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	new_env[i - j] = NULL;
	__environ = new_env;
}

int		ft_unset_env(char *name)
{
	int		index;

	if ((index = ft_find_in_env(name)) != -1)
		ft_delete_env(index);
	return (0);
}