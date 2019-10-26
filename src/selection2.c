/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 01:40:48 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 04:11:44 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		select_all(t_select *sel, int mode)
{
	t_sel_list	*list;

	list = sel->first;
	list->sel = mode;
	list = list->next;
	while (list != sel->first)
	{
		list->sel = mode;
		list = list->next;
	}
	print_opts(sel);
}

void		print_secret(t_select *sel, char **tab, int start)
{
	int				i;
	int				row;
	int				col;

	ioctl(STDIN_FILENO, TIOCGWINSZ, sel->ws);
	if (sel->ws->ws_col > 22 && sel->ws->ws_row > 12)
	{
		i = 0;
		col = sel->ws->ws_col / 2 - 11;
		row = start ? start : sel->ws->ws_row / 2 - 6;
		while (tab[i])
		{
			ftgoto(col, row++);
			ft_dprintf(STDIN_FILENO, "%s", tab[i++]);
		}
	}
}

void		secret(t_select *sel)
{
	char			*tab[11];

	tab[0] = "   )\" .";
	tab[1] = "  /    \\      (\\-./";
	tab[2] = " /     |    _/ o. \\";
	tab[3] = "|      | .-\"      y)-";
	tab[4] = "|      |/       _/ \\";
	tab[5] = "\\     /j   _\".\\(@)";
	tab[6] = " \\   ( |    `.''  )";
	tab[7] = "  \\  _`-     |   /";
	tab[8] = "    \"  `-._  <_ (";
	tab[9] = "           `-.,),)";
	tab[10] = NULL;
	print_secret(sel, tab, 0);
}

void		undel_item(t_select *sel)
{
	t_sel_list	*add;
	t_sel_list	*next;
	t_sel_list	*prev;

	if (!is_empty(sel->del))
	{
		add = (t_sel_list *)pop(sel->del);
		next = add->next;
		prev = add->prev;
		next->prev = add;
		prev->next = add;
	}
}
