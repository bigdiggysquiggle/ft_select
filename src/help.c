/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:36:29 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 03:48:39 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static void	help_sql(t_select *sel, int height)
{
	char			*tab[11];

	tab[0] = "   )\" .              | /";
	tab[1] = "  /    \\      (\\-./  |/";
	tab[2] = " /     |    _/ o. \\";
	tab[3] = "|      | .-\"      y)-";
	tab[4] = "|      |/       _/ \\";
	tab[5] = "\\     /j   _\".\\(@)";
	tab[6] = " \\   ( |    `.''  )";
	tab[7] = "  \\  _`-     |   /";
	tab[8] = "    \"  `-._  <_ (";
	tab[9] = "           `-.,),)";
	tab[10] = NULL;
	print_secret(sel, tab, height);
}

static void	print_controls(t_select *sel, char **tab)
{
	int	i;
	int	width;
	int	row;

	i = 0;
	width = 3;
	row = 1;
	while (tab[i])
	{
		if (width + LONGEST > sel->ws->ws_col)
		{
			row++;
			width = 3;
		}
		ftgoto(width, row);
		ft_putstr_fd(tab[i++], STDIN_FILENO);
		width += LONGEST;
	}
}

static void	help_printing(int width, int cols, t_select *sel, char **tab)
{
	int	height;
	int	i;

	height = CONTROLS % cols ? (CONTROLS / cols) + 1 : CONTROLS / cols;
	ftgoto(0, 0);
	repchar('_', width);
	i = 0;
	while (i++ < height)
	{
		ftgoto(0, i);
		write(STDIN_FILENO, "|", 1);
		ftgoto(width, i);
		write(STDIN_FILENO, "|", 1);
	}
	ftgoto(0, i);
	repchar('_', width);
	if (sel->ws->ws_row - (height + 2) > 10)
		help_sql(sel, height + 2);
	print_controls(sel, tab);
	ft_dprintf(STDIN_FILENO, "{eoc}");
}

static void	construct_window(t_select *sel, char **tab)
{
	int	width;
	int	cols;

	width = sel->ws->ws_col - 1;
	cols = (width - 4) / LONGEST;
	if (!cols)
	{
		ftgoto(sel->ws->ws_col / 2 - 10, sel->ws->ws_row / 2);
		ft_dprintf(STDERR_FILENO, "Window tooo smoll :(");
	}
	else
		help_printing(width, cols, sel, tab);
}

void		print_help(t_select *sel)
{
	char	*tab[CONTROLS + 1];

	ft_do_cap("cl");
	tab[0] = "Arrows: move cursor";
	tab[1] = "Space: select item";
	tab[2] = "A/D: select/deselect all";
	tab[3] = "I: invert selections";
	tab[4] = "Del/Backspace: remove item";
	tab[5] = "U: undo deletion";
	tab[6] = "Enter: quit, print selection";
	tab[7] = "Esc: quit without printing";
	tab[CONTROLS - 1] = "S: secret";
	tab[CONTROLS] = NULL;
	ft_dprintf(STDIN_FILENO, "{yellow}");
	construct_window(sel, tab);
}
