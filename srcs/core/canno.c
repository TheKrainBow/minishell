/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:53:41 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:02:57 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enable_canno(struct termios *save)
{
	struct termios		new;

	g_pid.exit_status = 0;
	signals_main();
	tcgetattr(0, &new);
	tcgetattr(0, save);
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	return (!tcsetattr(0, TCSANOW, &new));
}

int	disable_canno(struct termios *save, t_data *data)
{
	signals_pipe();
	if (g_pid.exit_status)
		data->wexitstatus = g_pid.exit_status;
	return (!tcsetattr(STDIN_FILENO, TCSANOW, save));
}
