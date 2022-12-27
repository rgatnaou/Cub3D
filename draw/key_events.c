/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:02:03 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/27 15:42:20 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->move.ws_move = 0;
	else if (keycode == KEY_S)
		data->move.ws_move = 0;
	else if (keycode == KEY_D)
		data->move.ad_move = 0;
	else if (keycode == KEY_A)
		data->move.ad_move = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		data->move.rotation = 0;
	else if (keycode == KEY_ARROW_LEFT)
		data->move.rotation = 0;
	return (0);
}

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_D)
		data->move.ad_move = 1;
	else if (keycode == KEY_A)
		data->move.ad_move = -1;
	else if (keycode == KEY_S)
		data->move.ws_move = -1;
	else if (keycode == KEY_W)
		data->move.ws_move = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		data->move.rotation = 1;
	else if (keycode == KEY_ARROW_LEFT)
		data->move.rotation = -1;
	else if (keycode == KEY_ESC)
		destroy_win(data);
	return (0);
}
