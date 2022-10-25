/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 01:56:09 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/10 20:26:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_float(char *base_num, char *decimals, int prec, int fd)
{
	ft_putstr_fd(base_num, fd);
	if (prec)
	{
		write(fd, ".", 1);
		ft_putstr_fd(decimals, fd);
	}
}

static int	round_number(int i, char *num)
{
	if (i < 0)
		return (1);
	if (num[i] < '9')
	{
		num[i]++;
		return (0);
	}
	else
	{
		num[i] = '0';
		i--;
		return (round_number(i, num));
	}
}

static int	set_decimal(int prec, long double lift, char *decimals)
{
	int	i;
	int	ret;

	ret = 0;
	if (lift < 0)
		lift *= -1;
	lift = (lift - (long long)lift) * 10;
	if (!prec && !(lift < 5.0))
		return (-(lift == 5.0) | 1);
	i = -1;
	while (++i < prec - 1)
	{
		decimals[i] = (long long)lift + '0';
		lift = (lift - (long long)lift) * 10;
	}
	lift += (lift - (long long)lift > 0.5);
	if (lift >= 10.0)
	{
		lift = 0;
		ret = round_number(i - 1, decimals);
	}
	decimals[i++] = (long long)lift + '0';
	decimals[i] = '\0';
	return (ret);
}
/*
	ret = 0: no rounding
	ret = 1: round up
	ret = -1: banker rounding
 */

/* banker rounding for decimals
replace line 76:
if (lift - (long long)lift >= 0.5 && (long long)lift % 2 == 1) */

static void	get_base_num(long double lift, char base_num[25])
{
	char	*tmp;

	tmp = ft_itoa((long long)lift);
	ft_strcpy(base_num, tmp);
	free(tmp);
}

int	ft_putfloat_fd(long double lift, int prec, int fd)
{
	char	base_num[25];
	char	decimals[25];
	int		base_len;
	int		retrn_type;
	int		rounding_type;

	get_base_num(lift, base_num);
	base_len = ft_strlen(base_num);
	retrn_type = 0;
	rounding_type = set_decimal(prec, lift, decimals);
	if (rounding_type == 1
		|| (rounding_type == -1 && (base_num[base_len - 1] - '0') % 2 == 1))
	{
		retrn_type = round_number(base_len - 1, base_num);
		if (retrn_type)
		{
			base_num[0] = '1';
			base_num[base_len] = '0';
			base_num[base_len + 1] = '\0';
		}
	}
	print_float(base_num, decimals, prec, fd);
	return (retrn_type);
}

/* print float without using string */
/* limited to 18 decimals */

/* static int	number_rounding(int prec, int *i, long long *main_num,
		long double *lift)
{
	int	extra_digit;
	int	rounding;

	extra_digit = -1;
	rounding = 0;
	if (*lift - (long long)*lift >= 0.5)
	{
		(*lift)++;
		rounding = 1;
	}
	*i = ft_diglen((long long)*lift);
	if (*i > prec && rounding)
	{
		(*main_num)++;
		*lift = 0;
		extra_digit = (*main_num) % 10;
	}
	return (!extra_digit);
}

int	ft_putfloat_fd(long double lift, int prec, int fd)
{
	long long	main_num;
	int			i;
	int			extra_rounding_digit;

	main_num = (long long)lift;
	lift -= main_num;
	if (lift < 0)
		lift *= -1;
	lift *= ft_pow(10, prec);
	extra_rounding_digit = number_rounding(prec, &i, &main_num, &lift);
	ft_putnbr_fd(main_num, fd);
	if (prec)
	{
		write(fd, ".", 1);
		while (prec-- > i)
			write(fd, "0", 1);
		if (!lift)
			while (prec-- >= 0)
				write(fd, "0", 1);
		else
			ft_putnbr_fd((long long)lift, fd);
	}
	return (extra_rounding_digit);
} */
