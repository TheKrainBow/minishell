/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:27:54 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/02 17:26:20 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_update(char *path, t_cmd *cmd, t_data *data)
{
	char	*oldpath;
	t_cmd	env_update;

	data->wexitstatus = chdir(path);
	if (data->wexitstatus)
	{
		ft_putstr("This path does not exist : ");
		ft_putendl(cmd->args[1]);
		data->wexitstatus = 1;
		return ;
	}
	env_update.args = malloc(sizeof(char *) * 3);
	if (!(env_update.args))
		return ;
	env_update.args[1] = ft_strdup("OLDPWD=$PWD");
	env_update.args[2] = NULL;
	change_env_str(&(env_update.args[1]), data);
	ft_export_env(&env_update, data);
	free(env_update.args[1]);
	oldpath = getcwd(NULL, 0);
	env_update.args[1] = ft_strjoin("PWD=", oldpath);
	ft_export_env(&env_update, data);
	free(env_update.args[1]);
	free(env_update.args);
	free(oldpath);
}

void	remove_char(char **string, int *a, int *b)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (strlen((*string)) - 1));
	if (!(new))
		return ;
	i = -1;
	while ((*string) && (*string)[++i] && i < *a)
		new[i] = (*string)[i];
	while ((*string) && (*string)[i] && (*string)[i + 1] && i + 1 < *b)
	{
		new[i] = (*string)[i + 1];
		i++;
	}
	while ((*string) && (*string)[i] && (*string)[i + 1] && (*string)[i + 2])
	{
		new[i] = (*string)[i + 2];
		i++;
	}
	new[i] = '\0';
	*a = -1;
	*b -= 2;
	free(*string);
	*string = new;
}

void	quote_bin2(char **path, int *strong, int *weak, int *i)
{
	char	*temp;

	temp = *path;
	if ((*path)[*i] == '\'' && *weak == -1)
	{
		if (*strong == -1)
			*strong = *i;
		else
			remove_char(path, strong, i);
	}
	else if ((*path)[*i] == '"' && *strong == -1)
	{
		if (*weak == -1)
			*weak = *i;
		else
			remove_char(path, weak, i);
	}
}

void	quote_bin(char **path, t_data *data)
{
	int		weak;
	int		strong;
	int		i;

	data->quote = 0;
	weak = -1;
	strong = -1;
	i = 0;
	while (path && *path && (*path)[i])
	{
		quote_bin2(path, &strong, &weak, &i);
		i++;
	}
}
