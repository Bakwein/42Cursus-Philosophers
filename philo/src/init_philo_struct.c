/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:07:02 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:57:25 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_pthread_struct(t_data *all_data)
{
	all_data->pthread_list = (pthread_t *) malloc(sizeof(pthread_t)
			* all_data->input_param.count);
	all_data->forks_list = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* all_data->input_param.count);
	all_data->chats_list = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* all_data->input_param.count);
	all_data->dead_checker = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* all_data->input_param.count);
	all_data->philo_list = (t_philo *) malloc(sizeof(t_philo)
			* all_data->input_param.count);
	if (!all_data->pthread_list || !all_data->forks_list
		|| !all_data->philo_list || !all_data->chats_list
		|| !all_data->dead_checker)
		return (0);
	return (1);
}

int	init_mutexes(t_data *all_data)
{
	int	i;

	i = 0;
	while (i < all_data->input_param.count)
	{
		if (pthread_mutex_init(&all_data->forks_list[i], 0) != 0)
			return (0);
		if (pthread_mutex_init(&all_data->chats_list[i], 0) != 0)
			return (0);
		if (pthread_mutex_init(&all_data->dead_checker[i], 0) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&all_data->print_fork, 0) != 0)
		return (0);
	if (pthread_mutex_init(&all_data->dead_man_check, 0) != 0)
		return (0);
	return (1);
}

t_philo	create_philo_struct(int index, t_data *all_data)
{
	t_philo	philo;

	philo.r_fork = &all_data->forks_list[index];
	if (index != all_data->input_param.count - 1)
		philo.l_fork = &all_data->forks_list[index + 1];
	else
		philo.l_fork = &all_data->forks_list[0];
	philo.check_hunger = &all_data->chats_list[index];
	philo.id = index;
	philo.state = 0;
	philo.time_eat = 0;
	philo.all_data = all_data;
	return (philo);
}

int	init_all_data(t_data *all_data)
{
	int	i;

	if (!init_pthread_struct(all_data))
		return (0);
	if (!init_mutexes(all_data))
		return (0);
	all_data->start_time = get_time();
	all_data->dead_man = 0;
	all_data->must_eat_counter = 0;
	i = 0;
	while (i < all_data->input_param.count)
	{
		all_data->philo_list[i] = create_philo_struct(i, all_data);
		i++;
	}
	return (1);
}
