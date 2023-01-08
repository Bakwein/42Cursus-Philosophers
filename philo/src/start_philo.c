/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:07:38 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:58:28 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		is_some_dead(t_philo *philo);
void	philo_eat(t_philo *philo, t_data *all_data);
void	philo_sleep(t_philo *philo, t_data *all_data);

void	philo_think(t_philo *philo, t_data *all_data)
{
	if (is_some_dead(philo))
		return ;
	philo_print(all_data, philo->id, "is thinking");
}

void	first_move(t_data *all_data, t_philo *philo)
{
	if (philo->id == 0 || philo->id % 2 == 0)
	{
		philo_think(philo, all_data);
		usleep(all_data->input_param.time_to_eat * 500);
	}
}

void	*thread_philo(void *param)
{
	t_data	*all_data;
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(philo->check_hunger);
	philo->last_eat = get_time();
	philo->state = 1;
	pthread_mutex_unlock(philo->check_hunger);
	all_data = philo->all_data;
	first_move(all_data, philo);
	while (1)
	{
		philo_eat(philo, all_data);
		if (is_some_dead(philo))
			break ;
		philo_sleep(philo, all_data);
		if (is_some_dead(philo))
			break ;
		philo_think(philo, all_data);
		if (is_some_dead(philo))
			break ;
	}
	return (NULL);
}

int	start_philo(t_data	*all_data)
{
	int	i;

	i = 0;
	while (i < all_data->input_param.count)
	{
		if (pthread_create(&all_data->pthread_list[i], NULL,
				thread_philo, &all_data->philo_list[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
