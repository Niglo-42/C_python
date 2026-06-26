#ifndef TUPLE_H
# define TUPLE_H
# include "../obj.h"
# include "../../runtime/arena.h"

typedef struct s_tuple
{
	t_obj	base;
	size_t	size;
	t_obj	**members;
}	t_tuple;

int		count(t_tuple *self, t_obj *elem, t_type type);
int		__index__(t_tuple *self, t_obj *elem, t_type type);
t_tuple	*tuple_new(size_t n, t_arena *arena, va_list data);

int		index_float(t_tuple *self, t_obj *elem, t_type type);
int		index_int(t_tuple *self, t_obj *elem, t_type type);
int		index_str(t_tuple *self, t_obj *elem, t_type type);

int		count_str(t_tuple *self, t_obj *elem, t_type type);
int		count_int(t_tuple *self, t_obj *elem, t_type type);
int		count_float(t_tuple *self, t_obj *elem, t_type type);

t_tuple	*tup(t_arena *arena, int n, ...);
void	print_tuple(t_tuple *self);
t_obj	*get_at_index(t_tuple *self, int index);
#endif
