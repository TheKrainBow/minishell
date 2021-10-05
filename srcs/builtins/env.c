/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:43:55 by magostin          #+#    #+#             */
/*   Updated: 2021/07/14 22:07:03 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_path(t_data *data)
{
	char		*str;
	int			index;

	ft_free_tab(data->path);
	data->path = NULL;
	index = ft_find_in_env("PATH", data);
	if (index == -1)
		return ;
	str = data->temp_environ[index];
	data->path = ft_split(str + 5, ':');
}

int	ft_env_size(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_free_env(t_data *data)
{
	int		i;

	i = -1;
	while (data->temp_environ[++i])
		free(data->temp_environ[i]);
	free(data->temp_environ);
}

void	ft_malloc_env(t_data *data)
{
	char	**new_env;
	int		env_size;
	int		i;
	t_cmd	cmd;

	cmd.args = ft_strs_to_tab(2, "unset", "OLDPWD");
	data->temp_environ = NULL;
	env_size = ft_env_size(__environ);
	new_env = malloc(sizeof(char *) * (env_size + 1));
	if (!(new_env))
		return ;
	i = -1;
	while (++i < env_size)
		new_env[i] = ft_strdup(__environ[i]);
	new_env[i] = NULL;
	data->temp_environ = new_env;
	ft_unset_env(&cmd, data);
	ft_free_tab(cmd.args);
}

void	ft_print_env(t_cmd *cmd, t_data *data)
{
	int			i;

	(void)cmd;
	i = -1;
	while (data->temp_environ[++i])
		ft_putendl(data->temp_environ[i]);
}
