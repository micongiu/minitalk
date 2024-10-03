#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

static void	sig_handler(int signal, siginfo_t *talk, void *context)
{
	static int	bits;
	static int	pid;
	static char	c;

	(void)context;
	if (!pid)
		pid = talk->si_pid;
	if (signal == SIGUSR1)
		c = (c << 1) | 1;
	else if (signal == SIGUSR2)
		c <<= 1;
	if (++bits == 8)
	{
		bits = 0;
		ft_putchar_fd(c, 1);
		c = '\0';
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
	}
}

int	main(void)
{
	struct sigaction	talk;

	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	talk.sa_flags = SA_RESTART | SA_SIGINFO;
	talk.sa_sigaction = &sig_handler;
	if (sigaction(SIGUSR1, &talk, NULL) == -1)
		ft_putstr_fd("Problem with the change of SINGUSR1\n", 1);
	if (sigaction(SIGUSR2, &talk, NULL) == -1)
		ft_putstr_fd("Problem with the change of SINGUSR2\n", 1);
	while (1)
		pause();
	return (1);
}
