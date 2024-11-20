/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:19:42 by tsukuru           #+#    #+#             */
/*   Updated: 2024/08/21 18:59:58 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ptr_digits(unsigned long long n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}

static void	put_ptr(unsigned long long adr)
{
	static char	digits[] = "0123456789abcdef";

	if (adr >= 16)
		put_ptr(adr / 16);
	write(1, &digits[adr % 16], 1);
}

int	prt_ptr(void *adr)
{
	write(1, "0x", 2);
	put_ptr((unsigned long long)adr);
	return (ptr_digits((unsigned long long)adr) + 2);
}
