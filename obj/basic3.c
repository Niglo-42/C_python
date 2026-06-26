#include "dict/dict.h"

static t_dict  *base_dict(t_arena *arena, char *base)
{
    t_dict  *dict;
    size_t  i;
	char	*s;

    i = 0;
    dict = new_dict(NULL, strlen(base), arena);
    while (base[i])
	{
		s = get_memory(2, arena);
		ft_memcpy(s, &base[i], 1);
		s[1] = 0;
		set(dict, new_entry(s, int_new(i, arena), arena));
		i++;
	}
    return (dict);
}

static char	*get_char_s(char *s, t_arena *arena)
{
	char	*c;

	c = get_memory(2, arena);
	ft_memcpy(c, s, 1);
	c[1] = 0;
	return (c);
}

int	ft_atoi_base(int *flag, char *s, char *base, t_arena *arena)
{
	size_t	i;
	int		sign;
	t_dict	*dict;
    size_t  base_len;
	int		res;

    base_len = strlen(base);
	if (base_len < 2 || base_len > 60)
		return (*flag = 1, 1);
    dict = base_dict(arena, base);
	i = 0;
	res = 0;
	sign = 1;
	while(s[i] && (s[i] == 32 || (s[i] >= 8 && s[i] <= 13)))
		i++;
	while(s[i] && (s[i] == '+' || s[i] == '-'))
		if (s[i++] == '-')
			sign = -1;
	while (s[i])
	{
		if (get(dict, get_char_s(&s[i], arena)))
			res = res * base_len + ((t_int *)get(dict, get_char_s(&s[i], arena))->value)->val;
		else
			break;
		i++;
	}
	return (res * sign);
}

int	*ft_atoi(int *res, char *s)
{
	size_t	i;
	int		sign;

	i = 0;
	*res = 0;
	sign = 0;
	while(s[i] && s[i] >= 8 && s[i] <= 13)
		i++;
	while(s[i] && (s[i] == '+' || s[i] == '-'))
		if (s[i++] == '-')
			sign = 1;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (NULL);
		*res = *res * 10 + (s[i] - 48);
		i++;
	}
	return (res);
}
