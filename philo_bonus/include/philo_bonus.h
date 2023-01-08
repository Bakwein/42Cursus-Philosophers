/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:08:11 by stunca            #+#    #+#             */
/*   Updated: 2022/12/17 02:53:57 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_param
{
	int				count;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				philo_must_eat;
}	t_param;

typedef struct s_data
{
	t_param			input_param;
	unsigned long	start_time;
	pid_t			*philo_pids;
	sem_t			*sem_forks;
	sem_t			*sem_philo_must_eat;
	sem_t			*sem_print;
	char			**child_sem_name;
}	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	start_time;
	unsigned long	last_eat;
	unsigned long	time_to_die;
	int				time_eat;
	sem_t			*sem_forks;
	sem_t			*sem_philo_must_eat;
	sem_t			*sem_print;
	sem_t			*sem_eat_update;
	char			*name_sem_eat_update;
}	t_philo;

char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				error(char *str);
t_param			init_input(int argc, char **argv);
t_data			*init_all_data(int argc, char **argv);
int				start_philo(int id, t_data *all_data);
unsigned long	get_time(void);
void			philo_print(t_philo *philo, char *msg);
t_philo			*init_philo_struct(int id, t_data *all_data);
void			*monitor_limit(void *data);
void			*monitor_hunger(void *philo_param);
void			ft_kill(t_data *all_data);
void			destroy_semaphores(t_data *all_data);

#endif 
