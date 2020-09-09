/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initial_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zeno <zeno@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/24 18:03:23 by zeno          #+#    #+#                 */
/*   Updated: 2020/09/09 14:47:03 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"
#include "../gnl/get_next_line.h"
#include "../mlx_mac/mlx.h"
#include <fcntl.h>

void	check_data(t_data *data)
{
	int index;

	index = 0;
	if (!data->res_check)
		errors("Missing resolution data from the cub file.", data);
	if (!data->fc[0].filled)
		errors("Missing floor data from the cub file.", data);
	if (!data->fc[1].filled)
		errors("Missing ceilling data from the cub file.", data);
	if (!data->dir.y && !data->dir.x &&
		!data->plane.y && !data->plane.x)
		errors("No spawnpoint in map", data);
	if (!data->pos.x && !data->pos.y)
		errors("Failed to parse player position from the map.", data);
	while (index <= 3 || index < data->i)
	{
		if (!data->wall[index].filled && index <= 3)
			errors("Missing wall data from the cub file.", data);
		if (!data->sprite[index].filled && index < data->i)
			errors("missing sprite data", data);
		index++;
	}
}

void	set_max_res(t_data *data)
{
	int	sizex;
	int	sizey;

	if (data->bmp)
	{
		if (data->height > 16384)
			data->height = 16384;
		if (data->width > 16384)
			data->width = 16384;
		return ;
	}
	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	if (data->width > sizex)
		data->width = sizex;
	if (data->height > sizey)
		data->height = sizey;
}

void	parse_input_data(char *line, t_data *data)
{
	char **input;

	input = ft_split(line, ' ');
	if (!input)
		errors("Could not split the cub data in seperate elements", data);
	if (!ft_strncmp(input[0], "R", 2))
		parse_res(input, data);
	if (!ft_strncmp(input[0], "NO", 3))
		parse_tex(line, data, 0);
	if (!ft_strncmp(input[0], "EA", 3))
		parse_tex(line, data, 1);
	if (!ft_strncmp(input[0], "SO", 3))
		parse_tex(line, data, 2);
	if (!ft_strncmp(input[0], "WE", 3))
		parse_tex(line, data, 3);
	if (!ft_strncmp(input[0], "S", 2))
		parse_sprite_data(line, data);
	if (!ft_strncmp(input[0], "C", 2))
		parse_fc(input, data, 1);
	if (!ft_strncmp(input[0], "F", 2))
		parse_fc(input, data, 0);
	free_arrays(input);
}

void	parse_data(int fd, t_data *data)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1 || !valid_line(line))
		{
			free(line);
			errors("Cub file contents can not be parsed", data);
		}
		if (valid_line(line) == 1)
			parse_input_data(line, data);
		if (valid_line(line) == 2)
			break ;
		free(line);
	}
	parse_map(data, line, fd);
	if (valid_line(line) == 2)
		free(line);
	parse_map_data(data);
}

void	file_check(int argv, char **argc, t_data *data)
{
	int fd;

	reset_data(data);
	if (argv != 2 && argv != 3)
		errors("Invalid amount of arguments", data);
	if (argv == 3)
	{
		if (ft_strncmp(argc[2], "--save", 7))
			errors("Second argument is not recognized", data);
		else
			data->bmp = 1;
	}
	if (!check_name(argc[1]))
		errors("Map file path is invalid", data);
	fd = open(argc[1], O_RDONLY);
	if (fd == -1)
		errors("Failed to open cub file", data);
	if (read(fd, 0, 0) == -1)
		errors("Map is invalid", data);
	parse_data(fd, data);
	check_data(data);
	check_sprites(data);
	check_map(data);
	set_max_res(data);
}
