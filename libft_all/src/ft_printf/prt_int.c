/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:11:53 by tsukuru           #+#    #+#             */
/*   Updated: 2024/11/20 16:21:21 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	int_digits(int n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits += 1;
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}
	return (digits);
}

static void	put_digits(int n)
{
	static char	digits[] = "0123456789";

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		put_digits(n / 10);
	write(1, &digits[n % 10], 1);
}

int	prt_int(int n)
{
	int	len;

	len = int_digits(n);
	if (n == INT_MIN)
		return (write(1, "-2147483648", 11));
	put_digits(n);
	return (len);
}
