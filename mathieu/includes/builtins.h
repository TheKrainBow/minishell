/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:52 by magostin          #+#    #+#             */
/*   Updated: 2021/02/08 18:41:56 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_print_env(void);
int		ft_export_env(char *name, char *value);
int		ft_env_size(void);
void	ft_malloc_env(void);
void	ft_free_env(void);
int		ft_find_in_env(char *name);
int		ft_unset_env(char *name);

#endif