/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:14:01 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 14:13:45 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			echo_bytes(char *s, int len)
{
	int		i;

	i = 0;
	while (i < len)
		ft_printf("%d\t", s[i++]);
	ft_printf("\n");
}

void			print_assignment(t_sel_list *list)
{
	t_sel_list	*item;

	ft_printf("%d x %d %s\n", list->col, list->row, list->option);
	item = list->next;
	while (item != list)
	{
		ft_printf("%d x %d %s\n", item->col, item->row, item->option);
		item = item->next;
	}
}
