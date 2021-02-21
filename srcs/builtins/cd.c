/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:26 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/21 19:38:10 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_char(char *string, int *a, int *b)
{
	int		i;
	char	*new;

	if (!(new = malloc(sizeof(char) * (strlen(string) - 1))))
		return (NULL);
	i = 0;
	while (string && string[i] && i < *a)
	{
		new[i] = string[i];
		i++;
	}
	while (string && string[i] && i + 1 < *b)
	{
		new[i] = string[i + 1];
		i++;
	}
	while (string && string[i])
	{
		new[i] = string[i + 2];
		i++;
	}
	new[i] = '\0';
	*a = -1;
	*b -= 2;
	return (new);
}

char	*quote_bin(char *path)
{
	int		weak;
	int		strong;
	int		i;

	weak = -1;
	strong = -1;
	i = 0;
	while (path && path[i])
	{
		if (path[i] == '\'' && weak == -1)
		{
			if (strong >= 0)
				path = remove_char(path, &strong, &i);
			else
				strong = i;
		}
		else if (path[i] == '"' && strong == -1)
		{
			if (weak >= 0)
				path = remove_char(path, &weak, &i);
			else
				weak = i;
		}
		i++;
	}
	return (path);
}

char	*get_path_in_env(void)
{
	int		index;
	char	*path;

	path = NULL;
	index = ft_find_in_env("HOME");
	if (index >= 0)
		path = ft_strchr( __environ[index], '=') + 1;
	return (path);
}

void	cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[1] && (cmd->args[1][0] != '~' || cmd->args[1][1]))
		path = quote_bin(cmd->args[1]);
	else
		path = get_path_in_env();
	data->wexitstatus = chdir(path);
}

/*tester comment se comporte chdir avec path = "~" et path = NULL;*/