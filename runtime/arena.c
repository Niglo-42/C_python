#include "arena.h"

static size_t   aligned__alloc(size_t x)
{
    return ((x + sizeof(void *) - 1) & ~(sizeof(void *) - 1));
}

t_block *new_block(size_t size, t_block *parent)
{
    t_block *new;

    new = malloc(sizeof(t_block) + size);
    memset(new, 0, size + sizeof(t_block));
    if (!new)
        return NULL;

    new->next = parent;
    new->rsp = 0;
    new->cap = size;
    return (new);
}

t_arena *new_arena(void)
{
    t_arena *new;

    new = malloc(sizeof(t_arena));
    if (!new)
        return (NULL);
    new->base.refcnt = 0;
    new->base.type = V_ARENA;
    new->block = new_block(0x1000, NULL);
    return (new);
}

void *get_memory(size_t size, t_arena *arena)
{
    t_block *b;
    void    *ptr;

    b = arena->block;
    size = aligned__alloc(size);
    if (b->rsp + size >= b->cap)
    {
        if (size > 0x1000)
            arena->block = new_block(size, arena->block);
        else
            arena->block = new_block(0x1000, arena->block);
    }
    ptr = arena->block->data + arena->block->rsp;
    arena->block->rsp += size;
    return (ptr);
}

void    free_all(t_arena *arena)
{
    t_block *b;
    while (arena->block)
    {
        b = arena->block;
        arena->block = arena->block->next;
        free(b);
    }
    free(arena);
}

void dump_arena(t_block *block)
{
    uint8_t *ptr = block->data;

    for (size_t i = 0; i < block->rsp; i++)
    {
        if (i % 8 == 0)
            printf("\n%04zx ", i);
        printf("%02x ", ptr[i]);
    }
    printf("\n");
}