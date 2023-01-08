/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:07:29 by stunca            #+#    #+#             */
/*   Updated: 2022/12/16 01:03:31 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_data *all_data, int id, char *msg)
{
	pthread_mutex_lock(&all_data->print_fork);
	printf("%lu %d %s\n", get_time() - all_data->start_time, id + 1, msg);
	pthread_mutex_unlock(&all_data->print_fork);
}

int	is_some_dead(t_philo *philo)
{
	t_data	*all_data;
	int		ret;

	all_data = philo->all_data;
	ret = 0;
	pthread_mutex_lock(&all_data->dead_man_check);
	if (all_data->dead_man)
		ret = 1;
	pthread_mutex_unlock(&all_data->dead_man_check);
	return (ret);
}

int	take_fork(t_philo *philo, t_data *all_data)
{
	pthread_mutex_lock(philo->r_fork);
	if (is_some_dead(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	philo_print(all_data, philo->id, "has taken a fork");
	if (all_data->input_param.count == 1)
	{
		while (get_time() < philo->last_eat
			+ all_data->input_param.time_to_die + 1)
			usleep(330);
		return (0);
	}
	pthread_mutex_lock(philo->l_fork);
	if (is_some_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	philo_print(all_data, philo->id, "has taken a fork");
	return (1);
}

void	philo_eat(t_philo *philo, t_data *all_data)
{
	if (!take_fork(philo, all_data))
		return ;
	pthread_mutex_lock(philo->check_hunger);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->check_hunger);
	if (is_some_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	philo_print(all_data, philo->id, "is eating");
	philo->time_eat++;
	while (get_time() < philo->last_eat + all_data->input_param.time_to_eat)
		usleep(330);
	if (!is_some_dead(philo)
		&& philo->time_eat == all_data->input_param.philo_must_eat)
	{
		pthread_mutex_lock(&all_data->dead_man_check);
		all_data->must_eat_counter += 1;
		pthread_mutex_unlock(&all_data->dead_man_check);
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo, t_data *all_data)
{
	unsigned long	start_sleep;

	start_sleep = get_time();
	if (is_some_dead(philo))
		return ;
	philo_print(all_data, philo->id, "is sleeping");
	while (get_time() < start_sleep + all_data->input_param.time_to_sleep)
		usleep(330);
}
