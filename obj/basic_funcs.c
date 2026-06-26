#include "obj.h"
#include "list/list.h"
#include "tuple/tuple.h"
#include "dict/dict.h"

char	*ft_itoa(char *buf, long n, size_t base)
{
	long	nb;
	int		i;
	int		sign;

	i = (n == 0);
	sign = (n < 0);
	nb = n * (n >= 0) + (-n * (n < 0));
	n = nb;
	while (n > 0 && ++i)
		n = n / base;
	buf[i + sign] = 0;
	buf[0] = 0;
	while (i-- > 0)
	{
		buf[i + sign] = "0123456789abcdef"[nb % base];
		nb = nb / base;
	}
	return (buf[0] += '-' * sign, buf);
}

void	display_error(char *s, int *value, size_t base)
{
	char	nb[13];
	t_error	error;

	ft_memcpy(error.e, s, strlen(s) + 1);
	if (value)
	{
		ft_itoa(nb, *(long *)value, base);
		ft_memcpy(((void *)error.e + strlen(s)), nb, strlen(nb) + 1);
		ft_memcpy(((void *)error.e + strlen(error.e)), "\n", 3);
	}
	write(1, error.e, strlen(error.e));
}

int	minmax(int a, int b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

size_t	ft_max(size_t a, size_t b)
{
	if (a < b)
		return (b);
	return (a);
}

t_obj	*new_node(int val, t_arena *arena)
{
	t_node	*new;

	new = (t_node *)get_memory(sizeof(t_node), arena);
	new->integer.base.type = V_NODE;
	new->integer.val = val;
	new->right = NULL;
	new->left = NULL;
	new->red = 0;
	return ((t_obj *)new);
}
