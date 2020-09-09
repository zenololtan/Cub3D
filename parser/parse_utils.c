/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 19:27:20 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/09 14:54:17 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../lft/libft.h"

void	check_sprites(t_data *data)
{
	int i;
	int check;

	check = 1;
	i = 0;
	while (check <= data->i)
	{
		while (data->map_str[i])
		{
			if (data->map_str[i] == check + 49)
				break ;
			i++;
			if (data->map_str[i] == '\0')
				errors("A sprite is not included in map", data);
		}
		i = 0;
		check++;
	}
}

void	join_map_lines(t_data *data, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ret;
	char	*s1;

	s1 = data->map_str;
	if (!s1)
	{
		data->map_str = ft_strdup(s2);
		if (!data->map_str)
			errors("Something went wrong with duplicating a map line", data);
		return ;
	}
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1len + s2len + 2));
	if (!ret)
		errors("Something went wrong with mallocing a map line", data);
	ft_memcpy(ret, s1, s1len);
	ft_strlcpy(ret + s1len + 1, s2, s2len + 1);
	ret[s1len] = '\n';
	free(data->map_str);
	data->map_str = ret;
}

int		check_name(char *str)
{
	int		i;

	i = ft_strlen(str);
	if (str[i - 1] == 'b' && str[i - 2] == 'u' && \
		str[i - 3] == 'c' && str[i - 4] == '.')
		return (1);
	return (0);
}

int		valid_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] == 'N' && line[i + 1] == 'O') || \
		(line[i] == 'S' && line[i + 1] == 'O') || \
		(line[i] == 'E' && line[i + 1] == 'A') || \
		(line[i] == 'W' && line[i + 1] == 'E') || \
		line[i] == 'R' || line[i] == 'F' || \
		line[i] == 'C' || line[i] == 'S')
		return (1);
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		return (2);
	if (line[i] == '\0' || line[i] == '\n')
		return (-1);
	return (0);
}

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
	return (1);
}
