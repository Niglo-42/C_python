#ifndef DICT_H
# define DICT_H

#include "../obj.h"
#include "../../runtime/arena.h"
#include "../list/list.h"
#include "../tuple/tuple.h"

typedef struct s_abcd
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
} t_abcd;

# define EMPTY 1
# define FILLED 2
# define DELETED 4

typedef struct s_entry
{
    t_obj       base;
    const char  *key;
    t_obj       *value;
    uint8_t     state;
} t_entry;

typedef struct s_dict
{
    t_obj   base;
    size_t  cap;
    t_abcd  vars;
    size_t  size;
    t_entry *tab_entry[];
} t_dict;


t_dict  *new_dict(t_dict *src, size_t len, t_arena *arena);
t_entry *get(t_dict *self, const char *key);
void	set(t_dict *self, t_arena *arena, t_entry *entry);
void    print_dict(t_dict *self);

///// hash functions
uint32_t    rol(uint32_t x, uint32_t s);
uint32_t    F(t_abcd var, uint32_t *key, int i);
size_t      hash(t_dict *self, const char *s);
size_t      hash2(t_dict *self, uint32_t *key, uint32_t *hacher);

//////////dict

t_dict  *copy_dict(t_dict *self, t_arena *arena);
t_dict  *new_dict(t_dict *src, size_t len, t_arena *arena);
t_abcd  __init__vars(void);
t_entry *new_entry(const char *key, t_obj *val, t_arena *arena);
void	print_entry(t_entry *self);
#endif
