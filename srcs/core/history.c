/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:51:17 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:02:06 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_history(t_data *data)
{
	int	i;

	data->index_history = 0;
	i = 0;
	while (i < SIZE_HISTORY)
	{
		data->history[i] = NULL;
		i++;
	}
}

void	ft_add_history(t_data *data, char *command)
{
	int		i;

	if (!command || !command[0])
		return ;
	i = SIZE_HISTORY - 1;
	if (data->history[i])
	{
		free(data->history[i]);
		data->history[i] = NULL;
	}
	while (i > 1)
	{
		data->history[i] = data->history[i - 1];
		i--;
	}
	data->history[1] = ft_strdup(command);
}

void	ft_rm_history(t_data *data)
{
	int	i;

	i = -1;
	free(data->history[0]);
	while (++i < SIZE_HISTORY - 1)
		data->history[i] = data->history[i + 1];
	free(data->history[i]);
	data->history[i] = NULL;
}

char	*ft_look_up_history(t_data *data, int direction, char *current)
{
	if (data->index_history == 0)
		data->current_cmd = ft_strdup(current);
	if (current)
		free(current);
	if (data->index_history + direction < SIZE_HISTORY
		&& data->index_history + direction >= 0
		&& (data->history[data->index_history + direction]
			|| data->index_history + direction == 0))
		data->index_history += direction;
	if (data->index_history == 0)
		return (data->current_cmd);
	return (ft_strdup(data->history[data->index_history]));
}
