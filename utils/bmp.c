/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/08 13:09:37 by zenotan       #+#    #+#                 */
/*   Updated: 2020/09/10 20:17:48 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void	set_file_header(t_data *data)
{
	char	bmp_header[14];
	int		write_val;

	bmp_header[0] = 0x42;
	bmp_header[1] = 0x4D;
	*(unsigned int *)(bmp_header + 2) = data->bmp_filesize;
	*(short *)(bmp_header + 6) = 0;
	*(short *)(bmp_header + 8) = 0;
	*(unsigned int *)(bmp_header + 10) = 54;
	write_val = write(data->bmp_fd, bmp_header, 14);
	if (write_val == -1)
		errors("Failed to write file header to the .bmp file", data);
}

static void	set_img_header(t_data *data)
{
	char	bmp_image_header[40];
	int		write_val;

	*(unsigned int *)(bmp_image_header) = 40;
	*(int *)(bmp_image_header + 4) = (int)data->width;
	*(int *)(bmp_image_header + 8) = (int)data->height;
	*(short *)(bmp_image_header + 12) = 1;
	*(short *)(bmp_image_header + 14) = 24;
	*(unsigned int *)(bmp_image_header + 16) = 0;
	*(unsigned int *)(bmp_image_header + 20) = 0;
	*(unsigned int *)(bmp_image_header + 24) = 0;
	*(unsigned int *)(bmp_image_header + 28) = 0;
	*(unsigned int *)(bmp_image_header + 32) = 0;
	*(unsigned int *)(bmp_image_header + 36) = 0;
	write_val = write(data->bmp_fd, bmp_image_header, 40);
	if (write_val == -1)
		errors("Failed to write img header to the .bmp file", data);
}

static void	draw_bmp(t_data *data)
{
	int				x;
	int				y;
	char			*pixel_addr;
	unsigned int	pixel;

	y = data->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->width)
		{
			pixel_addr = data->img[data->frame].addr +
						(y * data->img[data->frame].line_length + x *
						(data->img[data->frame].bits_per_pixel / 8));
			pixel = *(unsigned int *)pixel_addr;
			if (write(data->bmp_fd, &pixel, 3) == -1)
				errors("Failed to write to .bmp file", data);
			x++;
		}
		if (write(data->bmp_fd, "/0/0/0", data->bmp_padding) == -1)
				errors("Failed to write to .bmp file", data);
		y--;
	}
}

void		ft_bmp(t_data *data)
{
	data->bmp_fd =
		open("./screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (data->bmp_fd == -1)
		errors("Failed to create a .bmp file", data);
	data->bmp_padding = 0;
	while ((3 * data->width + data->bmp_padding) % 4 != 0)
		++data->bmp_padding;
	data->bmp_filesize =
		54 + (3 * (data->width + data->bmp_padding) * data->height);
	set_file_header(data);
	set_img_header(data);
	draw_bmp(data);
	close_window(data);
}
