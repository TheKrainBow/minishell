/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:18:34 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:25:50 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_value(char *name, char *value, t_data *data)
{
	char	*new_value_name;
	char	*new_value;

	value = clear_quotes(value, data);
	new_value_name = ft_strjoin(name, "=");
	new_value = ft_strjoin(new_value_name, value);
	free(value);
	free(new_value_name);
	return (new_value);
}

void	ft_add_to_env(char *name, char *value, t_data *data)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = ft_env_size(data->temp_environ);
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!(new_env))
		return ;
	i = -1;
	while (++i < env_size)
	{
		new_env[i] = ft_strdup(data->temp_environ[i]);
		free(data->temp_environ[i]);
	}
	new_env[i] = create_env_value(name, value, data);
	new_env[i + 1] = NULL;
	free(data->temp_environ);
	data->temp_environ = new_env;
}

int	ft_export_name(char *name, char *value, t_data *data)
{
	int		index;

	if (env_check(name, data))
		return (1);
	index = ft_find_in_env(name, data);
	if (index != -1)
	{
		free(data->temp_environ[index]);
		data->temp_environ[index] = create_env_value(name, value, data);
	}
	else
		ft_add_to_env(name, value, data);
	if (!ft_strcmp(name, "PATH"))
		ft_update_path(data);
	return (0);
}

void	ft_export_print(char **strs)
{
	int			i;
	int			max;
	char		**temp;

	max = ft_tablen(strs);
	i = -1;
	while (++i < max)
	{
		ft_putstr_fd("export ", 1);
		temp = ft_split(strs[i], '=');
		ft_putstr(temp[0]);
		ft_putstr("=\"");
		ft_putstr(ft_strchr(strs[i], '=') + 1);
		ft_putstr("\"\n");
		ft_free_tab(temp);
	}
}

void	ft_export_env(t_cmd *cmd, t_data *data)
{
	char		*name;
	char		*value;
	int			i;
	char		*sep;

	data->wexitstatus = 0;
	i = 0;
	if (!cmd->args[1])
		ft_print_sorted_env(data);
	while (cmd->args && cmd->args[++i])
	{
		sep = ft_strchr(cmd->args[i], '=');
		if (sep == NULL)
		{
			env_check(cmd->args[i], data);
			continue ;
		}
		value = sep + 1;
		*sep = 0;
		name = cmd->args[i];
		if (ft_export_name(name, value, data))
			data->wexitstatus = 1;
	}
}
