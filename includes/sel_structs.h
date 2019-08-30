/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:20:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/29 15:24:14 by dromansk         ###   ########.fr       */
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
	int			sel;
	t_sel_list	*next;
};

struct	s_select
{
	int			mcol;
	int			mrow;
	t_sel_list	*options;
	termios_p	*termios;
	int			status;
}

#endif
