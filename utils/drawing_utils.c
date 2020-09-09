/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 18:23:26 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/08 14:14:38 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include <math.h>

void	calc_tex(t_data *data, t_raycaster *ray, int index)
{
	if (ray->side == 0)
		data->wall[index].wallx =
			data->pos.y + ray->perpwalldist * ray->raydir.y;
	else
		data->wall[index].wallx =
			data->pos.x + ray->perpwalldist * ray->raydir.x;
	data->wall[index].wallx -= floor(data->wall[index].wallx);
	data->wall[index].tex.x =
		data->wall[index].wallx * data->wall[index].texwidth;
	if (ray->side == 0 && ray->raydir.x > 0)
		data->wall[index].tex.x =
			data->wall[index].texwidth - data->wall[index].tex.x - 1;
	if (ray->side == 1 && ray->raydir.y < 0)
		data->wall[index].tex.x =
			data->wall[index].texwidth - data->wall[index].tex.x - 1;
	data->wall[index].step =
		1.0 * data->wall[index].texheight / ray->lineheight;
	data->wall[index].texpos = (ray->drawstart - data->height / 2 +
		ray->lineheight / 2) * data->wall[index].step;
}

void	draw_tex(t_data *data, t_raycaster *ray, int index)
{
	int	pixel;
	int y;
	int x;

	calc_tex(data, ray, index);
	x = ray->x;
	y = ray->drawstart;
	while (y <= ray->drawend)
	{
		data->wall[index].tex.y =
		(int)data->wall[index].texpos & (data->wall[index].texwidth - 1);
		data->wall[index].texpos += data->wall[index].step;
		pixel = ((data->wall[index].tex.y * data->wall[index].img.line_length) +
		data->wall[index].tex.x * (data->wall[index].img.bits_per_pixel >> 3));
		data->wall[index].color =
		*(unsigned int *)(data->wall[index].img.addr + pixel);
		if (ray->side == 1)
			data->wall[index].color = (data->wall[index].color >> 1) & 8355711;
		data->wall[index].color =
			fog_color(ray->perpwalldist, data->wall[index].color);
		ft_mlx_pixel_put(&data->img[data->frame],
			x, y, data->wall[index].color);
		y++;
	}
}

void	draw_floor_ceiling(t_data *data, t_raycaster *ray)
{
	int	y;
	int horizon;

	y = 0;
	horizon = data->height >> 1;
	while (y < horizon)
	{
		if (y < ray->drawstart)
			ft_mlx_pixel_put(&data->img[data->frame],
			ray->x, y, data->fc[1].value);
		y++;
	}
	while (y < data->height)
	{
		if (y > ray->drawend)
			ft_mlx_pixel_put(&data->img[data->frame],
			ray->x, y, data->fc[0].value);
		y++;
	}
}
