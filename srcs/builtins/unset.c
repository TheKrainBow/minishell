/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:33:10 by magostin          #+#    #+#             */
/*   Updated: 2021/06/25 14:30:01 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_in_env(char *name, t_data *data)
{
	int			i;

	i = 0;
	while (data->temp_environ && data->temp_environ[i]
		&& ft_strncmp(data->temp_environ[i], name, ft_max((int)ft_strlen(name),
				ft_strchr(data->temp_environ[i], '=') - data->temp_environ[i])))
		i++;
	if (data->temp_environ[i])
		return (i);
	return (-1);
}

void	ft_delete_env(int index, t_data *data)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (ft_env_size(data->temp_environ)));
	if (!(new_env))
		return ;
	i = -1;
	j = 0;
	while (data->temp_environ[++i])
	{
		if (i != index)
			new_env[i - j] = ft_strdup(data->temp_environ[i]);
		else
			j++;
		free(data->temp_environ[i]);
	}
	new_env[i - j] = NULL;
	free(data->temp_environ);
	data->temp_environ = new_env;
}

int	env_check(char *del, t_data *data)
{
	int		i;

	i = -1;
	while (del && del[++i])
	{
		if (!((ft_isalnum(del[i]) && i != 0)
				|| (ft_isalpha(del[0]) && i == 0) || (del[i] == '_')))
		{
			ft_putstr_fd("minishell: export `", 1);
			ft_putstr_fd(del, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			data->wexitstatus = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_unset_name(char *name, t_data *data)
{
	int		index;

	if (env_check(name, data))
		return (1);
	index = ft_find_in_env(name, data);
	if (index != -1)
		ft_delete_env(index, data);
	if (!ft_strcmp(name, "PATH"))
		ft_update_path(data);
	return (0);
}

void	ft_unset_env(t_cmd *cmd, t_data *data)
{
	int		i;

	data->wexitstatus = 0;
	i = 0;
	while (cmd->args[++i])
		if (ft_unset_name(cmd->args[i], data))
			data->wexitstatus = 1;
	ft_update_path(data);
}
