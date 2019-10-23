/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 13:17:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		assign_coordinates(t_sel_list *opts, int i, int len, int row)
{
	t_sel_list	*curr;
	int			count;
	int			col;

	count = 1;
	col = 1;
//	ft_printf("%s\n", opts->option);//
	opts->row = row;
	opts->col = 0;
	curr = opts->next;
//	ft_printf("%d %d\n", row, i);//
	while (curr != opts)
	{
		if (!(count % i))
		{
			curr->row = row;
			curr->col = col++ * len;
		}
		curr = curr->next;
		count++;
	}
}

void		assign_pos(t_sel_list *list, int i, int len)
{
	int			counter;
	int			row_num;

	counter = 1;
//	ft_printf("i   %d\n", i);//
	while (counter <= i)
	{
		row_num = counter - 1;
//		ft_printf("row %d\n", row_num);
		assign_coordinates(list, i, len, row_num);
		list = list->next;
		counter++;
	}
}

int			column_count(t_sel_list *sel, int len)
{
	struct winsize	ws;
	int				width;
	int				cols;
	int				i;

	ioctl(1, TIOCGWINSZ, &ws);
//	ft_printf("winsize %d x %d\n", ws.ws_row, ws.ws_col);//
	width = ws.ws_col;
	cols = width > len ? width / len : -1;
//	ft_printf("columns %d / %d = %d\n", width, len, cols);//
	i = sel_list_len(sel);
	i = cols % i ? cols / i + 1 : cols / i;
	assign_pos(sel, i, len);
	return (cols);
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
//	ft_printf("%d\n", len);//
	sel->col_count = column_count(sel->first, len);
//	print_assignment(sel->first);//
//	exit(1);//
}
