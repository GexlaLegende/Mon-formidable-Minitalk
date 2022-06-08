/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:26:34 by apercebo          #+#    #+#             */
/*   Updated: 2022/03/21 17:17:02 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "ft_printf/ft_printf.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strmjoin(char *s1, int c)
{
	char	*str;
	int		i;

	i = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !c)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = (char)c;
	i++;
	str[i] = '\0';
	free(s1);
	return (str);
}

int	atoibase(char *str)
{
	int	nbr;
	int	i;
	int	binary;

	binary = 128;
	i = 0;
	nbr = 0;
	while (i < 8)
	{
		if (str[i] == '1')
			nbr += binary;
		binary /= 2;
		i++;
	}
	return (nbr);
}

void	handler(int sigtype)
{
	static int	x = 0;
	static char	byte[9];
	static char	*str = NULL;
	int			c;

	byte[8] = '\0';
	if (sigtype == SIGUSR1)
		byte[x++] = '0';
	else if (sigtype == SIGUSR2)
		byte[x++] = '1';
	if (x > 7)
	{
		x = 0;
		c = atoibase(byte);
		if (c == 0)
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			return ;
		}
		str = ft_strmjoin(str, (char)c);
	}
}

int	main(void)
{
	pid_t				serverpid;
	struct sigaction	action;

	serverpid = getpid();
	action.sa_handler = handler;
	action.sa_flags = SA_RESTART;
	ft_printf("Server PID : %d\n", serverpid);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		sleep(7);
}
