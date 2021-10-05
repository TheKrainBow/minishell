/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:04:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 13:22:37 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "minishell.h"

int		enable_canno(struct termios *save);
int		disable_canno(struct termios *save, t_data *data);

void	ft_add_history(t_data *data, char *command);
char	*ft_look_up_history(t_data *data, int direction, char *current);
void	ft_init_history(t_data *data);

void	is_remove(char **line, char buffer[17], t_data *data);
int		is_newline(char buffer[17], t_data *data);
int		is_ctrl(char **line, char buffer[17], t_data *data);
void	is_nothing(char **line, char buffer[17], t_data *data);
int		is_down_arrow(char buffer[17]);
int		is_up_arrow(char buffer[17]);
void	is_arrow(char **line, char buffer[17], t_data *data);

void	delete_char(int x, t_data *data);
int		get_next_command(char **line, t_data *data);

void	signals_main(void);
void	signals_pipe(void);

#endif
