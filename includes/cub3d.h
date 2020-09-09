/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 18:00:29 by zenotan       #+#    #+#                 */
/*   Updated: 2020/09/09 14:46:30 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef	enum		e_defenitions
{
	KEYPRESS = 2,
	KEYRELEASE = 3,
	CLOSE = 17,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	LEFT = 123,
	RIGHT = 124,
	ESC = 53,
}					t_defenitions;

typedef	struct		s_u_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
	int				filled;
	int				value;
}					t_u_color;

typedef	union		u_uncolor
{
	unsigned int	color;
	t_u_color		argb;
}					t_uncolor;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				value;
	int				filled;
}					t_color;

typedef struct		s_i_pos
{
	int				x;
	int				y;
}					t_i_pos;

typedef struct		s_d_pos
{
	double			x;
	double			y;
}					t_d_pos;

typedef struct		s_mlx_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx_img;

typedef struct		s_sprite
{
	t_mlx_img		img;
	t_d_pos			pos;
	char			*path;
	int				texwidth;
	int				texheight;
	int				color;
	int				filled;
}					t_sprite;

typedef struct		s_spritedata
{
	t_sprite		sprite;
	t_d_pos			pos;
	double			dist;
}					t_spritedata;

typedef struct		s_tex
{
	t_mlx_img		img;
	char			*path;
	int				texwidth;
	int				texheight;
	double			step;
	double			wallx;
	t_i_pos			tex;
	double			texpos;
	int				color;
	int				filled;
}					t_tex;

typedef struct		s_bmp
{
	int				fd;
}					t_bmp;

typedef	struct		s_input
{
	int				horizontal;
	int				vertical;
	int				turn;
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				turn_left;
	int				turn_right;
	int				shift;
}					t_input;

typedef struct		s_spritecaster
{
	int				i;
	int				d;
	int				y;
	int				stripex;
	int				texx;
	int				texy;
	int				spritescreenx;
	int				spriteheight;
	int				spritewidth;
	int				drawstarty;
	int				drawendy;
	int				drawstartx;
	int				drawendx;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
}					t_spritecaster;

typedef struct		s_raycaster
{
	t_d_pos			raydir;
	t_d_pos			sidedist;
	t_d_pos			deltadist;
	t_d_pos			map;
	double			perpwalldist;
	t_i_pos			step;
	int				hit;
	int				side;
	int				drawstart;
	int				drawend;
	int				lineheight;
	int				x;
}					t_raycaster;

typedef struct		s_data
{
	int				width;
	int				height;
	int				res_check;
	int				bmp_fd;
	int				bmp_padding;
	int				bmp_filesize;
	t_tex			wall[4];
	t_sprite		sprite[9];
	t_spritedata	*spriteindex;
	int				i;
	int				spritenum;
	double			*zbuffer;
	t_color			fc[2];
	char			*map_str;
	char			**map;
	t_d_pos			spawn;
	int				map_check;
	int				bmp;
	void			*mlx;
	void			*mlx_win;
	int				frame;
	t_mlx_img		img[2];
	t_d_pos			pos;
	t_d_pos			dir;
	t_d_pos			plane;
	double			move_speed;
	t_input			input;
	int				free;
	int				multiple_sprites;
}					t_data;

void				file_check(int argv, char **argc, t_data *data);
void				reset_data(t_data *data);
void				parse_map_data(t_data *data);
void				parse_map(t_data *data, char *line, int fd);
void				parse_tex(char *input, t_data *data, int index);
void				parse_sprite_data(char *input, t_data *data);
void				parse_sprite(t_data *data);
void				parse_res(char **input, t_data *data);
void				parse_fc(char **input, t_data *data, int i);
void				join_map_lines(t_data *data, char *s2);
char				*strjoiner(char **input);
int					check_name(char *str);
int					valid_line(char *line);
int					valid_num(char *num);
void				convert_tex(t_data *data);
void				check_map(t_data *data);
void				check_sprites(t_data *data);
void				ft_bmp(t_data *data);
void				draw_tex(t_data *data, t_raycaster *ray, int index);
void				ft_mlx_pixel_put(t_mlx_img *img,
					int x, int y, unsigned int color);
int					get_color(t_color color);
void				draw_floor_ceiling(t_data *data, t_raycaster *ray);
void				draw_wall(t_data *data, int x, int drawstart,
						int drawend, t_color color);
unsigned int		fog_color(double distance, unsigned int color);
int					close_window(t_data *data);
void				free_struct(t_data *data);
void				free_arrays(char **str);
void				init_raycaster(t_data *data);
void				errors(char *str, t_data *data);
void				insertion_sort(t_data *data);
void				sprite_cast(t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
void				detect_movement(t_data *data);

#endif
