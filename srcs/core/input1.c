/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:59:49 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:01:13 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_remove(char **line, char buffer[17], t_data *data)
{
	if (data->printed)
		return ;
	if (buffer[0] == 127)
	{
		delete_char(ft_strlen(*line), data);
		if (*line && (*line)[0])
			ft_strtrunc(line, 1);
		ft_putstr(*line);
		data->printed = 1;
	}
}

int	is_newline(char buffer[17], t_data *data)
{
	if (data->printed)
		return (0);
	if (buffer[0] == '\n')
	{
		ft_putchar('\n');
		data->printed = 1;
		return (1);
	}
	return (0);
}

int	is_ctrl(char **line, char buffer[17], t_data *data)
{
	char		*temp;

	if (data->printed)
		return (0);
	if (buffer[0] == 4)
	{
		data->printed = 1;
		temp = *line;
		if ((*line) && (*line)[0] == 0)
		{
			*line = ft_strdup("exit");
			ft_putstr(*line);
			ft_putchar('\n');
			free(temp);
			return (1);
		}
	}
	return (0);
}

void	is_nothing(char **line, char buffer[17], t_data *data)
{
	if (data->printed)
		return ;
	data->printed = 1;
	buffer[1] = 0;
	ft_strjoin_to(line, buffer);
	ft_putchar(buffer[0]);
}
