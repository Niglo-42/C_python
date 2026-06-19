/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:01:50 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 11:43:00 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tuple/tuple.h"
#include "../list/list.h"
#include "dict.h"

// t_obj *popitem(t_dict *self)
// {
// 	int val;
// 	if (self->size == 0)
// 		return (NULL);
// 	self->size -= 1;
// 	val = ((t_int *)pop(self->items, -1))->val;
// 	self->buffer[val].size--;
// 	return self->buffer[val].members[self->buffer[val].size];
// 	//car on assume que c forcement le dernier
// }

void	set(t_dict *self, t_entry *entry)
{
	size_t	index;

	if (self->size >= self->cap)
		return ;
	index = hash(self, entry->key);
	while (self->tab_entry[index % self->cap] != NULL)
	{
		index++;
	}
	self->tab_entry[index % self->cap] = entry;
	self->size++;
}

t_entry	*get(t_dict *self, const char *key)
{
	t_entry	*entry;
	size_t	index;

	index = hash(self, key);
	while (self->tab_entry[index % self->cap])
	{
		entry = self->tab_entry[index % self->cap];
		if (strcmp(entry->key, key) == 0)
			return (entry);
		index++;
	}
	return (NULL);
}
/* NE PERMET PAS DE DEL DES ELEMENTS !!!! CAR 
L'heuristique c'est que c'est contigue donc on peut chercher
tant que le state est ON, sinon il faudrait continuer de chercher et 
ca repars en O/n */

void	print_entry(t_entry *self)
{
	write(1, self->key, strlen(self->key));
	write(1, ": ", 2);
	print_obj(self->value);
}

t_dict	*copy_dict(t_dict *self, t_arena *arena)
{
	t_dict	*new;
	size_t	i;

	new = new_dict(NULL, self->cap, arena);
	i = 0;
	while (i < self->cap)
	{
		new->tab_entry[i] = self->tab_entry[i];
		i++;
	}
	new->size = self->size;
	return (new);
}
