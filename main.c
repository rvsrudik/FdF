#include "fdf.h"

//void	ft_determ_windows_params(t_window *window)
//{
//	window->hight = 400;
//	window->width = 500;
//	window->position_x = 50;
//	window->position_y = 50;
//}
//
//
//static void ft_key_hook(t_window *window)
//{
//	mlx_key_hook(window->win, ft_my_key_func, window);
//}
//
//
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
//
//
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
////	while (i < 4)
////	{
////		data_adr[i] = 'g';
////		i++;
////	}
////	data_adr[0] = 11;
////	data_adr[1] = 11;
////	data_adr[2] = 11;
////	data_adr[3] = 'B';
////	data_adr[4] = '0';
////	data_adr[5] = 'B';
//
//
//
//			mlx_put_image_to_window(window->mlx, window->win, window->img, window->position_x, window->position_y);
//
//
//	mlx_pixel_put(window->mlx, window->win, 50, 51, 1242520);
//	ft_key_hook(window);
//
//	mlx_loop(window->mlx);
//	return 0;
//}

void ft_usage()
{
	ft_putstr("usage: ./fdf [file_name]\n");
	exit(0);
}

void ft_wrong_fd()
{
	ft_putstr("Can't read from file.\n");
	exit(0);
}

void	ft_count_lines(int fd, t_window *window)
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

char		**ft_count_pixels_in_line(char *line, t_window *window)
{
	char 	**pixels_from_line;
	int 	pixels;
	int 	i;

	i = 0;
	pixels = 0;
	pixels_from_line = ft_strsplit(line, ' ');

	while (pixels_from_line[i])
	{
		pixels++;
		i++;
	}

	window->pixels_width = pixels;
	return (pixels_from_line);
}

static int	ft_hex_to_dig(char color[])
{
	int		dig1;
	int 	dig2;
	char 	*tmp;

	dig1 = color[0];
	dig2 = color[1];
	if (ft_isalnum(dig1))
		dig1 -= '0';
	else if ((tmp = ft_strchr("abcdef", dig1)))
		dig1 = *tmp - 'a' + 10;

	printf(">>%c\n", dig1);
	return ((dig1 * 16) + dig2);
}

static void	ft_determ_pixel_color(t_pixel_info *pixel_info, char *color)
{
	char color_hex[2];
	if (!color)
	{
		pixel_info->default_color_r = 255;
		pixel_info->default_color_g = 255;
		pixel_info->default_color_b = 255;
	}
	else
	{
		while (*color != '\0')
			color++;
		color--;
		color_hex[1] = *color;
		color--;
		color_hex[0] = *color;
		pixel_info->default_color_b = ft_hex_to_dig(color);
	}
	printf("%s\n", color);
}

void	ft_determ_pixel_info(int y, t_pixel_info **pixels_arr, t_window *window, char **pixels_from_line)
{
	int				start_pixel;
	int				i;
	char			**hight_agn_color;
	t_pixel_info	*pixel_info;

	i = 0;
	start_pixel = y * window->pixels_width;
	while (i < window->pixels_width)
	{
		hight_agn_color = ft_strsplit(pixels_from_line[i], ',');
		pixels_arr[start_pixel] = (t_pixel_info*)malloc(sizeof(t_pixel_info));
		pixels_arr[start_pixel]->current_y = y;
		pixels_arr[start_pixel]->default_y = y;
		pixels_arr[start_pixel]->current_x = i;
		pixels_arr[start_pixel]->default_x = i;
		pixels_arr[start_pixel]->default_z = ft_atoi(hight_agn_color[0]);
		pixels_arr[start_pixel]->current_z = ft_atoi(hight_agn_color[0]);
		ft_determ_pixel_color(pixels_arr[start_pixel], hight_agn_color[1]);
		start_pixel++;
		i++;
	}
}

void	ft_fill_pixel_arr(t_pixel_info **pixels_arr, t_window *window, char **pixels_from_line)
{
	int 	y;

	y = 0;
	ft_determ_pixel_info(y, pixels_arr, window, pixels_from_line);
}

int		main(int argc, char **argv)
{
	char			*line;
	int				fd;
	t_window		*window;
	t_pixel_info	**pixels_arr;
	char 			**pixels_from_line;

	if (argc != 2)
		ft_usage();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_wrong_fd();
	window = (t_window*)malloc(sizeof(*window));
	ft_count_lines(fd, window);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	pixels_from_line = ft_count_pixels_in_line(line, window);
	pixels_arr = (t_pixel_info**)malloc(sizeof(t_pixel_info*) * window->pixels_hight * window->pixels_width);
	ft_fill_pixel_arr(pixels_arr, window, pixels_from_line);
//	printf("|%d|\n", pixels_arr[9]->default_y);
	close(fd);
	return (0);
}