/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 16:04:59 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/07 20:11:00 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include <math.h>

void		draw_sprite_verline(t_data *data, t_spritecaster *sprite)
{
	unsigned int	color;

	sprite->y = sprite->drawstarty;
	while (sprite->y < sprite->drawendy)
	{
		sprite->d = (sprite->y << 8) - (data->height << 7) +
		(sprite->spriteheight << 7);
		sprite->texy = ((sprite->d *
			data->spriteindex[sprite->i].sprite.texheight) /
			sprite->spriteheight) / 256;
		color =
			*(unsigned int*)(data->spriteindex[sprite->i].sprite.img.addr +
			(sprite->texy * data->spriteindex[sprite->i].sprite.img.line_length
			+ sprite->texx *
			(data->spriteindex[sprite->i].sprite.img.bits_per_pixel >> 3)));
		color = fog_color(data->spriteindex[sprite->i].dist, color);
		if (color != 0)
		{
			ft_mlx_pixel_put(&data->img[data->frame], sprite->stripex,
			sprite->y, color);
		}
		sprite->y++;
	}
}

void		draw_sprite(t_data *data, t_spritecaster *sprite)
{
	sprite->stripex = sprite->drawstartx;
	while (sprite->stripex < sprite->drawendx)
	{
		sprite->texx = (int)(((sprite->stripex - ((-sprite->spritewidth >> 1)
			+ sprite->spritescreenx)) << 8) *
			data->spriteindex[sprite->i].sprite.texwidth /
			sprite->spritewidth) >> 8;
		if (sprite->transformy > 0 && sprite->stripex > 0 &&
		sprite->stripex < data->width &&
		sprite->transformy < data->zbuffer[sprite->stripex])
			draw_sprite_verline(data, sprite);
		sprite->stripex++;
	}
}

void		calc_dimensions(t_data *data, t_spritecaster *sprite)
{
	sprite->spriteheight = (int)fabs(data->height / sprite->transformy);
	sprite->drawstarty = (-sprite->spriteheight >> 1) + (data->height >> 1);
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = (sprite->spriteheight >> 1) + (data->height >> 1);
	if (sprite->drawendy >= data->height)
		sprite->drawendy = data->height - 1;
	sprite->spritewidth = (int)fabs(data->height / sprite->transformy);
	sprite->drawstartx = (-sprite->spritewidth >> 1) + sprite->spritescreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = (sprite->spritewidth >> 1) + sprite->spritescreenx;
	if (sprite->drawendx >= data->width)
		sprite->drawendx = data->width - 1;
}

void		calc_sprite(t_data *data, t_spritecaster *sprite)
{
	sprite->spritex = data->spriteindex[sprite->i].pos.x - data->pos.x;
	sprite->spritey = data->spriteindex[sprite->i].pos.y - data->pos.y;
	sprite->invdet = 1.0 / (data->plane.x * data->dir.y -
		data->dir.x * data->plane.y);
	sprite->transformx = sprite->invdet * (data->dir.y *
		sprite->spritex - data->dir.x * sprite->spritey);
	sprite->transformy = sprite->invdet * (-data->plane.y *
		sprite->spritex + data->plane.x * sprite->spritey);
	sprite->spritescreenx = (int)((data->width >> 1) * (1 +
		sprite->transformx / sprite->transformy));
}

void		sprite_cast(t_data *data)
{
	t_spritecaster	sprite;

	sprite.i = data->spritenum - 1;
	insertion_sort(data);
	while (sprite.i >= 0)
	{
		calc_sprite(data, &sprite);
		calc_dimensions(data, &sprite);
		draw_sprite(data, &sprite);
		sprite.i--;
	}
}
