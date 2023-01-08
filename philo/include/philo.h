/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:06:04 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:56:53 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_param
{
	int				count;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				philo_must_eat;
}	t_param;

typedef struct s_philo
{
	int				id;
	int				state;
	int				time_eat;
	unsigned long	last_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*check_hunger;
	void			*all_data;
}	t_philo;

typedef struct s_data
{
	pthread_t		*pthread_list;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks_list;
	pthread_mutex_t	*chats_list;
	pthread_mutex_t	*dead_checker;
	t_philo			*philo_list;
	t_param			input_param;
	pthread_mutex_t	print_fork;
	pthread_mutex_t	dead_man_check;
	unsigned long	start_time;
	int				dead_man;
	int				must_eat_counter;
}	t_data;

t_param			init_input(int argc, char **argv);
int				init_all_data(t_data *all_data);
void			*monitor(void	*param);
int				start_philo(t_data	*all_data);
unsigned long	get_time(void);
void			philo_print(t_data *all_data, int id, char *msg);
int				error(char *str);
void			destroy_mutexes(t_data *all_data);
int				join_philo_thread(t_data *all_data);
void			free_all_data(t_data **all_data);

#endif //PHILO_H
