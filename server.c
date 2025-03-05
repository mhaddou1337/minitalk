/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddou <mhaddou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:55:57 by mhaddou           #+#    #+#             */
/*   Updated: 2025/03/05 21:55:25 by mhaddou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

struct sigaction	g_srv;

void	ft_putnumber(int nb)
{
	if (nb > 9)
	{
		ft_putnumber(nb / 10);
		ft_putnumber(nb % 10);
	}
	else
		write(1, &nb, (nb += 48, 1));
	return ;
}

int	ft_iterative_power(int nb, int power)
{
	int	result;
	int	pr;

	pr = 1;
	result = 1;
	if (power == 0)
	{
		return (1);
	}
	while (pr <= power)
	{
		result = result * nb;
		pr++;
	}
	return (result);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int		i = 7;
	static char		val = 0;
	static __pid_t	pid_clt = -1;

	if (pid_clt != info->si_pid)
		(1) && (val = 0, i = 7, pid_clt = info->si_pid);
	pid_clt = info->si_pid;
	(void)context;
	if (i >= 0)
	{
		if (sig == SIGUSR2)
			val += ft_iterative_power(2, i);
		i--;
	}
	if (i < 0)
	{
		if (val)
			write(1, &val, 1);
		if (!val)
			kill(info->si_pid, SIGUSR2);
		i = 7;
		val = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int	i;

	g_srv.sa_sigaction = sig_handler;
	g_srv.sa_flags = SA_SIGINFO;
	sigemptyset(&g_srv.sa_mask);
	write(1, "SERVER PID : ", 13);
	ft_putnumber(getpid());
	write(1, "\n", 1);
	i = 0;
	while (1)
	{
		sigaction(SIGUSR1, &g_srv, (void *)0);
		sigaction(SIGUSR2, &g_srv, (void *)0);
		pause();
		i++;
	}
	return (0);
}
