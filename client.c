/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:42:14 by micongiu          #+#    #+#             */
/*   Updated: 2024/10/05 13:43:14 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int	handle_error(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return (ft_putstr_fd("Use ./client <server pid> message\n", 1), -1);
	if (argv[2] == NULL)
		return (ft_putstr_fd("Invalid message, empty\n", 1), -1);
	i = 0;
	while (argv[1][i])
		if (!ft_isdigit(argv[1][i++]))
			return (ft_putstr_fd("Invalid pid, only number\n", 1), -1);
	return (0);
}

void	send_message(char c, int pid, int bits)
{
	bits = 7;
	while (bits >= 0)
	{
		if (c >> bits & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bits--;
	}
}

void	sig_handler(int signal, siginfo_t *talk, void *context)
{
	(void)signal;
	(void)talk;
	(void)context;
	if (signal == SIGUSR1)
		ft_putstr_fd("The character was received successfully!\n", 1);
	else if (signal == SIGUSR2)
		ft_putstr_fd("ciao\n", 1);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	talk;
	int					bits;

	if (handle_error(argc, argv) == -1)
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_putstr_fd("Problem with the pid\n", 1), -1);
	bits = 0;
	i = 0;
	sigemptyset(&talk.sa_mask);
	talk.sa_flags = SA_RESTART | SA_SIGINFO;
	talk.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &talk, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 1);
	if (sigaction(SIGUSR2, &talk, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 1);
	while (argv[2][i])
		send_message(argv[2][i++], pid, bits);
	send_message('\n', pid, bits);
	return (1);
}
