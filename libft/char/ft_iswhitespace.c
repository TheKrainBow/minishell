/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:38:53 by magostin          #+#    #+#             */
/*   Updated: 2024/05/16 18:43:40 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespace(int c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\t'
		|| c == '\n'
		|| c == '\r'
		|| c == '\v');
}