/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 16:37:39 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/09 13:54:57 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"

void	free_arrays(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_struct(t_data *data)
{
	int index;

	index = 0;
	if (data->zbuffer)
		free(data->zbuffer);
	if (data->map_str)
		free(data->map_str);
	if (data->map)
		free_arrays(data->map);
	while (index <= data->i)
	{
		if (data->sprite[data->i].path)
			free(data->sprite[data->i].path);
		if (data->wall[index].path && index <= 3)
			free(data->wall[index].path);
		index++;
	}
	if (data->spriteindex)
		free(data->spriteindex);
}

void	reset_data(t_data *data)
{
	int index;

	index = 0;
	ft_bzero(data, sizeof(t_data));
	while (index <= 7)
	{
		if (index <= 1)
		{
			ft_bzero(&data->fc[index], sizeof(t_color));
			ft_bzero(&data->img[index], sizeof(t_mlx_img));
		}
		if (index <= 3)
			ft_bzero(&data->wall[index], sizeof(t_tex));
		ft_bzero(&data->sprite[index], sizeof(t_sprite));
		index++;
	}
	ft_bzero(&data->input, sizeof(t_input));
	data->spawn.x = 0;
	data->spawn.y = 0;
	data->move_speed = 0.05;
	data->bmp = 0;
	data->free = 1;
	data->multiple_sprites = 0;
}
