/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sprite.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/20 16:52:07 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/09 14:37:06 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include <stdlib.h>
#include <math.h>

void	calc_distance(t_data *data)
{
	int i;

	i = 0;
	while (i < data->spritenum)
	{
		data->spriteindex[i].dist = pow(data->pos.x -
		data->spriteindex[i].pos.x, 2) + pow(data->pos.y -
		data->spriteindex[i].pos.y, 2);
		i++;
	}
}

void	insertion_sort(t_data *data)
{
	t_spritedata	key;
	int				i;
	int				j;

	i = 1;
	calc_distance(data);
	while (i < data->spritenum)
	{
		key = data->spriteindex[i];
		j = i - 1;
		while (j >= 0 && data->spriteindex[j].dist > key.dist)
		{
			data->spriteindex[j + 1] = data->spriteindex[j];
			j = j - 1;
		}
		data->spriteindex[j + 1] = key;
		i++;
	}
}

void	calc_sprite_data(t_data *data, int x, int y, int i)
{
	if (!data->sprite[data->map[y][x] - 50].filled)
		errors("Map containst a sprite which does not exist", data);
	data->spriteindex[i].sprite = data->sprite[data->map[y][x] - 50];
	data->spriteindex[i].pos.x = (double)x + 0.5;
	data->spriteindex[i].pos.y = (double)y + 0.5;
}

void	parse_sprite(t_data *data)
{
	static int	i;
	int			x;
	int			y;

	x = 0;
	y = 0;
	i = 0;
	data->spriteindex = malloc(sizeof(t_spritedata) * data->spritenum);
	if (!data->spriteindex)
		errors("Memory fault", data);
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] > '1' && data->map[y][x] <= '9')
			{
				calc_sprite_data(data, x, y, i);
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	insertion_sort(data);
}

void	parse_sprite_data(char *input, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[j] == ' ')
		j++;
	j += 2;
	while (input[j] == ' ')
		++j;
	if (data->sprite[data->i].filled)
		errors("Multiple declerations of a sprite texture", data);
	data->sprite[data->i].path = ft_strdup(input + j);
	data->sprite[data->i].filled = 1;
	if (!data->sprite[data->i].path)
		errors("Memory fault", data);
	while (i <= data->i)
	{
		if (!ft_strncmp(data->sprite[data->i].path, data->sprite[i].path,
			ft_strlen(data->sprite[data->i].path)) && i != data->i)
			errors("Multiple inclusions of the same sprite image", data);
		i++;
	}
	data->i++;
}
