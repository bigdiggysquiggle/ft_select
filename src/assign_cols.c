/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/03 20:31:57 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		assign_every_i(t_sel_list *opts, int i, int len, int col_num)
{
	t_sel_list *curr;
	int			count;
	int			row;

	count = 1;
	row = 1;
	opts->col = col_num * len;
	opts->row = 0;
	curr = opts->next;
	while (curr != opts)
	{
		if (!(count % i))
		{
			curr->col = col_num * len;
			curr->row = row++;
		}
		curr = curr->next;
		count++;
	}
}

void		assign_pos(t_select *sel, int cols, int size, int len)
{
	t_sel_list	*opts;
	int			counter;
	int			i;

	opts = sel->options;
	counter = 1;
	i = size / cols;
	if (size % cols)
		i++;
	sel->col_count = i;
	while (counter <= i)
	{
		assign_every_i(opts, i, len, counter - 1);
		opt = opt->next;
		counter++;
	}
}

void		column_count(t_select *sel, int len, int count)
{
	struct winsize	ws;
	int				size;
	int				cols;

	cols = 1;
	ioctl(1, TIOCGWINSZ, &ws);
	size = ws.ws_col;
	if (size > len)
		cols = size / len;
	assign_pos(sel, cols, count, len);
}

int			len_check_lmoa(int len, int cmp)
{
	while (cmp >= len)
		len += 4;
	return (len);
}

void		columnize_opts(t_select *sel)
{
	t_sel_list	*start;
	t_sel_list	*opts;
	int			len;
	int			count;

	len = 4;
	count = 0;
	opts = sel->options;
	start = opts;
	while (opts != start)
	{
		count++;
		len = len_check_lmoa(len, opts->len - 1);
		opts = opts->next;
	}
	column_count(sel, len, count);
}
