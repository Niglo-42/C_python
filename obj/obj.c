/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:09:43 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/24 16:22:42 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "list/list.h"
#include "tuple/tuple.h"
#include "dict/dict.h"

void	print_obj(t_obj *obj)
{
	char	s[13];

	if (!obj)
	{
		write(1, "NULL", 4);
		return ;
	}
	memset(s, 0, 13);
	if (obj->type == V_STRING)
		write(1, ((t_string *)obj)->s, ((t_string *)obj)->size);
	else if (obj->type == V_CHR)
		write(1, &((t_chr *)obj)->c, 1);
	else if (obj->type == V_INT)
		ft_itoa(s, ((t_int *)obj)->val, 10);
	else if (obj->type == V_FLOAT)
		ft_itoa(s, ((t_float *)obj)->val, 10);
	else if (obj->type == V_TUP)
		print_tuple((t_tuple *)obj);
	else if (obj->type == V_LIST)
		print_list((t_list *)obj);
	else if (obj->type == V_ENTRY)
		print_entry((t_entry *)obj);
	if (obj->type == V_INT || obj->type == V_FLOAT)
		write(1, s, strlen(s));
}

t_obj	*str_new(char *s, t_arena *arena)
{
	t_string	*new;
	size_t		size;

	size = strlen(s);
	new = (t_string *)get_memory(sizeof(t_string) + size + 1, arena);
	new->base.refcnt = 0;
	new->base.type = V_STRING;
	new->size = size;
	ft_memmove(new->s, s, size + 1);
	return ((t_obj *)new);
}

t_obj	*int_new(int val, t_arena *arena)
{
	t_int	*new;

	new = (t_int *)get_memory(sizeof(t_int), arena);
	new->base.refcnt = 0;
	new->base.type = V_INT;
	new->val = val;
	return ((t_obj *)new);
}

t_obj	*chr_new(char c, t_arena *arena)
{
	t_chr	*new;

	new = (t_chr *)get_memory(sizeof(t_chr), arena);
	new->base.refcnt = 0;
	new->base.type = V_CHR;
	new->c = c;
	return ((t_obj *)new);
}

t_obj	*float_new(float val, t_arena *arena)
{
	t_float	*new;

	new = (t_float *)get_memory(sizeof(t_float), arena);
	new->base.refcnt = 0;
	new->base.type = V_FLOAT;
	new->val = val;
	return ((t_obj *)new);
}
