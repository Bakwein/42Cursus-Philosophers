/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:09:01 by stunca            #+#    #+#             */
/*   Updated: 2022/12/16 14:32:25 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_general_semaphores(t_data *all_data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_philo_must_eat");
	all_data->sem_forks = sem_open("/philo_forks",
			O_CREAT | O_EXCL, 0644, all_data->input_param.count);
	if (all_data->input_param.philo_must_eat != -1)
		all_data->sem_philo_must_eat = sem_open("/philo_philo_must_eat",
				O_CREAT | O_EXCL, 666, 0);
	else
		all_data->sem_philo_must_eat = NULL;
	all_data->sem_print = sem_open("/philo_print",
			O_CREAT | O_EXCL, 666, 1);
	if (all_data->sem_forks == SEM_FAILED || all_data->sem_print == SEM_FAILED
		|| all_data->sem_philo_must_eat == SEM_FAILED)
		return (0);
	return (1);
}

int	init_child_sem_name(t_data *all_data)
{
	char	**names;
	char	*str_tmp;
	int		id;
	int		num_philo;

	num_philo = all_data->input_param.count;
	names = (char **) malloc(sizeof(char *) * num_philo);
	if (!names)
		return (0);
	id = 0;
	while (id < num_philo)
	{
		str_tmp = ft_itoa(id + 1);
		names[id] = ft_strjoin("/sem_eat_update_", str_tmp);
		free(str_tmp);
		id++;
	}
	all_data->child_sem_name = names;
	return (1);
}

t_data	*init_all_data(int argc, char **argv)
{
	t_data	*all_data;

	all_data = (t_data *) malloc(sizeof(t_data));
	if (!all_data)
		return (NULL);
	all_data->input_param = init_input(argc, argv);
	if (!all_data->input_param.count)
		return (NULL);
	all_data->philo_pids = (pid_t *) malloc(sizeof(pid_t)
			* all_data->input_param.count);
	if (!all_data->philo_pids)
		return (NULL);
	all_data->start_time = get_time();
	if (!init_general_semaphores(all_data))
		return (NULL);
	if (!init_child_sem_name(all_data))
		return (NULL);
	return (all_data);
}
