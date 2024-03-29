/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positive_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 23:13:51 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/15 23:20:11 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_is_positive_number(char *c)
{
	if (*c == '+')
		c++;
	while(*c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		c++;
	}
	return(1);
}