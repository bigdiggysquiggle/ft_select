/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:14:01 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 04:24:52 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			echo_bytes(char *s, int len)
{
	int			i;

	i = 0;
	while (i < len)
		ft_dprintf(STDIN_FILENO, "%hhd\t", s[i++]);
	ft_dprintf(STDIN_FILENO, "\n");
}

void			print_assignment(t_select *list)
{
	t_sel_list	*item;

	item = list->first;
	ft_dprintf(STDIN_FILENO, "%d x %d %s\n", item->col, item->row,
			item->option);
	item = item->next;
	while (item != list->first)
	{
		ft_dprintf(STDIN_FILENO, "%d x %d %s\n", item->col, item->row,
				item->option);
		item = item->next;
	}
}
