/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:08:59 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/22 13:14:19 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// int	get_int_length(int n)
// {
// 	int		length;
// 	bool	is_negative;

// 	length = 0;
// 	is_negative = n < 0;
// 	if (n == 0)
// 		return (1);
// 	if (is_negative)
// 		n = -n;
// 	while (n > 0)
// 	{
// 		n /= 10;
// 		length++;
// 	}
// 	if (is_negative)
// 		return (length + 1);
// 	else
// 		return (length);
// }

// char	*ft_strcpy(char *dest, const char *src)
// {
// 	char	*original_dest;
// 	int		i;

// 	original_dest = dest;
// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src [i];
// 		i++;
// 	}
// 	original_dest[i] = '\0';
// 	return (original_dest);
// }

// char	*handle_int_min(void)
// {
// 	char	*min_str;

// 	min_str = (char *)malloc(12 * sizeof(char));
// 	if (min_str == NULL)
// 		return (NULL);
// 	ft_strcpy(min_str, "-2147483648");
// 	return (min_str);
// }

// void	convert_number_to_string(int n, char *str, int length, bool is_negative)
// {
// 	int	index;

// 	index = length - 1;
// 	if (n == 0)
// 		str[index] = '0';
// 	else
// 	{
// 		while (n > 0)
// 		{
// 			str[index--] = '0' + (n % 10);
// 			n /= 10;
// 		}
// 	}
// 	if (is_negative)
// 		str[0] = '-';
// 	str[length] = '\0';
// }

// char	*ft_itoa(int n)
// {
// 	int		length;
// 	bool	is_negative;
// 	char	*str;

// 	length = get_int_length(n);
// 	is_negative = n < 0;
// 	if (n == INT_MIN)
// 		return (handle_int_min());
// 	str = (char *)malloc((length + 1) * sizeof(char));
// 	if (str == NULL)
// 		return (NULL);
// 	if (is_negative)
// 	{
// 		str[0] = '-';
// 		n = -n;
// 	}
// 	convert_number_to_string(n, str, length, is_negative);
// 	return (str);
// }

int	get_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*nb;
	int		len;

	len = get_len(n);
	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	n = n * sign;
	nb = (char *)malloc((len + 1) * sizeof(char));
	if (!nb)
		return (NULL);
	nb[len--] = '\0';
	while (len >= 0)
	{
		nb[len--] = '0' + (n % 10);
		n = n / 10;
	}
	if (sign == -1)
		nb[0] = '-';
	return (nb);
}