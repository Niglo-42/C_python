/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:09:43 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/17 18:00:37 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "list/list.h"
#include "tuple/tuple.h"
#include "dict/dict.h"

// typedef struct s_list t_list;
// typedef struct s_dict t_dict;
// typedef struct s_tuple t_tuple;

// void obj_incref(t_obj *obj)
// {
//     if (obj)
//         obj->refcnt++;
// }

// void	str_destroy(t_string *obj)
// {
// 	free(obj);
// }

// void	int_destroy(t_int *obj)
// {
// 	free(obj);
// }

// void	float_destroy(t_float *obj)
// {
// 	free(obj);
// }

// void	obj_destroy(t_obj *obj)
// {
//     if (obj->type == V_STRING)
//         str_destroy((t_string *)obj);
// 	else if (obj->type == V_INT)
//         int_destroy((t_int *)obj);
// 	else if (obj->type == V_FLOAT)
//         float_destroy((t_float *)obj);
// 	else if (obj->type == V_TUP)
//         tuple_destroy((t_tuple *)obj);
// 	else if (obj->type == V_LIST)
//         destroy_list((t_list *)obj);
// 	else if (obj->type == V_DICT)
//         destroy_dict((t_dict *)obj);
// }

// void	obj_decref(t_obj *obj)
// {
//     if (!obj)
//         return;
//     if (--obj->refcnt <= 0)
//         obj_destroy(obj);
// }

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

 void	display_error(char *s, int *value, size_t base){
	char	nb[13];
	t_error	error;

	memcpy(error.e, s, strlen(s) + 1);
	if (value)
	{
		strcat(error.e, ft_itoa(nb, *(long *)value, base));
		strcat(error.e, "\n");
	}
	write(1, error.e, strlen(error.e));
}

int	minmax(int a, int b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

void	print_obj(t_obj *obj)
{
	char	s[13];

	if (!obj)
		return ;
	memset(s, 0, 13);
	if (obj->type == V_STRING)
		write(1, ((t_string *)obj)->s, ((t_string *)obj)->size);
	else if (obj->type == V_CHR)
		write(1, &((t_chr *)obj)->c, 1);
	else if (obj->type == V_INT)
		ft_itoa(s, ((t_int *)obj)->val, 10);
	else if (obj->type == V_FLOAT)
		ft_itoa(s, ((t_float *)obj)->val, 10);
	else if (obj->type == V_TUP)
		print_tuple((t_tuple *)obj);
	else if (obj->type == V_LIST)
		print_list((t_list *)obj);
	else if (obj->type == V_ENTRY)
		print_entry((t_entry *)obj);
	if (obj->type == V_INT || obj->type == V_FLOAT)
		write(1, s, strlen(s));
}

t_obj	*str_new(char *s, t_arena *arena)
{
	t_string	*new;
	size_t		size;

	size = strlen(s);
	new = (t_string *)get_memory(sizeof(t_string) + size + 1, arena);
	new->base.refcnt = 0;
	new->base.type = V_STRING;
	new->size = size;
	memmove(new->s, s, size + 1);
	return ((t_obj *)new);
}

t_obj	*int_new(int val, t_arena *arena)
{
	t_int	*new;

	new = (t_int *)get_memory(sizeof(t_int), arena);
	new->base.refcnt = 0;
	new->base.type = V_INT;
	new->val = val;
	return ((t_obj *)new);
}

t_obj	*chr_new(char c, t_arena *arena)
{
	t_chr	*new;

	new = (t_chr *)get_memory(sizeof(t_chr), arena);
	new->base.refcnt = 0;
	new->base.type = V_CHR;
	new->c = c;
	return ((t_obj *)new);
}

t_obj	*float_new(float val, t_arena *arena)
{
	t_float	*new;

	new = (t_float *)get_memory(sizeof(t_float), arena);
	new->base.refcnt = 0;
	new->base.type = V_FLOAT;
	new->val = val;
	return ((t_obj *)new);
}