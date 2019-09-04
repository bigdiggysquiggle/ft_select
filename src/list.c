/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:35:21 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/04 14:00:20 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** possibility that argv items would get erased under larger memory loads
*/

t_select			*store_sel(t_select *sel)
{
	static t_select *stored;

	if (sel == NULL)
		sel = stored;
	else
		stored = sel;
	return (sel);
}

static t_sel_list	*new_item(char *item)
{
	t_sel_list	*new;

	if ((new = (t_sel_list *)malloc(sizeof(t_sel_list))))
	{
		new->option = item;
		new->col = 0;
		new->row = 0;
		new->len = ft_strlen(item);
		new->sel = 0;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

t_sel_list			*make_list(int ac, char **av)
{
	int			i;
	t_sel_list	*list;
	t_sel_list	*item;

	if (ac > 1)
	{
		i = 0;
		if ((list = new_item(av[++i])))
		{
			item = list;
			while (++i < ac)
			{
				list->next = new_item(av[i]);
				list->next->prev = list;
				list = list->next;
			}
			item->prev = list;;
			return (item);
		}
	}
	return (NULL);
}

t_select			*make_select(t_sel_list *options)
{
	t_select	*sel;
	termios_p	*termios;

	if ((sel = (t_select *)malloc(sizeof(t_select))) && !tcgetattr(0, &termios))
	{
		sel->mcol = 0;
		sel->mrow = 0;
		sel->options = options;
		sel->termios = termios;
		sel->status = 0;
		return (sel);
	}
	return (NULL);
}

void			free_sel(t_select *sel)
{
	t_sel_list	*tmp;

	tmp = sel->options->next->next;
	while (tmp != sel->options)
	{
		free(tmp->prev);
		tmp = tmp->next;
	}
	free(tmp->prev);
	free(tmp);
	free(sel);
}
