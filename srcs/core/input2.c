/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 01:00:19 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:02:49 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_up_arrow(char buffer[17])
{
	char		comp[4];
	char		comp2[4];

	comp[0] = 27;
	comp[1] = '[';
	comp[2] = 'A';
	comp[3] = '\0';
	ft_memcpy(comp2, comp, 4);
	comp2[1] = 79;
	return (!ft_memcmp(buffer, comp, 4) || !ft_memcmp(buffer, comp2, 4));
}

int	is_down_arrow(char buffer[17])
{
	char		comp[4];
	char		comp2[4];

	comp[0] = 27;
	comp[1] = '[';
	comp[2] = 'B';
	comp[3] = '\0';
	ft_memcpy(comp2, comp, 4);
	comp2[1] = 79;
	return (!ft_memcmp(buffer, comp, 4) || !ft_memcmp(buffer, comp2, 4));
}

void	is_arrow(char **line, char buffer[17], t_data *data)
{
	int			dir;

	if (data->printed)
		return ;
	dir = 0;
	if (is_up_arrow(buffer))
		dir = 1;
	else if (is_down_arrow(buffer))
		dir = -1;
	if (dir)
	{
		delete_char(ft_strlen(*line), data);
		*line = ft_look_up_history(data, dir, *line);
		ft_putstr(*line);
		data->printed = 1;
	}
}
