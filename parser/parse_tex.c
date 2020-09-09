/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 19:30:26 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/07 21:55:55 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_mac/mlx.h"
#include "../includes/cub3d.h"
#include "../lft/libft.h"

void	check_type_sprite(t_data *data, char *str, int index)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		++i;
	if (str[i - 1] == 'g' && str[i - 2] == 'n'
		&& str[i - 3] == 'p' && str[i - 4] == '.')
		data->sprite[index].img.img = mlx_png_file_to_image(data->mlx,
			str, &data->sprite[index].texwidth,
			&data->sprite[index].texheight);
	if (str[i - 1] == 'm' && str[i - 2] == 'p'
		&& str[i - 3] == 'x' && str[i - 4] == '.')
		data->sprite[index].img.img = mlx_xpm_file_to_image(data->mlx,
			str, &data->sprite[index].texwidth,
			&data->sprite[index].texheight);
}

void	check_type_wall(t_data *data, char *str, int index)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		++i;
	if (str[i - 1] == 'g' && str[i - 2] == 'n'
		&& str[i - 3] == 'p' && str[i - 4] == '.')
		data->wall[index].img.img = mlx_png_file_to_image(data->mlx,
			str, &data->wall[index].texwidth,
			&data->wall[index].texheight);
	if (str[i - 1] == 'm' && str[i - 2] == 'p'
		&& str[i - 3] == 'x' && str[i - 4] == '.')
		data->wall[index].img.img = mlx_xpm_file_to_image(data->mlx,
			str, &data->wall[index].texwidth,
			&data->wall[index].texheight);
}

void	convert_sprite(t_data *data)
{
	int index;

	index = 0;
	while (index < data->i)
	{
		check_type_sprite(data, data->sprite[index].path, index);
		if (!data->sprite[index].img.img)
			errors("Failed to convert a texture", data);
		data->sprite[index].img.addr =
			mlx_get_data_addr(data->sprite[index].img.img,
			&data->sprite[index].img.bits_per_pixel,
			&data->sprite[index].img.line_length,
			&data->sprite[index].img.endian);
		if (!data->sprite[index].img.addr)
			errors("Invalid image address", data);
		index++;
	}
}

void	convert_tex(t_data *data)
{
	int index;

	index = 0;
	while (index <= 3)
	{
		check_type_wall(data, data->wall[index].path, index);
		if (!data->wall[index].img.img)
			errors("Failed to convert a texture", data);
		data->wall[index].img.addr =
			mlx_get_data_addr(data->wall[index].img.img,
			&data->wall[index].img.bits_per_pixel,
			&data->wall[index].img.line_length, &data->wall[index].img.endian);
		if (!data->wall[index].img.addr)
			errors("Invalid image address", data);
		index++;
	}
	convert_sprite(data);
}

void	parse_tex(char *input, t_data *data, int index)
{
	int i;

	i = 0;
	while (input[i] == ' ')
		i++;
	i += 3;
	while (input[i] == ' ')
		++i;
	if (data->wall[index].filled)
		errors("Multiple declerations of a texture", data);
	data->wall[index].path = ft_strdup(input + i);
	data->wall[index].filled = 1;
	if (!data->wall[index].path)
		errors("Memory fault", data);
}
