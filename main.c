/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zeno <zeno@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 14:33:15 by zeno          #+#    #+#                 */
/*   Updated: 2020/09/09 13:33:16 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_mac/mlx.h"
#include "includes/cub3d.h"
#include <stdlib.h>

int		update(t_data *data)
{
	detect_movement(data);
	return (0);
}

void	events(t_data *data)
{
	mlx_hook(data->mlx_win, CLOSE, 1L << 17, &close_window, data);
	mlx_hook(data->mlx_win, KEYPRESS, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, KEYRELEASE, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx, &update, data);
	mlx_loop(data->mlx);
}

void	create_frames(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->img[i].img = mlx_new_image(data->mlx,
		data->width, data->height);
		if (!data->img[i].img)
			errors("Failed to create a new image", data);
		data->img[i].addr = mlx_get_data_addr(data->img[i].img,
		&data->img[i].bits_per_pixel, &data->img[i].line_length,
		&data->img[i].endian);
		i++;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		errors("Failed to link a window", data);
	if (!data->bmp)
	{
		data->mlx_win = mlx_new_window(data->mlx, data->width,
		data->height, "Hello world!");
		if (!data->mlx_win)
			errors("Failed to create a window", data);
	}
	create_frames(data);
	convert_tex(data);
	parse_sprite(data);
	data->zbuffer = (double*)malloc(sizeof(double) * data->width);
	if (!data->zbuffer)
		errors("Failed to allocate memory for the zbuffer", data);
	init_raycaster(data);
}

int		main(int argv, char **argc)
{
	t_data	data;

	file_check(argv, argc, &data);
	init_mlx(&data);
	events(&data);
	return (0);
}
