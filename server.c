#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void	sig_handler(void)
{

}

void	control_signal(void)
{
	struct sigaction	talk;

	talk.sa_flags = SA_SIGINFO;
	talk.sa_sigaction = &sig_handler;
	if (sigaction(SIGUSR1, &talk, NULL) == -1)
		ft_putstr_fd("Problem with the change of SINGUSR1\n", 1);
	if (sigaction(SIGUSR2, &talk, NULL) == -1)
		ft_putstr_fd("Problem with the change of SINGUSR2\n", 1);

}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd("\n", 1);
	while (1)
		control_signal();
	return (1);
}