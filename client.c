#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void	send_message(char c, int pid, int bits)
{
	unsigned char c;

	bits = 8;
	while (bits)
	{
		if (c & 0b10000000)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
			c <<= 1;
		bits--;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "Character has been sucessfully receieved!\n", 42);
}

int main (int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	talk;
	int					bits;

	if (argc != 3)
		return (ft_putstr_fd("Use ./client <server pid> message\n", 1), -1);
	if (argv[2] == NULL)
		return (ft_putstr_fd("Invalid message, empty\n", 1), -1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_putstr_fd("Problem with the pid\n", 1), -1);
	bits = 0;
	sigemptyset(&talk.sa_mask);
	talk.sa_flags = SA_SIGINFO;
	talk.sa_handler = sig_handler;
	while (argv[2][i++])
		send_message(argv[2][i], pid, bits);	
}