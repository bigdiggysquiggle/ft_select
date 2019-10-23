/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:13:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 15:03:00 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** data[0] = i
** data[1] = len
** data[2] = row
*/

void		assign_coordinates(t_sel_list *first, t_sel_list *opts, int *data)
{
	int			count;
	int			col;

	count = 1;
	col = 1;
//	ft_printf("%s\n", opts->option);//
	opts->row = data[2];
	opts->col = 0;
//	ft_printf("row %d i %d\n", data[2], data[0]);//
	opts = opts->next;
	while (opts != first)
	{
//		ft_printf("\tcount %d %% i %d = %d\n", count, data[0], count % data[0]);//
		if (!(count % data[0]))
		{
			opts->row = data[2];
			opts->col = col++ * data[1];
//			ft_printf("\tcol %d row %d %s\n", opts->col, opts->row, opts->option);//
		}
		opts = opts->next;
		count++;
	}
//	printf("first\n\t");//
//	print_assignment(first);//
//	printf("opts\n\t");//
//	print_assignment(opts);//
//	printf("\n");//
}

void		assign_pos(t_sel_list *first, int i, int len)
{
	int			counter;
	int			data[3];
	t_sel_list	*list;

	counter = 1;
	list = first;
//	ft_printf("i   %d\n", i);//
//	ft_printf("first %s\n", list->option);//
	data[0] = i;
	data[1] = len;
	while (counter <= i)
	{
		data[2] = counter - 1;
//		ft_printf("row %d\n", data[2]);//
		assign_coordinates(first, list, data);
		list = list->next;
		counter++;
	}
}

int			column_count(t_sel_list *sel, int len)
{
	struct winsize	ws;
	int				width;
	int				cols;
	int				count;

	ioctl(1, TIOCGWINSZ, &ws);
//	ft_printf("winsize %d x %d\n", ws.ws_row, ws.ws_col);//
	width = ws.ws_col;
	cols = width > len ? width / len : -1;
//	ft_printf("columns %d / %d = %d\n", width, len, cols);//
	count = sel_list_len(sel);
//	ft_printf("every i %d / %d = %d\n", cols, count, count % cols ? (count / cols) + 1 : count / cols);//
	assign_pos(sel, count % cols ? (count / cols) + 1 : count / cols, len);
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
