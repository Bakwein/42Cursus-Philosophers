/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:09:18 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:54:28 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	start_processes(t_data *all_data)
{
	int	i;

	i = 0;
	while (i < all_data->input_param.count)
	{
		all_data->philo_pids[i] = fork();
		if(all_data->philo_pids[i] == -1) //?
		{
			error("Error: failed use fork function");
		}
		if (all_data->philo_pids[i] == 0)
		{
			if (!start_philo(i, all_data))
				error("Error : failed start philo\n");
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		*all_data;
	pthread_t	thread_limit_monitor;

	if (argc != 5 && argc != 6)
		return (error("Error : Invalid input\n"));
	all_data = init_all_data(argc, argv);
	if (!all_data)
		return (error("Error : Failed init all_data\n"));
	if (all_data->input_param.philo_must_eat != -1)
	{
		if (pthread_create(&thread_limit_monitor, 0, monitor_limit, all_data))
			return (0);
		pthread_detach(thread_limit_monitor);
	}
	start_processes(all_data);
	waitpid(-1, NULL, 0);
	ft_kill(all_data);
	destroy_semaphores(all_data);
	exit(0);
}
