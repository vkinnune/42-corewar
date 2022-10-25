/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:39:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/10 20:31:48 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_float(char *base_num, char *decimals, int prec)
{
	ft_putstr(base_num);
	if (prec)
	{
		write(1, ".", 1);
		ft_putstr(decimals);
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

int	ft_putfloat(long double lift, int prec)
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
	print_float(base_num, decimals, prec);
	return (retrn_type);
}
