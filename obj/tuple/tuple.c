#include "tuple.h"
#include "../list/list.h"
#include "../dict/dict.h"

int    count(t_tuple *self, t_obj *elem, t_type type)
{
    if (type == V_STRING)
        return count_str(self, elem, type);
    if (type == V_INT)
        return count_int(self, elem, type);
    if (type == V_FLOAT)
        return count_float(self, elem, type);
    return -1;
}

int    __index__(t_tuple *self, t_obj *elem, t_type type)
{
    if (type == V_STRING)
        return index_str(self, elem, type);
    if (type == V_INT)
        return index_int(self, elem, type);
    if (type == V_FLOAT)
        return index_float(self, elem, type);
    return -1;
}

t_tuple *tuple_new(size_t n, t_arena *arena, va_list data)
{
    size_t  i;
    t_tuple *new;

    i = -1;
    new = (t_tuple *)get_memory(sizeof(t_tuple) + n * sizeof(void *), arena);
    if (!new)
        return (NULL);
    new->size = n;
    new->base.refcnt = 0;
    new->base.type = V_TUP;
    while (++i < n)
    {
        new->members[i] = va_arg(data, t_obj *);
    }
    return new;
}

t_tuple *tup(t_arena *arena, int n, ...)
{
    va_list lst;
    va_start(lst, n);
    return tuple_new(n, arena, lst);
}

void    print_tuple(t_tuple *self)
{
    size_t  i;

    i = 0;
    write(1, "(", 1);
    while (i < self->size)
    {
        print_obj(self->members[i++]);
        write(1, ", ", 2 * (self->size > i));
    }
    write(1, ")", 1);
}

// int main(void)
// {
//     t_tuple *tuple3;
//     t_tuple *tuple;
//     t_arena	*arena;

// 	arena = new_arena();
//     tuple3 = tup(arena, 2, int_new(42, arena), int_new(32, arena));
//     tuple = tup(
//         arena, 6, 
//         str_new("azur", arena), str_new("python", arena),
//         int_new(2147483647, arena), int_new(255, arena), int_new(65535, arena), tuple3
//     );
//     print_tuple(tuple);
//     // dump_arena(arena->block);
//     free_all(arena);
// }