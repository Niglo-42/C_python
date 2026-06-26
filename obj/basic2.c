#include "runtime/arena.h"
#include "list/list.h"

t_obj	*new_null(t_arena *arena)
{
	t_nul	*new;

	new = (t_nul *)get_memory(sizeof(t_nul), arena);
	new->base.refcnt = 0;
	new->base.type = V_NULL;
	return ((t_obj *)new);
}

void	wrap_default(size_t n, t_obj *_val_default, t_list *self)
{
	size_t	i;

	i = 0;
	if (_val_default->type == V_NULL)
		while (i < n)
			self->members[i++] = NULL;
	else
		while (i < n)
			self->members[i++] = _val_default;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	return ((void *)dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*des;
	const unsigned char	*source;

	des = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (des == source || n == 0)
		return (dest);
	if (des < source)
		while (n--)
			*des++ = *source++;
	else
		while (n--)
			des[n] = source[n];
	return (dest);
}


