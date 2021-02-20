/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:15 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/20 22:33:30 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_option(char *word)
{
	int		i;

	if (!word || word[0] != '-')
		return (0);
	i = 1;
	while (word[i] && word[i] == 'n')
		i++;
	if (i > 1 && word[i] == '\0')
		return (1);
	return (0);
}

int		printing(char *word, t_data *data)
{
	int		strong;
	int		i;
	int		printed;

	strong = 0;
	printed = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\\')
			printed += print_esc(&word[i], &i);
		if (word[i] == '\'')
		{
			strong = (strong + 1) % 2;
			i++;
		}
		if (!strong && word[i] == '$')
			printed += print_var(&word[i], &i, data);
		if (!strong && word[i] == '"')
			i++;
		if (word[i])
		{
			printf("%c", word[i]);
			printed++;
			i++;
		}
	}
	return (printed);
}

void	echo(t_cmd *cmd, t_data *data)
{
	int		i;
	int		printed;
	int		n;

	n = 0;
	i = 1;
	while (ft_option(cmd->args[i]))
		i++;
	if (i != 1)
		n = 1;
	while (cmd->args[i])
	{
		printed = printing(cmd->args[i], data);
		if (cmd->args[++i] && printed)
			printf(" ");
	}
	if (!n)
		printf("\n");
	data->wexitstatus = 0;
}