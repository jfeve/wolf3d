/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_countdigits.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:31:52 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2018/12/19 19:16:29 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_countdigits(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	if (n == 0)
		return (1);
	return (i);
}
