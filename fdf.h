

#ifndef FDF_H
# define FDF_H

#define WINDOW_HIGH 1024
#define WINDOW_WIDTH 1600
#define ANGLE_X 60
#define ANGLE_Y 25
#define ANGLE_Z 0


#define DEFAULT_LOCATION_X 0
#define DEFAULT_LOCATION_Y 0
#define ZOOM 1


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"
#include <math.h>

char	*ft_strnew_bchar(size_t size, char c);

typedef struct	s_window
{
	void		*win;
	void		*mlx;
	int			width;
	int			high;
	int			pixels_width;
	int			pixels_hight;
}				t_window;


typedef struct	s_imege
{
	void		*img;
	int			width;
	int			high;

	int			max_x;
	int			min_x;
	int			max_y;
	int			min_y;
	int			default_angle_x;
	int			default_angle_y;
	int			default_angle_z;
	int			default_location_x;
	int			default_location_y;
	int			default_object_hight;
	double		default_zoom;
	int			default_image_hight;
	int			default_image_widht;
	int			current_angle_x;
	int			current_angle_y;
	int			current_angle_z;
	int			current_location_x;
	int			current_location_y;
	int			current_object_hight;
	double		current_zoom;
	int			current_image_hight;
	int			current_image_widht;

}				t_image;

typedef struct	s_data_im_addr
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*data_im_adr;
	t_image		*image;
	t_window	*window;
}				t_data_im_addr;

typedef struct	s_pixel_info
{
	int			default_x;
	int			default_y;
	int			default_z;
	int			default_color_r;
	int			default_color_g;
	int			default_color_b;
	int			current_x;
	int			current_y;
	int			current_z;
	int			current_color_r;
	int			current_color_g;
	int			current_color_b;
	int			draw_x;
	int			draw_y;
}				t_pixel_info;


typedef struct	s_allstruct
{
	t_window	*window;
	t_image		*image;
	t_pixel_info **pixels_arr;
}				t_allstruct;

typedef struct		s_line
{
	int				deltax;
	int				deltay;
	int				signx;
	int				signy;
	int				error;
	int				error2;
	int				x1;
	int				y1;
	int				y2;
	int				color_r;
	int				color_g;
	int				color_b;
	int				x2;
}					t_line;

void	ft_line(t_pixel_info *a, t_pixel_info *b, t_window *wind,  t_image *img, t_data_im_addr *data_im_addr);
void	ft_use_img_setting(t_image *image, t_pixel_info **pixels_arr, t_window *window);
void	ft_draw_image(t_window *window, t_image *image, t_pixel_info **pixels_arr);



void	ft_put_pixel_to_image(t_data_im_addr *data_im_adr, int x, int y, int color[]);




int		ft_my_key_func(int keycode, t_allstruct *allstruct);

void	ft_determ_pixel_info(int y, t_pixel_info **pixels_arr,
		t_window *window, char **pixels_from_line);
void	ft_read_and_fill_pixel_arr(t_pixel_info **pixels_arr,
		t_window *window, char **pixels_line_array, int fd);
char	**ft_pixels_line_to_array(char *line, t_window *window);
int		ft_hex_to_dig(char color[]);
/*
 **---------------------------------------------------------------------
 **----------------------------->ERRORS<--------------------------------
*/
void	ft_error_number_of_params();
void	ft_error_wrong_fd();
void	ft_error_wrong_map();
/*
 **---------------------------------------------------------------------
 **------------------------------>END<----------------------------------
*/



#endif