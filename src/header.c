/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:36:29 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 20:56:18 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static void	repchar(char c, int i)
{
	while (i--)
		write(STDIN_FILENO, &c, 1);
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

static void	construct_window(t_select *sel, char **tab)
{
	int	width;
	int	cols;
	int	height;
	int	i;

	width = sel->ws->ws_col - 1;
	cols = (width - 4) / LONGEST;
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
	sel->head = height + 3;
	print_controls(sel, tab);
}

void		print_header(t_select *sel)
{
	char	*tab[CONTROLS + 1];

	tab[0] = "Arrows: move cursor";
	tab[1] = "Space: select item";
	tab[2] = "A/D: select/deselect all";
	tab[3] = "I: invert selections";
	tab[4] = "Del/Backspace: remove item";
	tab[5] = "Enter: quit, print selection";
	tab[6] = "Esc: quit without printing";
	tab[CONTROLS - 1] = "S: secret ;)";
	tab[CONTROLS] = NULL;
	construct_window(sel, tab);
}
