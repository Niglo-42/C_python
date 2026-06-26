#include "../list/list.h"
#include "../dict/dict.h"
#include "../tuple/tuple.h"
#include "../obj.h"

static t_obj	*for_str(t_obj *iter, t_arena *arena)
{
	static size_t	rsp = 0;
	t_string		*s;

	s = (t_string *)iter;
	if (rsp < s->size)
		return (chr_new(s->s[rsp++], arena));
	rsp = 0;
	return (NULL);
}

static t_obj	*for_lst(t_obj *iter)
{
	static size_t	rsp = 0;
	t_list			*list;

	list = (t_list *)iter;
	if (rsp < list->size)
		return (list->members[rsp++]);
	rsp = 0;
	return (NULL);
}

static t_obj	*for_tup(t_obj *iter)
{
	static size_t	rsp = 0;
	t_tuple			*tuple;

	tuple = (t_tuple *)iter;
	if (rsp < tuple->size)
		return (tuple->members[rsp++]);
	rsp = 0;
	return (NULL);
}

static t_obj	*for_dict(t_obj *iter)
{
	static size_t	rsp = 0;
	t_dict			*dict;

	dict = (t_dict *)iter;
	while (dict->tab_entry[rsp] == NULL && rsp < dict->cap)
		rsp++;
	if (rsp < dict->cap)
		return ((t_obj *)dict->tab_entry[rsp++]);
	rsp = 0;
	return (NULL);
}

t_obj	*for_each(t_obj *iter, t_arena *arena)
{
	t_type	x;

	x = iter->type;
	if (x == V_STRING)
		return (for_str(iter, arena));
	else if (x == V_LIST)
		return (for_lst(iter));
	else if (x == V_TUP)
		return (for_tup(iter));
	else if (x == V_DICT)
		return (for_dict(iter));
	else
		display_error("obj int or float is not iterable", NULL, 10);
	return (NULL);
}
/*
	NE GERE ABSOLUEMENT PAS LES ITER MULTIPLES !! SORRY
*/
