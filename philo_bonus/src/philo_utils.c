/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:09:45 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:45:00 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	philo_sleep(t_philo *philo, t_param input_param)
{
	unsigned long	start_sleep;

	start_sleep = get_time();
	philo_print(philo, "is sleeping");
	while (get_time() < start_sleep + input_param.time_to_sleep)
		usleep(330);
}

void	philo_eat(t_philo *philo, t_param input_param)
{
	sem_wait(philo->sem_forks);
	philo_print(philo, "has taken a fork");
	sem_wait(philo->sem_forks);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	sem_wait(philo->sem_eat_update);
	philo->last_eat = get_time();
	philo->time_eat++;
	sem_post(philo->sem_eat_update);
	while (get_time() < philo->last_eat + input_param.time_to_eat)
		usleep(330);
	if (philo->time_eat == input_param.philo_must_eat)
		sem_post(philo->sem_philo_must_eat);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
}
