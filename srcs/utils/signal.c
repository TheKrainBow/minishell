/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:47:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 14:27:30 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
}

void	main_sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_main(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_pipe(void)
{
	signal(SIGINT, pipe_sigint);
	signal(SIGQUIT, pipe_sigint);
}
