/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:34 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 10:42:59 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

int	index_str(t_tuple *self, t_obj *elem, t_type type)
{
	size_t	i;
	int		res;

	i = -1;
	res = -1;
	while (++i < self->size)
	{
		if (self->members[i]->type == V_TUP)
		{
			res = __index__((t_tuple *)self->members[i], elem, type);
			if (res != -1)
				return (i);
		}
		if (self->members[i]->type == type)
			if (strcmp(((t_string *)self->members[i])->s,
					((t_string *)elem)->s) == 0)
				return (i);
	}
	return (-1);
}

int	index_int(t_tuple *self, t_obj *elem, t_type type)
{
	size_t	i;
	int		res;

	i = -1;
	res = -1;
	while (++i < self->size)
	{
		if (self->members[i]->type == V_TUP)
		{
			res = __index__((t_tuple *)self->members[i], elem, type);
			if (res != -1)
				return (i);
		}
		if (self->members[i]->type == type)
			if (((t_int *)self->members[i])->val == ((t_int *)elem)->val)
				return (i);
	}
	return (-1);
}

int	index_float(t_tuple *self, t_obj *elem, t_type type)
{
	size_t	i;
	int		res;

	i = -1;
	res = -1;
	while (++i < self->size)
	{
		if (self->members[i]->type == V_TUP)
		{
			res = __index__((t_tuple *)self->members[i], elem, type);
			if (res != -1)
				return (i);
		}
		if (self->members[i]->type == type)
			if (((t_float *)self->members[i])->val == ((t_float *)elem)->val)
				return (i);
	}
	return (-1);
}
