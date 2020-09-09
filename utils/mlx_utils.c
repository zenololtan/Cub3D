/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 16:27:12 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/09 13:37:30 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"

int				close_window(t_data *data)
{
	if (data->mlx && data->img[0].img)
		mlx_destroy_image(data->mlx, data->img[0].img);
	if (data->mlx && data->img[1].img)
		mlx_destroy_image(data->mlx, data->img[1].img);
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->free)
		free_struct(data);
	exit(0);
}

void			errors(char *str, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->free = 0;
	close_window(data);
}

void			ft_mlx_pixel_put(t_mlx_img *img,
				int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}

int				get_color(t_color color)
{
	return ((int)color.r << 16 | (int)color.b << 8 | (int)color.g);
}

unsigned int	fog_color(double distance, unsigned int color)
{
	t_uncolor	pack;
	double		multi;

	multi = (10 / distance) / 3;
	if (multi > 1.0)
		multi = 1.0;
	if (multi < 0.35)
		multi = 0.35;
	pack.argb.r = (color & 0xFF0000) >> 16;
	pack.argb.r *= multi;
	pack.argb.g = (color & 0xFF00) >> 8;
	pack.argb.g *= multi;
	pack.argb.b = color & 0xFF;
	pack.argb.b *= multi;
	return (pack.color & 0x00FFFFFF);
}
