/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:18:18 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/02 17:23:34 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_lastcmd_value(char **dest, int *j, t_data *data)
{
	char	*temp;

	temp = ft_itoa(data->wexitstatus);
	if (temp)
	{
		ft_strjoin_to(dest, temp);
		(*j)++;
	}
	free(temp);
}

void	swap_env_str(char **str, int pos, t_data *data)
{
	char	*dest;
	char	*name;
	int		i;
	int		j;

	name = NULL;
	dest = ft_strndup(*str, 0, pos);
	j = 0;
	while (ft_isalnum(*(*str + pos + j + 1)) || (*(*str + pos + j + 1) == '_'))
		j++;
	name = ft_strndup(*str, pos + 1, j);
	if (j && name)
	{
		i = ft_find_in_env(name, data);
		if (i != -1)
			ft_strjoin_to(&dest, ft_strchr(data->temp_environ[i], '=') + 1);
	}
	else if (*(*str + pos + 1) == '?')
		get_lastcmd_value(&dest, &j, data);
	free(name);
	ft_strjoin_to(&dest, *str + pos + 1 + j);
	free(*str);
	*str = dest;
}

void	change_env_str(char **str, t_data *data)
{
	int		i;

	data->quote = 0;
	i = -1;
	while (*str && (*str)[++i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			ft_toggle_quote((*str)[i], data);
		if ((*str)[i] == '$' && data->quote != '\'')
		{
			swap_env_str(str, i, data);
			i = -1;
		}
	}
}

void	apply_env(t_data *data, t_list *parsed_line)
{
	t_list	*temp;
	t_cmd	*cmd;
	int		i;

	temp = parsed_line;
	while (temp)
	{
		cmd = (t_cmd *)temp->content;
		i = -1;
		while (cmd && cmd->args[++i])
			change_env_str(&(cmd->args[i]), data);
		temp = temp->next;
		if (!cmd->piped)
			break ;
	}
}
