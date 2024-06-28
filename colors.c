/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:50 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/15 13:54:37 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_setcolor(const char *color_code)
{
	printf("%s", color_code);
}

void	ft_resetcolor(void)
{
	printf("\033[0m");
}
