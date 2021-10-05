/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:26 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:21:17 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_in_env(char *var, t_data *data)
{
	int		index;
	char	*path;

	path = NULL;
	index = ft_find_in_env(var, data);
	if (index >= 0)
		path = ft_strdup(ft_strchr(data->temp_environ[index], '=') + 1);
	return (path);
}

void	combi(char **path, char **original, char *cmp)
{
	char	*join;

	if (*original && !ft_strncmp(cmp, *original, 2))
	{
		join = ft_strjoin(*path, *original + 1);
		free(*path);
		*path = join;
	}
}

int	invalid_option(char **path, char *temp, t_data *data)
{
	if ((*path)[1])
	{
		ft_putstr("cd : -");
		ft_putchar((*path)[1]);
		ft_putstr(" invalid option\n");
		free(temp);
		data->wexitstatus = 2;
		return (1);
	}
	return (0);
}

int	ft_cd2(char **path, char *temp, t_data *data)
{
	if ((*path) && !ft_strncmp("-", (*path), 1))
	{
		if (invalid_option(path, temp, data))
			return (1);
		*path = get_path_in_env("OLDPWD", data);
		if (!(*path))
		{
			ft_putstr("cd : OLDPWD undefined\n");
			data->wexitstatus = 1;
			free(temp);
			return (1);
		}
		ft_putstr((*path));
		ft_putstr("\n");
		free(temp);
	}
	else if (!(*path) || !ft_strncmp("~", (*path), 1))
	{
		(*path) = get_path_in_env("HOME", data);
		combi(path, &temp, "~/");
		free(temp);
	}
	return (0);
}

void	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*temp;

	path = NULL;
	if (cmd->args[1])
		path = ft_strdup(cmd->args[1]);
	quote_bin(&path, data);
	temp = path;
	if (path && cmd->args[2])
	{
		ft_putstr("cd : too many arguments\n");
		free(temp);
		data->wexitstatus = 1;
		return ;
	}
	if (ft_cd2(&path, temp, data))
		return ;
	env_update(path, cmd, data);
	free(path);
}
