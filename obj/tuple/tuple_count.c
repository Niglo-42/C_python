#include "tuple.h"

int  count_str(t_tuple *self, t_obj *elem, t_type type)
{
    size_t  i;
    int  c;

    c = 0;
    i = -1;
    while (++i < self->size)
    {
        if (self->members[i]->type == V_TUP)
            c += count((t_tuple *)self->members[i], elem, type);
        if (self->members[i]->type == type)
            if (strcmp(((t_string *)self->members[i])->s, 
            ((t_string *)elem)->s) == 0)
                c++;
    }
    return (c);
}

int  count_int(t_tuple *self, t_obj *elem, t_type type)
{
    size_t  i;
    int  c;

    c = 0;
    i = -1;
    while (++i < self->size)
    {
        if (self->members[i]->type == V_TUP)
            c += count((t_tuple *)self->members[i], elem, type);
        if (self->members[i]->type == type)
            if (((t_int *)self->members[i])->val == ((t_int *)elem)->val)
                c++;
    }
    return (c);
}

int  count_float(t_tuple *self, t_obj *elem, t_type type)
{
    size_t  i;
    int  c;

    c = 0;
    i = -1;
    while (++i < self->size)
    {
        if (self->members[i]->type == V_TUP)
            c += count((t_tuple *)self->members[i], elem, type);
        if (self->members[i]->type == type)
            if (((t_float *)self->members[i])->val == ((t_float *)elem)->val)
                c++;
    }
    return (c);
}