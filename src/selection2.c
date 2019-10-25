/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 01:40:48 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 02:38:09 by dromansk         ###   ########.fr       */
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

static void	sec_gen(char ***tab)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * 11);
	new[0] = "   )\" .";
	new[1] = "  /    \\      (\\-./";
	new[2] = " /     |    _/ o. \\";
	new[3] = "|      | .-\"      y)-";
	new[4] = "|      |/       _/ \\";
	new[5] = "\\     /j   _\".\\(@)";
	new[6] = " \\   ( |    `.''  )";
	new[7] = "  \\  _`-     |   /";
	new[8] = "    \"  `-._  <_ (";
	new[9] = "           `-.,),)";
	new[10] = NULL;
	*tab = new;
}

void		secret(t_select *sel)
{
	int				row;
	int				col;
	char			**tab;
	int				i;

	ioctl(STDIN_FILENO, TIOCGWINSZ, sel->ws);
	if (sel->ws->ws_col > 22 && sel->ws->ws_row > 12)
	{
		i = 0;
		sec_gen(&tab);
		ft_do_cap("cl");
		col = sel->ws->ws_col / 2 - 11;
		row = sel->ws->ws_row / 2 - 6;
		while (tab[i])
		{
			ftgoto(col, row++);
			ft_dprintf(STDIN_FILENO, "%s", tab[i++]);
		}
		free(tab);
	}
}
