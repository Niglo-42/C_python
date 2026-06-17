#include "list.h"
#include "../tuple/tuple.h"
#include "../dict/dict.h"

t_list *list_new(size_t n, t_arena *arena, va_list data)
{
    size_t  i;
    t_list *self;

    i = -1;
    self = (t_list *)get_memory(sizeof(t_list) + (n * 2) * sizeof(t_obj *), arena);
    if (!self)
        return (NULL);
    self->cap = n * 2;
    self->size = n;
    self->base.refcnt = 0;
    self->base.type = V_LIST;
    while (++i < n)
    {
        self->members[i] = va_arg(data, t_obj *);
    }
    return self;
}

t_list *lst(t_arena *arena, int n, ...)
{
    va_list lst;
    va_start(lst, n);
    return list_new(n, arena, lst);
}

void    realloc_list(t_list *self, t_arena *arena)
{
    if (self->cap == 0)
        self->cap = 1;
    self->cap <<= 1;
    self = get_memory(sizeof(t_list) + self->cap * sizeof(t_obj *), arena);
}

void    append(t_list *self, t_obj *data, t_arena *arena)
{
    int i;

    i = 0;
    if (!self)
        return (display_error("self not found", &i, 10));
    if (self->cap < self->size + 1)
        realloc_list(self, arena);
    self->members[self->size] = data;

    self->size += 1;
}

t_obj *pop(t_list *self, int index)
{
    t_obj *res;

    if (index < 0)
        index = (int)self->size + index;
    if (index >= (int)self->size || self->size == 0 || index < 0)
        return (display_error("Out_of_Range index: ", &index, 10), NULL);
    res = self->members[index];
    memmove(
    &self->members[index],
    &self->members[index + 1],
    (self->size - 1 - index) * sizeof(t_obj));
    self->size--;
    return res;
}

void print_list(t_list *self)
{
    size_t  i;

    i = 0;
    write(1, "[", 1);
    while (i < self->size)
    {
        print_obj(self->members[i++]);
        write(1, ", ", 2 * (self->size > i));
    }
    write(1, "]", 1);
}

int handle_error(t_list *self, int start, int end)
{
    if (start < 0 || start >= (int)self->size)
    {
        return (display_error(
            "OutOfRangeError, given start index: ", &start, 10), 1);
    }
    if (end < -1 || end > (int)self->size)
        return (display_error(
    "OutOfRangeError, given end index: ", &end, 10), 1);
    return 0;
}

static int apply_step(int *start, int step)
{
    *start += step;
    return (*start - step);
}

t_list *slice(t_list *self, int *range, t_arena *arena)
{
    t_list  *list;
    int upper;
    int lower;
    int start;
    int end;
    int step;

    start = range[0];
    end = range[1];
    step = range[2];
    upper = self->size -1;
    lower = 0;
    if (start < 0)
        start = self->size + start;
    if (end < 0)
        end = self->size + end;
    if (start > end && end >= lower)
        lower = end + 1 - range[3];
    else if (start < end && end <= upper)
        upper = end - 1 + range[3];
    handle_error(self, start, end);
    list = lst(arena, 0);
    while (start >= lower && start <= upper)
        append(list, (t_obj *)self->members[apply_step(&start, step)], arena);
    return (list);
}

// int main(void)
// {
//     t_arena	*arena;

// 	arena = new_arena();
//     print_list(lst(
//         arena, 5, 
//         str_new("azur", arena), str_new("python", arena),
//         int_new(2147483647, arena), tup(arena, 2, int_new(255, arena),
//         int_new(65535, arena)),
//         lst(arena, 2, int_new(42, arena), int_new(32, arena))
//     ));
//     // dump_arena(arena->block);
//     free_all(arena);
// }