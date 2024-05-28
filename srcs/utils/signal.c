/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:47:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 00:14:38 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_pipe(int signum)
{
	if (g_pid == 0)
		g_pid.exit_status = 0;
	kill(g_pid, g_pid.exit_status);
	g_pid.exit_status = signum + 128;
}

void	stop_read(int signum)
{
	close(0);
	ft_putendl("^C");
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
