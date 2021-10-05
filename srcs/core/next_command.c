/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:17:47 by magostin          #+#    #+#             */
/*   Updated: 2021/06/25 14:00:54 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

void	delete_char(int x, t_data *data)
{
	int			i;

	i = -1;
	while (++i < x)
		tputs(data->caps->le, 1, ms_putchar);
	tputs(data->caps->ce, 1, ms_putchar);
}

void	prompt_line(char *line, t_data *data)
{
	delete_char(ft_strlen(line), data);
	if (line)
		ft_putstr(line);
}

void	prompt_display(int red)
{
	if (red)
		ft_putstr(RPROMPT);
	else
		ft_putstr(GPROMPT);
}

int	get_next_command(char **line, t_data *data)
{
	char	buffer[17];
	int		ret;

	*line = ft_strdup("");
	prompt_display(data->wexitstatus);
	while (g_pid.main)
	{
		data->printed = 0;
		prompt_line(*line, data);
		ft_memset(buffer, 0, 17);
		ret = read(0, buffer, 16);
		if (ret <= 0)
		{
			dup2(data->fd.stdin_save, 0);
			break ;
		}
		buffer[ret] = 0;
		is_arrow(line, buffer, data);
		is_remove(line, buffer, data);
		if (is_ctrl(line, buffer, data) || is_newline(buffer, data))
			break ;
		is_nothing(line, buffer, data);
	}
	return (1);
}
