/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:46 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/15 22:02:07 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	pwd(void)
{
	char	*path;

	path = NULL;
	if ((path = getcwd(NULL, 0)) == NULL)
		return (-1);
	printf("%s\n", path);
	free(path);
	return (0);
}
