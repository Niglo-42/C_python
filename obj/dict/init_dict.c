#include "dict.h"

t_abcd __init__vars(void)
{
    return (t_abcd)
    {
        .a = 0x67452301,
        .b = 0xefcdab89,
        .c = 0x98badcfe,
        .d = 0x10325476
    };
}

t_dict  *new_dict(t_dict *src, size_t len, t_arena *arena)
{
    t_dict *self;

    self = (t_dict *)get_memory(sizeof(t_dict) + len * sizeof(t_entry *), arena);
    self->base.refcnt = 0;
    self->base.type = V_DICT;
    if (src ==  NULL)
        self->size = 0;
    else
    {
        self->size = src->size;
        self->base.type = src->base.type;
        memcpy(self->tab_entry, src->tab_entry, len * sizeof(t_entry *));
    }
    self->cap = len;
    self->vars = __init__vars();
    return (self);
}

t_entry *new_entry(const char *key, t_obj *val, t_arena *arena)
{
    t_entry *new;
    
    new = (t_entry *)get_memory(sizeof(t_entry), arena);
    new->base.type = V_ENTRY;
    new->key = key;
    new->state = 1;
    new->value = val;
    return (new);
}