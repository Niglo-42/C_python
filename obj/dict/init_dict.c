#include "dict.h"

t_dict	*new_dict(t_dict *src, size_t len, t_arena *arena)
{
	t_dict	*self;

	self = (t_dict *)get_memory(
			sizeof(t_dict) + len * sizeof(t_entry *), arena);
	memset(self->tab_entry, 0, len * sizeof(t_entry *));
	self->base.refcnt = 0;
	self->base.type = V_DICT;
	if (src == NULL)
		self->size = 0;
	else
	{
		self->size = src->size;
		self->base.type = src->base.type;
		ft_memcpy(self->tab_entry, src->tab_entry, len * sizeof(t_entry *));
	}
	self->cap = len;
	return (self);
}

static int	is_last_entry(t_entry **entry, size_t i, size_t cap)
{
	while (i < cap)
		if (entry[i++] != NULL)
			return (0);
	return (1);
}

void	print_dict(t_dict *self)
{
	size_t	i;
	t_entry	*entry;

	i = 0;
	if (!self)
		return ;
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

t_entry	*new_entry(const char *key, t_obj *val, t_arena *arena)
{
	t_entry	*new;

	new = (t_entry *)get_memory(sizeof(t_entry), arena);
	new->base.type = V_ENTRY;
	new->key = key;
	new->state = 1;
	new->value = val;
	return (new);
}
