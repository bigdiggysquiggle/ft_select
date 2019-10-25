/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 02:37:26 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static int	assign_pos(t_select *start, int len)
{
	int				row;
	int				width;
	t_sel_list		*list;

	ioctl(STDIN_FILENO, TIOCGWINSZ, start->ws);
	width = 0;
	row = HEAD_PAD;
	start->first->col = 0;
	start->first->row = HEAD_PAD;
	list = start->first->next;
	while (list != start->first)
	{
		width += len;
		if (width + len > start->ws->ws_col)
		{
			row++;
			width = 0;
		}
		list->col = width;
		list->row = row;
		list = list->next;
	}
	return (len > start->ws->ws_col ||
			start->first->prev->row + 2 > start->ws->ws_row ?
			-(start->ws->ws_col / 2) : start->ws->ws_col / len);
}

static int	len_check_lmoa(int len, int cmp)
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
	len = len_check_lmoa(len, opts->len + 1);
	opts = opts->next;
	while (opts != sel->first)
	{
		len = len_check_lmoa(len, opts->len);
		opts = opts->next;
	}
	sel->col_count = assign_pos(sel, len);
}
