#include "fdf.h"

void ft_printf_pixel_info(t_pixel_info *pixel_info)
{
	printf("----------------------------------------------\n");
	printf("default: x = %d, y = %d, z = %d\n", pixel_info->default_x, pixel_info->default_y, pixel_info->default_z);
//	printf("current: x = %d, y = %d, z = %d\n", pixel_info->current_x, pixel_info->current_y, pixel_info->current_z);
	printf("default: r = %d, g = %d, b = %d\n", pixel_info->default_color_r, pixel_info->default_color_g, pixel_info->default_color_b);
	printf("----------------------------------------------\n");
}

static void		ft_count_lines(int fd, t_window *window)
{
	int			lines;
	char		buff[2000];
	int 		ret;

	lines = 0;
	while ((ret = read(fd, buff, 2000)))
	{
		int i;
		i = 0;
		while (i < ret)
		{
			if (buff[i] == '\n')
				lines++;
			i++;
		}
	}
	window->pixels_hight = lines;
}

static int		ft_count_pixel_width(char **pixels_line_array)
{
	int pixels;

	pixels = 0;
	while (pixels_line_array[pixels])
		pixels++;
	return (pixels);
}




void	ft_put_pixel_to_image(t_data_im_addr *data_im_adr, int x, int y, int color[])
{
	int i;
	i = ((data_im_adr->size_line * (y)) + (x * 4));

	data_im_adr->data_im_adr[i] = color[2];
	data_im_adr->data_im_adr[i + 1] = color[1];
	data_im_adr->data_im_adr[i + 2] = color[0];
}


void	ft_draw_image(t_window *window, t_image *image, t_pixel_info **pixels_arr)
{
	int i = 0;
	int color[3];
	t_data_im_addr *data_im_addr;

	data_im_addr = (t_data_im_addr*)malloc(sizeof(*data_im_addr));
	data_im_addr->data_im_adr = mlx_get_data_addr(image->img, &data_im_addr->bits_per_pixel, &data_im_addr->size_line, &data_im_addr->endian);

	while (i < window->pixels_width * window->pixels_hight)
	{
		color[0] = pixels_arr[i]->default_color_r;
		color[1] = pixels_arr[i]->default_color_g;
		color[2] = pixels_arr[i]->default_color_b;
		pixels_arr[i]->draw_x = pixels_arr[i]->current_x;
		pixels_arr[i]->draw_y = pixels_arr[i]->current_y;
		ft_put_pixel_to_image(data_im_addr, pixels_arr[i]->draw_x, pixels_arr[i]->draw_y, color);
		i++;
	}
	i = 0;
	ft_line(pixels_arr[0], pixels_arr[1], window, image, data_im_addr);
}

void	ft_set_img_setting(t_image *image)
{
	image->default_angle_x = ANGLE_X;
	image->default_angle_z = ANGLE_Y;
	image->default_angle_z = ANGLE_Z;
	image->default_location_x = DEFAULT_LOCATION_X;
	image->default_location_y = DEFAULT_LOCATION_Y;
	image->default_zoom = ZOOM;

	image->current_angle_x = image->default_angle_x;
	image->current_angle_z = image->default_angle_y;
	image->current_angle_z = image->default_angle_z;
	image->current_location_x = image->default_location_x;
	image->current_location_y = image->default_location_y;
	image->current_zoom = image->default_zoom;



}

void	ft_use_img_setting(t_image *image, t_pixel_info **pixels_arr, t_window *window)
{
	int i;

	i = 0;
	while (i < window->pixels_width * window->pixels_hight)
	{
		pixels_arr[i]->current_x = pixels_arr[i]->default_x * image->current_zoom;
		pixels_arr[i]->current_y = pixels_arr[i]->default_y * image->current_zoom;
		i++;
	}
}

void	ft_fdf(t_window *window, t_pixel_info **pixels_arr, char *name)
{
	t_image			*image;
	t_allstruct		*allstruct;


	window->high = WINDOW_HIGH;
	window->width = WINDOW_WIDTH;
	allstruct = (t_allstruct*)malloc(sizeof(*allstruct));
	image = (t_image*)malloc(sizeof(*image));
	allstruct->window = window;
	allstruct->image = image;
	allstruct->pixels_arr = pixels_arr;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->high, name);
	image->img = mlx_new_image(window->mlx, window->width, window->high);
	ft_set_img_setting(image);
	ft_use_img_setting(image, pixels_arr, window);

	ft_draw_image(window, image, pixels_arr);
	mlx_put_image_to_window(window->mlx, window->win, image->img, DEFAULT_LOCATION_X, DEFAULT_LOCATION_Y);
	mlx_hook(window->win, 2, 5, ft_my_key_func, allstruct);
	mlx_loop(window->mlx);
}

int		main(int argc, char **argv)
{
	char			*line;
	int				fd;
	t_window		*window;
	t_pixel_info	**pixels_arr;
	char 			**pixels_line_array;

	if (argc != 2)
		ft_error_number_of_params();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error_wrong_fd();
	window = (t_window*)malloc(sizeof(*window));
	ft_count_lines(fd, window);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	pixels_line_array = ft_pixels_line_to_array(line, window);
	window->pixels_width = ft_count_pixel_width(pixels_line_array);
	pixels_arr = (t_pixel_info**)malloc(sizeof(t_pixel_info*) * window->pixels_hight * window->pixels_width);
	ft_read_and_fill_pixel_arr(pixels_arr, window, pixels_line_array, fd);
	ft_fdf(window, pixels_arr, argv[1]);

	close(fd);
	return (0);
}