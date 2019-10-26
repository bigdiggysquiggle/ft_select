/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 02:14:04 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 02:25:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_stack	*init_stack(void)
{
	struct s_stack	*stack;

	stack = (struct s_stack *)malloc(sizeof(struct s_stack));
	stack->top = NULL;
	return (stack);
}

void			*pop(struct s_stack *stack)
{
	struct s_node	*stuff;
	void			*content;

	content = NULL;
	if (stack && stack->top)
	{
		stuff = stack->top;
		content = stuff->content;
		stack->top = stack->top->next;
		free(stuff);
	}
	return (content);
}

void			push(struct s_stack *stack, void *content)
{
	struct s_node	*top;

	if (stack)
	{
		top = (struct s_node *)malloc(sizeof(struct s_node));
		top->content = content;
		top->next = stack->top;
		stack->top = top;
	}
}

void			*peek(struct s_stack *stack)
{
	void	*content;

	content = NULL;
	if (stack && stack->top)
		content = stack->top->content;
	return (content);
}

int				is_empty(struct s_stack *stack)
{
	return (!stack || !stack->top);
}
