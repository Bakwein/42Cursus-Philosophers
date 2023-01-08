/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:09:50 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:55:00 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	philo_sleep(t_philo *philo, t_param input_param);
void	philo_eat(t_philo *philo, t_param input_param);

void	first_move(t_philo *philo, t_param input_param)
{
	if (philo->id == 0 || philo->id % 2 == 0)
	{
		philo_print(philo, "is thinking");
		usleep(input_param.time_to_eat * 500);
	}
}

int	start_philo(int id, t_data *all_data)
{
	pthread_t	monitor_thread;
	t_philo		*philo;

	philo = init_philo_struct(id, all_data);
	if (!philo)
		return (0);
	if (pthread_create(&monitor_thread, 0, monitor_hunger, philo) != 0)
		return (0);
	pthread_detach(monitor_thread);
	first_move(philo, all_data->input_param);
	while (1)
	{
		philo_eat(philo, all_data->input_param);
		philo_sleep(philo, all_data->input_param);
		philo_print(philo, "is thinking");
	}
}
