/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:06:34 by stunca            #+#    #+#             */
/*   Updated: 2022/12/14 02:06:36 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				minus;

	minus = 1;
	num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((((num * 10) + (*str - '0')) < num) && (minus == 1))
			return (-1);
		else if ((((num * 10) + (*str - '0')) < num) && (minus == -1))
			return (0);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return ((int)(num * minus));
}
