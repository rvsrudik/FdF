#include "fdf.h"

//void	ft_determ_windows_params(t_window *window)
//{
//	window->hight = 400;
//	window->width = 500;
//	window->position_x = 50;
//	window->position_y = 50;
//}

//void ft_put_pixel_to_image(int x, int y, char *color, t_window *);
//
//
//int main()
//{
//	t_window	*window;
//
//	char		*tmp;
//	int			size = 3;
//	int			color_val;
//
//
//
//	int x = 100;
//	int	y = 100;

//
//
//	window = (t_window*)malloc(sizeof(*window));
//
//	window->mlx = mlx_init();
//	ft_determ_windows_params(window);
//	window->win = mlx_new_window(window->mlx, window->width, window->hight, "mlx 42");
//	window->img = mlx_new_image(window->mlx, window->width, window->hight);
//
//
//	int		bits_per_pixel = 0;
//	int		size_line =  0;
//	int		endian = 0;
//	char	*data_adr;
//
//	data_adr = mlx_get_data_addr(window->img, &bits_per_pixel, &size_line, &endian);
//
//	mlx_string_put ( window->mlx, window->win, 10, 10 , 111111, "Exit = Q");
//
//	printf("b_per_pix |%d|\n", bits_per_pixel);
//	printf("size_line |%d|\n", size_line);
//	printf("endian    |%d|\n", endian);
//
//
//	int i = 0;
//	while (i < 4)
//	{
//		data_adr[i] = 'g';
//		i++;
//	}
//	data_adr[0] = 11;
//	data_adr[1] = 11;
//	data_adr[2] = 11;
//	data_adr[3] = 'B';
//	data_adr[4] = '0';
//	data_adr[5] = 'B';
//
//
//
//			mlx_put_image_to_window(window->mlx, window->win, window->img, window->position_x, window->position_y);
//
//
//	mlx_pixel_put(window->mlx, window->win, 50, 51, 1242520);
//	ft_key_hook(window);
//
//
//	return 0;
//}

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

void	ft_put_pixel_to_image(t_data_im_addr *data_im_adr, t_pixel_info *pixel_arr)
{
	int i;
	i = ((data_im_adr->size_line * (pixel_arr->current_y * 1)) + (pixel_arr->current_x * 1* 4));

	data_im_adr->data_im_adr[i] = pixel_arr->default_color_b;
	data_im_adr->data_im_adr[i + 1] = pixel_arr->default_color_g;
	data_im_adr->data_im_adr[i + 2] = pixel_arr->default_color_r;
}
void	ft_draw_image(t_window *window, t_image *image, t_pixel_info **pixels_arr)
{
	int i = 0;
	t_data_im_addr *data_im_addr;

	data_im_addr = (t_data_im_addr*)malloc(sizeof(*data_im_addr));

	data_im_addr->data_im_adr = mlx_get_data_addr(image->img, &data_im_addr->bits_per_pixel, &data_im_addr->size_line, &data_im_addr->endian);

	while (i < window->pixels_width * window->pixels_hight)
	{
		ft_put_pixel_to_image(data_im_addr, pixels_arr[i]);
		i++;
	}
}

void	ft_fdf(t_window *window, t_pixel_info **pixels_arr, char *name)
{
	t_image_setting *image_setting;
	t_image			*image;

	window->high = 1300;
	window->width = 2000;

	image = (t_image*)malloc(sizeof(*image));

	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->high, "qwe");
	image->img = mlx_new_image(window->mlx, window->width, window->high);
	ft_draw_image(window, image, pixels_arr);

	mlx_put_image_to_window(window->mlx, window->win, image->img, 10, 10);
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



	int start_pixel = 0;
//	while (start_pixel < window->pixels_hight * window->pixels_width)
//	{
//		ft_printf_pixel_info(pixels_arr[start_pixel]);
//		start_pixel++;
//	}
	close(fd);
	return (0);
}