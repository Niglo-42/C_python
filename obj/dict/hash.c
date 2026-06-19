/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:51:34 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 11:52:25 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

static t_abcd	__init__vars(void)
{
	t_abcd	new;

	new.a = 0x67452301;
	new.b = 0xefcdab89;
	new.c = 0x98badcfe;
	new.d = 0x10325476;
	return (new);
}

static const uint32_t	*get_k(void)
{
	static const uint32_t	g_k[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf,
		0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
		0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6,
		0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
		0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122,
		0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039,
		0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97,
		0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d,
		0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	return (g_k);
}

static const uint32_t	*get_rot(void)
{
	static const uint32_t	g_rot[64] = {7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	return (g_rot);
}

static size_t	hash2(uint32_t *key, uint32_t *hacher)
{
	int			i;
	uint32_t	tmp;
	t_abcd		var;

	i = -1;
	var = __init__vars();
	while (++i < 64)
	{
		tmp = var.c;
		var.c = var.b;
		var.b += rol(var.a + f(var, key, i) + get_k()[i], get_rot()[i]);
		var.a = var.d;
		var.d = tmp;
	}
	hacher[0] = var.a;
	hacher[1] = var.b;
	return (hacher[2] = var.c, hacher[3] = var.d, hacher[0]);
}

size_t	hash(t_dict *self, const char *s)
{
	int			i;
	int			j;
	uint32_t	hacher[4];
	uint32_t	buf_hash[16];

	i = 0;
	j = 0;
	memset(buf_hash, 0, 16 * sizeof(uint32_t));
	while (j < 14)
	{
		if (s[i])
		{
			j = i >> 2;
			buf_hash[j] |= s[i] << ((i & 0b11) << 3);
			i++;
		}
		else
			buf_hash[++j] = 0;
	}
	buf_hash[14] = 0x80;
	buf_hash[15] = i * 8;
	return (hash2(buf_hash, hacher) % self->cap);
}
