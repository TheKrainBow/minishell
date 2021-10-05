/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:27:14 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_pid;

int	init_termcaps(t_data *data)
{
	data->caps = malloc(sizeof(t_caps));
	if (tgetent(NULL, "xterm-256color") <= 0)
		return (1);
	data->caps->reset = tgetstr("me", NULL);
	data->caps->le = tgetstr("le", NULL);
	data->caps->nd = tgetstr("nd", NULL);
	data->caps->dl = tgetstr("dl", NULL);
	data->caps->sc = tgetstr("sc", NULL);
	data->caps->rc = tgetstr("rc", NULL);
	data->caps->ce = tgetstr("ce", NULL);
	return (0);
}

void	minishell(t_data *data)
{
	char				*line;
	struct termios		save;
	int					ret;

	ret = 1;
	while (ret)
	{
		g_pid.main = 1;
		enable_canno(&save);
		ret = get_next_command(&line, data);
		disable_canno(&save, data);
		if (!g_pid.main)
			free(line);
		if (!g_pid.main)
			continue ;
		execute_line(line, data);
	}
}

int	main(void)
{
	t_data				*data;

	data = malloc(sizeof(t_data));
	data->path = NULL;
	data->temp_environ = NULL;
	ft_malloc_env(data);
	ft_update_path(data);
	if (init_termcaps(data))
		return (1);
	data->fd.stdin_save = dup(0);
	data->fd.stdout_save = dup(1);
	data->current_cmd = NULL;
	data->pid = NULL;
	data->wexitstatus = 0;
	ft_init_history(data);
	minishell(data);
	ft_free_env(data);
	close(data->fd.stdin_save);
	close(data->fd.stdout_save);
	return (0);
}
