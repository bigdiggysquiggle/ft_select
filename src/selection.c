/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:48:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/03 20:54:57 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	select_item(t_select *sel)
{
}

void	move_hor(t_select *sel, t_sel_list *opt)
{
	char	*s;

	s = tgoto("cm", opt->col, opt->row);
	tputs(s, 1);
	sel->options = opt;
}

void	move_ver(t_select *sel, int up)
{
	int		move;
	char	*s;

	move = 0;
	while (move < sel->col_count)
	{
		sel->options = up ? sel->options->prev : sel->options->next;
		s = tgoto("cm", sel->options->col, sel->options->row);
		tputs(s, 1);
	}
}
