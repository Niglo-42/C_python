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


void	set(t_dict *self, t_arena *arena, t_entry *entry)
{
	size_t index;

	if (self->size >= self->cap)
	{
		self->cap <<= 1;
		self = copy_dict(self, arena);
	}
	self->size += 1;
	index = hash(self, entry->key);
	if (self->tab_entry[index] != NULL)
		index += 1;
	self->tab_entry[index] = entry;
}

t_entry *get(t_dict *self, const char *key)
{
	t_entry	*entry;
	size_t	index;

	index = hash(self, key);
	entry = self->tab_entry[index];
	while(1)
	{
		entry = self->tab_entry[index % self->cap];
		if (entry->state == 0)
			break ;
		if (strcmp(entry->key, key) == 0)
			return (entry);
		index += 1;
	}
	return (NULL);
}
/* NE PERMET PAS DE DEL DES ELEMENTS !!!! CAR 
L'heuristique c'est que c'est contigue donc on peut chercher
tant que le state est ON, sinon il faudrait continuer de chercher et 
ca repars en O/n */

int	is_last_entry(t_entry **entry, size_t i, size_t cap)
{
	while (i < cap)
		if (entry[i++] != NULL)
			return (0);
	return (1);
}

void	print_entry(t_entry *self)
{
	write(1, self->key, strlen(self->key));
	write(1, ": ", 2);
	print_obj(self->value);
}

void	print_dict(t_dict *self)
{
	size_t 	i;
	t_entry	*entry;

	i = 0;
	write(1, "{", 1);
	while (i < self->cap)
	{
		entry = self->tab_entry[i];
		if (entry != NULL)
		{
			write(1, entry->key, strlen(entry->key));
			write(1, ": ", 2);
			if (is_last_entry(self->tab_entry, i + 1, self->cap))
				i = self->cap;
			print_obj(entry->value);
			write(1, ", ", 2 * (self->cap > i));
		}
		i++;
	}
	write(1, "}\n", 2);
}

t_dict  *copy_dict(t_dict *self, t_arena *arena)
{
	t_dict  *new__dict;

	new__dict = new_dict(self, self->cap, arena);
	return (new__dict);
}

// int main(void)
// {
//     t_dict  *dict;
// 	t_arena	*arena;

// 	arena = new_arena();

//     dict = new_dict(NULL, 10, arena);
//     set(dict, arena, new_entry("clef", int_new(42, arena), arena));
// 	set(dict, arena, new_entry(
// 		"clef2", (t_obj *)tup(arena, 2, int_new(52, arena), int_new(62, arena)), arena));
//     print_dict(dict);
// 	free_all(arena);
// }