/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:24 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/25 15:55:12 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "../list/list.h"
#include "../dict/dict.h"

t_obj *get_at_index(t_tuple *self, int index)
{
    if (self->size < 1)
		return (NULL);
    if (index < 0)
		index = (int)self->size + index;
	if (index >= (int)self->size || self->size == 0 || index < 0) 
        return (display_error("Out_of_Range index: ", &index, 10), NULL);
    return (self->members[index]);
}