/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:59:09 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/04/23 14:12:57 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_pipe(int signum)
{
	if (g_pid.pid == 0)
		g_pid.exit_status = 0;
	kill(g_pid.pid, g_pid.exit_status);
	g_pid.exit_status = signum + 128;
}

void	stop_read(int signum)
{
	close(0);
	ft_putendl("^C");
	g_pid.main = 0;
	g_pid.exit_status = signum + 128;
}

void	signals_main(void)
{
	signal(SIGINT, stop_read);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_pipe(void)
{
	signal(SIGINT, ctrl_pipe);
	signal(SIGQUIT, ctrl_pipe);
}
