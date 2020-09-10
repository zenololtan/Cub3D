/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 14:24:52 by zenotan       #+#    #+#                 */
/*   Updated: 2020/09/10 17:29:22 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include "../gnl/get_next_line.h"
#include <fcntl.h>

void	check_orientation(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)data->pos.x] == 'W')
	{
		data->dir.x = -1;
		data->plane.y = -0.66667;
	}
	if (data->map[(int)data->pos.y][(int)data->pos.x] == 'E')
	{
		data->dir.x = 1;
		data->plane.y = 0.66667;
	}
	if (data->map[(int)data->pos.y][(int)data->pos.x] == 'N')
	{
		data->dir.y = -1;
		data->plane.x = 0.66667;
	}
	if (data->map[(int)data->pos.y][(int)data->pos.x] == 'S')
	{
		data->dir.y = 1;
		data->plane.x = -0.66667;
	}
	data->map[(int)data->pos.y][(int)data->pos.x] = '0';
	data->pos.x += 0.5;
	data->pos.y += 0.5;
}

void	parse_map_data(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (ft_strchr("NSWE", data->map[y][x]))
			{
				if (data->spawn.x || data->spawn.y)
					errors("Multiple spawn points found in the map", data);
				data->spawn.x = (double)x;
				data->spawn.y = (double)y;
				data->pos = data->spawn;
				check_orientation(data);
			}
			if (data->map[y][x] > '1' && data->map[y][x] <= '9')
				data->spritenum++;
			x++;
		}
		x = 0;
		y++;
	}
}

int		valid_map_line(char *line)
{
	int i;
	int ret;

	i = 0;
	ret = -1;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (2);
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && !ft_strchr("NEWS ", line[i]))
			return (0);
		if (line[i] != '1' && line[i] != ' ')
			ret = 1;
		i++;
	}
	return (ret);
}

void	get_lines(t_data *data, char *line, int fd)
{
	int ret;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (!valid_map_line(line))
			errors("map contains invalid information", data);
		if (valid_map_line(line) == 1 && data->map_check == 1)
			errors("Map contains spaces", data);
		if (valid_map_line(line) == 2)
			data->map_check = 1;
		else
			data->map_check = 0;
		if (valid_map_line(line) != 2)
			join_map_lines(data, line);
		free(line);
	}
}

void	parse_map(t_data *data, char *line, int fd)
{
	if (!valid_map_line(line))
		errors("Map contains incorrect data", data);
	data->map_str = ft_strdup(line);
	if (!data->map_str)
		errors("Failed to duplicating a map line", data);
	get_lines(data, line, fd);
	if (close(fd) == -1)
		errors("Failed to close the .cub file", data);
	data->map = ft_split(data->map_str, '\n');
	if (!data->map)
		errors("Failed to malloc the map string", data);
}
