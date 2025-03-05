/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddou <mhaddou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:55:52 by mhaddou           #+#    #+#             */
/*   Updated: 2024/12/31 20:04:44 by mhaddou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int		g_flag = 0;

ssize_t	mini_atoi(const char *nptr)
{
	ssize_t	index;
	ssize_t	result;

	result = 0;
	index = -1;
	while (nptr[++index])
	{
		if (!(nptr[index] >= '0' && nptr[index] <= '9'))
			return (-1);
		result = result * 10 + (nptr[index] - 48);
	}
	return (result);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
	else if (sig == SIGUSR2)
		write(1, "Your message has been sent successfully\n", 40);
}

int	ft_iterative_power(int nb, int power)
{
	int	result;
	int	pr;

	pr = 0;
	result = 1;
	if (power == 0)
		return (1);
	while (++pr <= power)
		result = result * nb;
	return (result);
}

void	sig_send(char c_of_str, __pid_t pid)
{
	int	pos_bit;
	int	val;

	pos_bit = 7;
	while (pos_bit >= 0)
	{
		val = c_of_str & ft_iterative_power(2, pos_bit);
		if (!val)
		{
			if (-1 == kill(pid, SIGUSR1))
				exit((write(2, "Server not running\n", 19), 1));
		}
		else
		{
			if (-1 == kill(pid, SIGUSR2))
				exit((write(2, "Server not running\n", 19), 1));
		}
		while (!g_flag)
			pause();
		g_flag = 0;
		pos_bit--;
	}
}

int	main(int ac, char **av)
{
	__pid_t	pid;
	size_t	index;

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	if (ac != 3)
		return (write(2, "<PID_SERVER> <STRING_TO_PASS>\n", 30), 1);
	pid = mini_atoi(av[1]);
	if (pid == -1)
		return (write(2, "error with pid ! \n", 18), 1);
	index = 0;
	while (av[2][index])
		sig_send(av[2][index++], pid);
	sig_send('\0', pid);
	return (0);
}
