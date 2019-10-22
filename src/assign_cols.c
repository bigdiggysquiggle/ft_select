/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 12:43:09 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** data[0] = i
** data[1] = len
** data[2] = col_num
*/

void		assign_every_i(t_sel_list *first, t_sel_list *opts, int *data)
{
	t_sel_list	*curr;
	int			count;
	int			row;

	count = 1;
	row = 1;
//	ft_printf("%s\n", opts->option);//
	opts->col = data[2];
	opts->row = 0;
	curr = opts->next;
//	ft_printf("%d %d\n", data[0], data[2]);//
	while (curr != first)
	{
		if (!(count % data[0]))
		{
			curr->col = data[2];
			curr->row = row++ * data[1];
		}
		curr = curr->next;
		count++;
	}
}

void		assign_pos(t_select *sel, int cols, int len, int x)
{
	t_sel_list	*opts;
	int			counter;
	int			data[3];

	data[1] = len;
	opts = sel->options;
	counter = 1;
	sel->col_count = cols;
//	ft_printf("count %d\n", cols);//
	cols = x ? cols + 1 : cols;
	data[0] = cols;
	while (counter <= cols)
	{
		data[2] = counter - 1;
		assign_every_i(sel->options, opts, data);
		opts = opts->next;
		counter++;
	}
}

void		column_count(t_select *sel, int len)
{
	struct winsize	ws;
	int				size;
	int				cols;

	cols = 1;
	ioctl(1, TIOCGWINSZ, &ws);
//	ft_printf("winsize %d x %d\n", ws.ws_row, ws.ws_col);//
	size = ws.ws_row;
	if (size > len)
		cols = size / len;
//	ft_printf("columns %d\n", cols);//
	assign_pos(sel, cols, len, size % len);
}

int			len_check_lmoa(int len, int cmp)
{
	while (cmp >= len)
		len += 4;
	return (len);
}

int			columnize_opts(t_select *sel)
{
	t_sel_list	*opts;
	int			len;

	len = 4;
	len = len_check_lmoa(len, sel->options->len - 1);
	opts = sel->options->next;
	while (opts != sel->options)
	{
		len = len_check_lmoa(len, opts->len - 1);
		opts = opts->next;
	}
//	ft_printf("%d\n", len);//
	column_count(sel, len);
//	print_assignment(sel->options);//
	return (len);
}
