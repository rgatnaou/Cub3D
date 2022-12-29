/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/29 14:39:57 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse(ac, av);
	if (!data)
		return (0);
	draw(data);
	return (0);
}
