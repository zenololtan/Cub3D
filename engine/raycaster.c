/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:20:55 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/02 13:23:27 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include <math.h>

void		calc_draw_len(t_data *data, t_raycaster *ray)
{
	ray->lineheight = (int)(data->height / ray->perpwalldist);
	ray->drawstart = data->height / 2 - ray->lineheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + data->height / 2;
	if (ray->drawend >= data->height)
		ray->drawend = data->height - 1;
	if (ray->side == 1 && ray->raydir.y < 0)
		draw_tex(data, ray, 0);
	if (ray->side == 0 && ray->raydir.x > 0)
		draw_tex(data, ray, 1);
	if (ray->side == 1 && ray->raydir.y > 0)
		draw_tex(data, ray, 2);
	if (ray->side == 0 && ray->raydir.x < 0)
		draw_tex(data, ray, 3);
}

void		ft_dda(t_data *data, t_raycaster *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->map[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->map.x - data->pos.x +
		(1 - ray->step.x) / 2) / ray->raydir.x;
	else
		ray->perpwalldist = (ray->map.y - data->pos.y +
		(1 - ray->step.y) / 2) / ray->raydir.y;
}

void		dda_setup(t_data *data, t_raycaster *ray)
{
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (data->pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x =
		(ray->map.x + 1.0 - data->pos.x) * ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y =
		(data->pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y =
		(ray->map.y + 1.0 - data->pos.y) * ray->deltadist.y;
	}
}

void		calc_ray(t_data *data, t_raycaster *ray)
{
	double camerax;

	camerax = 2 * ray->x / (double)data->width - 1;
	ray->raydir.x = data->dir.x + data->plane.x * camerax;
	ray->raydir.y = data->dir.y + data->plane.y * camerax;
	ray->map.x = (int)data->pos.x;
	ray->map.y = (int)data->pos.y;
	ray->deltadist.x = fabs(1 / ray->raydir.x);
	ray->deltadist.y = fabs(1 / ray->raydir.y);
}

void		init_raycaster(t_data *data)
{
	t_raycaster ray;

	ray.x = 0;
	while (ray.x < data->width)
	{
		calc_ray(data, &ray);
		dda_setup(data, &ray);
		ft_dda(data, &ray);
		calc_draw_len(data, &ray);
		draw_floor_ceiling(data, &ray);
		data->zbuffer[ray.x] = ray.perpwalldist;
		ray.x++;
	}
	if (data->spritenum != 0)
		sprite_cast(data);
	if (data->bmp)
		ft_bmp(data);
	if (data->mlx_win)
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->img[data->frame].img, 0, 0);
	data->frame = (data->frame == 0) ? 1 : 0;
}
