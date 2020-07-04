/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffloris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:07:26 by ffloris           #+#    #+#             */
/*   Updated: 2018/04/30 14:14:05 by ffloris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_sorted(int *a, int a_size)
{
	int	i;

	i = 0;
	while (i < a_size - 1)
	{
		if (a[i] > a[i + 1])
			return (0);
		i++;
	}
	return (1);
}