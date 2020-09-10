/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_res_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 19:29:21 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/10 17:14:40 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"

int		valid_num(char *num)
{
	int		i;

	i = 0;
	if (!num)
		return (0);
	while (num[i] != '\0')
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	if (i >= 10)
		return (-1);
	return (1);
}

void	parse_res(char **input, t_data *data)
{
	if (!input[1] || !input[2] || input[3])
		errors("Invalid information, cannot parse resolution", data);
	if (data->res_check)
		errors("Multiple declarations of resolution", data);
	if (!valid_num(input[1]) || !valid_num(input[2]))
		errors("Invalid resolution", data);
	data->width = ft_atoi(input[1]);
	data->height = ft_atoi(input[2]);
	if (valid_num(input[1]) == -1)
		data->width = 4000;
	if (valid_num(input[2]) == -1)
		data->height = 4000;
	if (data->width == 0 || data->height == 0)
		errors("Invalid resolution", data);
	data->res_check = 1;
}

char	*strjoiner(char **input)
{
	char	*line;
	char	*tmp;
	int		index;

	index = 1;
	line = "";
	while (input[index])
	{
		tmp = line;
		line = ft_strjoin(line, input[index]);
		if (!line)
			return (NULL);
		if (index != 1)
			free(tmp);
		index++;
	}
	return (line);
}

char	**line_checker(char *line, t_data *data)
{
	int		i;
	int		kommas;
	char	**color;

	i = 0;
	kommas = 0;
	while (line[i])
	{
		if (line[i] == ',')
			kommas++;
		i++;
	}
	if (kommas > 2)
		errors("Too many kommas in color data", data);
	color = ft_split(line, ',');
	if (!color)
		errors("Failed to split color code", data);
	return (color);
}

void	parse_fc(char **input, t_data *data, int i)
{
	char *line;
	char **color;

	if (!input[1])
		errors("No color values found", data);
	if (data->fc[i].filled)
		errors("Multiple declarations for a ceiling or floor color", data);
	line = strjoiner(input);
	if (!line)
		errors("Failed the strjoin while parsing floor ad ceiling", data);
	color = line_checker(line, data);
	if (!color)
		errors("Failed to split color code", data);
	if (!valid_num(color[0]) || !valid_num(color[1]) ||
		!valid_num(color[2]) || color[3] != NULL)
		errors("Invalid color code, ", data);
	data->fc[i].r = ft_atoi(color[0]);
	data->fc[i].g = ft_atoi(color[1]);
	data->fc[i].b = ft_atoi(color[2]);
	if (data->fc[i].r > 255 || data->fc[i].g > 255 || data->fc[i].b > 255)
		errors("Invallid color code", data);
	data->fc[i].value = get_color(data->fc[i]);
	data->fc[i].filled = 1;
	free(line);
	free_arrays(color);
}
