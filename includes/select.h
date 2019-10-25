/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:39:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 23:59:33 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H
# include "libft.h"
# include "termcap.h"
# include "sel_structs.h"
# include "signal.h"
# include "sys/ioctl.h"
# define ULINE "\e[4m"
# define REV "\e[7m"
# define REV_ULINE "\e[4;7m"
# define NORM "\e[m"
# define UP "\e[A"
# define DOWN "\e[B"
# define RIGHT "\e[C"
# define LEFT "\e[D"
# define DEL "\e[3~"
# define BS "\x7f"
# define SPACE " "
# define ESC "\e"
# define ENTER "\n"

t_sel_list		*make_list(int ac, char **av);
t_select		*make_select(t_sel_list *options);
t_select		*store_sel(t_select *sel);
void			free_sel(t_select *sel);
void			sel_signals(void);
void			screen_save_clear(int mode, t_select *sel);

void			print_selected(t_select *sel);
void			ft_do_cap(char *cap);
void			ftgoto(int col, int row);
void			print_opts(t_select *sel);
void			columnize_opts(t_select *sel);
void			del_item(t_select *sel);
void			select_item(t_select *sel);
void			move_hor(t_select *sel, int left);
void			move_ver(t_select *sel, int up);
int				selchar(int c);
int				sel_list_len(t_sel_list *sel);

void			print_assignment(t_select *list);
void			echo_bytes(char *s, int len);

#endif
