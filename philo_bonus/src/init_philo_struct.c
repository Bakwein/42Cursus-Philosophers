/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:09:12 by stunca            #+#    #+#             */
/*   Updated: 2022/12/14 02:09:12 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_philo	*init_philo_struct(int id, t_data *all_data)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->start_time = all_data->start_time;
	philo->last_eat = all_data->start_time;
	philo->time_to_die = all_data->input_param.time_to_die;
	philo->time_eat = 0;
	philo->sem_forks = all_data->sem_forks;
	philo->sem_philo_must_eat = all_data->sem_philo_must_eat;
	philo->sem_print = all_data->sem_print;
	philo->name_sem_eat_update = all_data->child_sem_name[id];
	sem_unlink(philo->name_sem_eat_update);
	philo->sem_eat_update = sem_open(philo->name_sem_eat_update,
			O_CREAT | O_EXCL, 0666, 1);
	if (philo->sem_eat_update == SEM_FAILED)
		return (NULL);
	return (philo);
}
