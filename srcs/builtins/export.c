/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:18:34 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 22:15:57 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_find_in_env(char *name)
{
	int			i;

	i = 0;
	while (__environ[i] && ft_strncmp(__environ[i], name, (int)ft_strlen(name)))
		i++;
	if (__environ[i])
		return (i);
	return (-1);
}

char	*create_env_value(char *name, char *value)
{
	char	*new_value_name;
	char	*new_value;

	new_value_name = ft_strjoin(name, "=");
	new_value = ft_strjoin(new_value_name, value);
	free(new_value_name);
	return (new_value);
}

void	ft_add_to_env(char *name, char *value)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = ft_env_size();
	if (!(new_env = malloc(sizeof(char *) * (env_size + 2))))
		return ;
	i = -1;
	while (++i < env_size)
	{
		new_env[i] = ft_strdup(__environ[i]);
		free(__environ[i]);
	}
	new_env[i] = create_env_value(name, value);
	new_env[i + 1] = NULL;
	free(__environ);
	__environ = new_env;
}

int		ft_export_name(char *name, char *value)
{
	int		index;

	if ((index = ft_find_in_env(name)) != -1)
	{
		free(__environ[index]);
		__environ[index] = create_env_value(name, value);
	}
	else
		ft_add_to_env(name, value);
	return (0);
}

void		ft_export_env(t_cmd *cmd, t_data *data)
{
	char		*name;
	char		*value;
	int			i;
	char		*sep;

	i = 0;
	while (cmd->args[++i])
	{
		sep = ft_strchr(cmd->args[i], '=');
		value = sep + 1;
		*sep = 0;
		name = cmd->args[i];
		ft_export_name(name, value);
	}
	ft_update_path(data);
}