/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:26:19 by apercebo          #+#    #+#             */
/*   Updated: 2022/03/21 14:05:34 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int			nbr;
	long int	result;

	nbr = 0;
	result = 0;
	while (str[nbr] >= 48 && str[nbr] <= 57)
	{
		result = result * 10 + (str[nbr] - 48);
		nbr++;
	}
	return (result);
}

void	ft_sendtoserver(char *binary, pid_t serverpid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(100);
		if (binary[i] == '0')
			kill(serverpid, SIGUSR1);
		else if (binary[i] == '1')
			kill(serverpid, SIGUSR2);
		i++;
	}
}

void	ft_convertobinary(int c, pid_t serverpid)
{
	char	binary[9];
	int		nbr;
	int		i;
	int		val;

	i = 0;
	nbr = 128;
	val = c;
	binary[8] = '\0';
	while (i < 8)
	{
		if (val / nbr >= 1)
		{
			binary[i] = '1';
			val -= nbr;
		}
		else
			binary[i] = '0';
		i++;
		nbr /= 2;
	}
	ft_sendtoserver(binary, serverpid);
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	int		i;

	i = 0;
	if (argc != 3)
		return (0);
	serverpid = ft_atoi(argv[1]);
	while (argv[2][i])
	{
		ft_convertobinary(argv[2][i], serverpid);
		i++;
	}
	ft_convertobinary(argv[2][i], serverpid);
	return (0);
}
