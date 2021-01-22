/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:07:23 by magostin          #+#    #+#             */
/*   Updated: 2021/01/22 11:09:22 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	char	*arg[] = {"/bin/ls", "./", NULL};
	pid_t	fork_return;
	int		ret;

	fork_return = fork();
	if (!fork_return)
	{
		execve("/bin/ls", arg, __environ);
		exit(1);
	}
	else
		waitpid(fork_return, &ret, 0);
	if (WIFEXITED(ret))
		printf("%d\n", WEXITSTATUS(ret));
	else
		printf("Fatal Error\n");
}