/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:20:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/03 20:26:11 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEL_STRUCTS_H
# define SEL_STRUCTS_H

typedef struct s_sel_list	t_sel_list;
typedef struct s_select		t_select;

struct	s_sel_list
{
	char		*option;
	int			col;
	int			row;
	int			len;
	int			sel;
	t_sel_list	*next;
	t_sel_list	*prev;
};

struct	s_select
{
	int			mcol;
	int			mrow;
	int			col_count;
	t_sel_list	*options;
	termios_p	*termios;
	int			status;
}

#endif
