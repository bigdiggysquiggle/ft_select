/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 14:14:30 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int			assign_pos(t_sel_list *start, int len)
{
	struct winsize	ws;
	int				row;
	int				width;
	t_sel_list		*list;

	ioctl(1, TIOCGWINSZ, &ws);
	width = 0;
	row = 0;
	start->col = 0;
	start->row = 0;
	list = start->next;
	while (list != start)
	{
		width += len;
		if (width + len > ws.ws_col)
		{
			row++;
			width = 0;
		}
		list->col = width;
		list->row = row;
		list = list->next;
	}
	return (len > ws.ws_col || start->prev->row + 2 > ws.ws_row ? -1 :
			ws.ws_col / len);
}

int			len_check_lmoa(int len, int cmp)
{
	while (cmp >= len)
		len += 2;
	return (len);
}

void		columnize_opts(t_select *sel)
{
	t_sel_list	*opts;
	int			len;

	len = 2;
	opts = sel->first;
	len = len_check_lmoa(len, opts->len);
	opts = opts->next;
	while (opts != sel->first)
	{
		len = len_check_lmoa(len, opts->len);
		opts = opts->next;
	}
	sel->col_count = assign_pos(sel->first, len);
}
