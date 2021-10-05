/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:15 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:33:24 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing2(char **word, int *strong, int *i, int *printed)
{
	if ((*word)[*i] == '\\')
		*printed += print_esc(word[*i], i);
	if ((*word)[*i] == '\'')
	{
		*strong = (*strong + 1) % 2;
		*i += 1;
	}
	if (!*strong && (*word)[*i] == '"')
		*i += 1;
}

int	printing(char **word, t_data *data)
{
	int		strong;
	int		i;
	int		printed;

	strong = 0;
	printed = 0;
	i = 0;
	quote_bin(word, data);
	while (word && *word && (*word)[i])
	{
		if ((*word)[i])
		{
			ft_putchar((*word)[i]);
			printed++;
			i++;
		}
	}
	return (printed);
}

void	ft_echo(t_cmd *cmd, t_data *data)
{
	int		i;
	int		printed;
	int		n;
	char	*temp;

	n = 0;
	i = 1;
	while (ft_option(cmd->args[i]))
		i++;
	if (i != 1)
		n = 1;
	while (cmd->args[i])
	{
		temp = ft_strdup(cmd->args[i]);
		printed = printing(&temp, data);
		if (cmd->args[++i] && printed)
			ft_putchar(' ');
		free(temp);
	}
	if (!n)
		ft_putchar('\n');
	data->wexitstatus = 0;
}
