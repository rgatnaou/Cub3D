/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 09:32:29 by rgatnaou         ###   ########.fr       */
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
