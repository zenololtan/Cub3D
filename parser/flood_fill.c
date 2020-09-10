/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 13:30:05 by zenotan       #+#    #+#                 */
/*   Updated: 2020/09/10 15:38:39 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"

int				count_rows(t_data *data)
{
	int	y;

	y = 0;
	while (data->map[y] != NULL)
		++y;
	return (y);
}

void			flood_fill(t_data *data, int x, int y, char **map)
{
	if (y < 0 || x < 0 || y >= count_rows(data) || x >= (int)ft_strlen(map[y]))
		errors("Walls in the map have not been closed off", data);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (map[y][x] == ' ')
		errors("Empty areas in map", data);
	map[y][x] = 'x';
	flood_fill(data, x, y + 1, map);
	flood_fill(data, x, y - 1, map);
	flood_fill(data, x + 1, y, map);
	flood_fill(data, x - 1, y, map);
	flood_fill(data, x + 1, y + 1, map);
	flood_fill(data, x + 1, y - 1, map);
	flood_fill(data, x - 1, y + 1, map);
	flood_fill(data, x - 1, y - 1, map);
}

void			check_map(t_data *data)
{
	char	**tmp_map;
	int		x;
	int		y;

	x = (int)data->pos.x + 0.5;
	y = (int)data->pos.y + 0.5;
	tmp_map = ft_split(data->map_str, '\n');
	if (!data->map)
		errors("Failed to malloc the map string for floodfill", data);
	flood_fill(data, x, y, tmp_map);
	free_arrays(tmp_map);
}
