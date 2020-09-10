/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 14:08:14 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/10 21:33:21 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include <math.h>

void		move_char(t_data *data)
{
	double		horizontal;
	double		vertical;
	t_d_pos		new;
	double		speed;

	horizontal = data->input.horizontal;
	vertical = data->input.vertical;
	speed = data->move_speed;
	if (horizontal != 0 && vertical != 0)
	{
		horizontal *= 0.7;
		vertical *= 0.7;
	}
	new.x = data->pos.x + data->dir.x * (vertical * speed);
	new.y = data->pos.y + data->dir.y * (vertical * speed);
	if (data->map[(int)new.y][(int)data->pos.x] < '1')
		data->pos.y = new.y;
	if (data->map[(int)data->pos.y][(int)new.x] < '1')
		data->pos.x = new.x;
	new.x = data->pos.x + data->plane.x * (horizontal * speed);
	new.y = data->pos.y + data->plane.y * (horizontal * speed);
	if (data->map[(int)new.y][(int)data->pos.x] < '1')
		data->pos.y = new.y;
	if (data->map[(int)data->pos.y][(int)new.x] < '1')
		data->pos.x = new.x;
}

void		turn_char(t_data *data)
{
	double rotspeed;
	double oldirx;
	double oldplanex;

	rotspeed = 0.04 * data->input.turn;
	oldirx = data->dir.x;
	data->dir.x =
	data->dir.x * cos(rotspeed) - data->dir.y * sin(rotspeed);
	data->dir.y =
	oldirx * sin(rotspeed) + data->dir.y * cos(rotspeed);
	oldplanex = data->plane.x;
	data->plane.x =
	data->plane.x * cos(rotspeed) - data->plane.y * sin(rotspeed);
	data->plane.y =
	oldplanex * sin(rotspeed) + data->plane.y * cos(rotspeed);
}

void		detect_movement(t_data *data)
{
	data->input.horizontal = (data->input.left > data->input.right) ? -1 : 1;
	data->input.vertical =
		(data->input.backward > data->input.forward) ? -1 : 1;
	data->input.turn = (data->input.turn_left > data->input.turn) ? -1 : 1;
	if ((data->input.left && data->input.right) ||
	(!data->input.left && !data->input.right))
		data->input.horizontal = 0;
	if ((data->input.forward && data->input.backward) ||
	(!data->input.forward && !data->input.backward))
		data->input.vertical = 0;
	if ((data->input.turn_left && data->input.turn_right) ||
	(!data->input.turn_left && !data->input.turn_right))
		data->input.turn = 0;
	if (data->input.horizontal || data->input.vertical)
		move_char(data);
	if (data->input.turn)
		turn_char(data);
	if (data->input.horizontal != 0 || data->input.vertical != 0
	|| data->input.turn != 0)
		init_raycaster(data);
}

int			key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->input.forward = 1;
	if (keycode == A)
		data->input.left = 1;
	if (keycode == S)
		data->input.backward = 1;
	if (keycode == D)
		data->input.right = 1;
	if (keycode == LEFT)
		data->input.turn_left = 1;
	if (keycode == RIGHT)
		data->input.turn_right = 1;
	if (keycode == ESC)
		close_window(data);
	return (0);
}

int			key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->input.forward = 0;
	if (keycode == A)
		data->input.left = 0;
	if (keycode == S)
		data->input.backward = 0;
	if (keycode == D)
		data->input.right = 0;
	if (keycode == LEFT)
		data->input.turn_left = 0;
	if (keycode == RIGHT)
		data->input.turn_right = 0;
	return (0);
}
