/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:13:30 by magostin          #+#    #+#             */
/*   Updated: 2021/06/25 14:12:50 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *line)
{
	return (!ft_strcmp(line, ">") || !ft_strcmp(line, ">>")
		|| !ft_strcmp(line, "<")
		|| !ft_strcmp(line, ";") || !ft_strcmp(line, "|"));
}

int	checkout_lexedline(t_data *data)
{
	t_list	*t;

	t = data->lexed_line;
	if (!(t))
		return (0);
	while (t && t->next)
	{
		if (is_redir((char *)t->content) && is_redir((char *)t->next->content))
		{
			printf("Minishell: Syntax error nearby '%s'. '%s' unexepected.\n",
				(char *)t->content, (char *)t->next->content);
			data->wexitstatus = 2;
			return (0);
		}
		t = t->next;
	}
	if (is_redir((char *)t->content) && ft_strcmp(";", (char *)t->content))
	{
		printf("Minishell: Syntax error nearby '%s'. Newline unexepected.\n",
			(char *)t->content);
		data->wexitstatus = 2;
		return (0);
	}
	return (1);
}

int	checkmultiline(char *line, t_data *data)
{
	int		i;

	i = -1;
	data->quote = 0;
	while (line && line[++i])
		if (line[i] == '\'' || line[i] == '\"')
			ft_toggle_quote(line[i], data);
	if (data->quote)
	{
		ft_putstr("Multiline not handled.\n");
		return (0);
	}
	return (1);
}

void	execute_line(char *line, t_data *data)
{
	ft_add_history(data, line);
	lex_line(line, data);
	if (checkout_lexedline(data) && checkmultiline(line, data))
	{
		pars_line_v2(data);
		ft_destroy_pars_line(data);
	}
	else
		ft_free_list(data->lexed_line);
	reset_std(data);
	if (data->index_history)
		free(data->current_cmd);
	data->current_cmd = NULL;
	data->index_history = 0;
	free(line);
}
