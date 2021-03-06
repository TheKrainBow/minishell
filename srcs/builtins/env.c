/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:43:55 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 22:15:36 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_path(t_data *data)
{
	char		*str;
	int			index;

	ft_free_tab(data->path);
	index = ft_find_in_env("PATH");
	if (index == -1)
		return ;
	str = __environ[index];
	data->path = ft_split(str + 5, ':');
}

int		ft_env_size(void)
{
	int		i;
	
	i = 0;
	while (__environ[i])
		i++;
	return (i);
}

void	ft_free_env(void)
{
	int		i;

	i = -1;
	while (__environ[++i])
		free(__environ[i]);
	free(__environ);
}

void	ft_malloc_env(void)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = ft_env_size();
	if (!(new_env = malloc(sizeof(char *) * (env_size + 1))))
		return ;
	i = -1;
	while (++i < env_size)
		new_env[i] = ft_strdup(__environ[i]);
	new_env[i] = NULL;
	__environ = new_env;
}

void		ft_print_env(t_cmd *cmd, t_data *data)
{
	int			i;

	(void)cmd;
	(void)data;
	i = -1;
	while (__environ[++i])
		printf("%s\n", __environ[i]);
}