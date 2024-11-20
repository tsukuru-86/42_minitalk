/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:14 by tkomai            #+#    #+#             */
/*   Updated: 2024/11/20 14:41:23 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}

// #include<stdio.h>

// int main(void)
// {
// 	const char *a = "ssssddddddddd";
// 	printf("%zu\n", ft_strlen(a));
// }