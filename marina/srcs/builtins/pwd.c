/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marina <marina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:45:52 by marina            #+#    #+#             */
/*   Updated: 2021/01/26 15:59:25 by marina           ###   ########.fr       */
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
