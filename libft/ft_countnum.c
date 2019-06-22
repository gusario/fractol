/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:24:22 by srobert-          #+#    #+#             */
/*   Updated: 2018/12/10 20:25:35 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countnum(int n)
{
	int i;

	if (n == 0)
		return (1);
	if (n >= 0)
		i = 0;
	else
		i = 1;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}