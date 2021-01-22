/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/01/22 10:57:20 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (str && *str)
	{
		ft_putchar(*str);
		str++;
	}
}

int		check_line(char *line)
{
	while (line && *line)
	{
		if (*line == ';' && (line + 1) && *(line + 1) == ';')
			return (0);
		line++;
	}
	return (1);
}
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int		main(void)
{
	char	*line;
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

	
	ret = 1;
	while (ret > 0)
	{
		ft_putstr("\033[4m\033[36;1mMinishell \033[1;31m>:\033[0m ");
		ret = get_next_line(0, &line);
		printf("%s\n", line);
		free(line);
	}
	return (42);
}