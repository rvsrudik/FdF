#include "includes/fdf.h"



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


void ft_x_rotation(t_pixel_info *pixel_info, t_image *image)
{
	float r = 0.01745329252;
	if (image->current_angle_x > 180)
		image->current_angle_x = -180;
	if (image->current_angle_x < -180)
		image->current_angle_x = 180;

//	printf("angle %d\n", image->current_angle_x);
	r = r * image->current_angle_x;
	printf("%d\n", image->current_angle_x);
	pixel_info->current_y = pixel_info->current_y * cos(r) + pixel_info->current_z * sin(r);
	pixel_info->current_z = pixel_info->current_z * cos(r) + pixel_info->current_y * sin(r);
//	pixel_info->current_x = pixel_info->current_x * cos(r) - pixel_info->current_z * sin(r);
//	pixel_info->current_z = pixel_info->current_z * cos(r) + pixel_info->current_x * sin(r);

}

void ft_y_rotation(t_pixel_info *pixel_info, t_image *image)
{
	float r = 0.01745329252;

	r = r * image->current_angle_y;
//	pixel_info->current_x = pixel_info->current_x * cos(r) - pixel_info->current_z * sin(r);
//	pixel_info->current_z = pixel_info->current_z * cos(r) + pixel_info->current_x * sin(r);
}

void ft_z_rotation(t_pixel_info *pixel_info, t_image *image)
{
	float r = 0.01745329252;

	r = r * image->current_angle_z;
//	pixel_info->current_x = pixel_info->current_x * cos(r) + pixel_info->current_y * sin(r);
//	pixel_info->current_y = pixel_info->current_y * cos(r) - pixel_info->current_x * sin(r);

}



void	ft_put_pixel_to_image(t_data_im_addr *data_im_adr, int x, int y, int color[])
{
	int i;
	int start_position_x;
	int start_position_y;
	int diff;
	//int diff2;
//	if (data_im_adr->image->min_x < 0)
//		data_im_adr->image->min_x *= -1;

	diff = data_im_adr->size_line * ((data_im_adr->image->min_y + data_im_adr->image->max_y)/2);
	//diff = 0;
	start_position_x = (data_im_adr->size_line / 2) - ((data_im_adr->image->min_x + data_im_adr->image->max_x)/2 * 4);
	//start_position_x = 0;
	i = (((data_im_adr->size_line * (y)) + (x*4)) + start_position_x) +  (data_im_adr->size_line * data_im_adr->window->high/2 - diff);

	data_im_adr->data_im_adr[i] = color[2];
	data_im_adr->data_im_adr[i + 1] = color[1];
	data_im_adr->data_im_adr[i + 2] = color[0];
}


void	ft_draw_image(t_window *window, t_image *image, t_pixel_info **pixels_arr)
{
	int i = 0;
	int colums;
	int row;
	t_data_im_addr *data_im_addr;
	int 	color[3];

	data_im_addr = (t_data_im_addr*)malloc(sizeof(*data_im_addr));
	data_im_addr->data_im_adr = mlx_get_data_addr(image->img, &data_im_addr->bits_per_pixel, &data_im_addr->size_line, &data_im_addr->endian);
	data_im_addr->image = image;
	data_im_addr->window = window;
	colums = 0;
	row = 0;

	ft_use_img_setting(image, pixels_arr, window);
	while (row < window->pixels_hight - 1)
	{
		while (colums < window->pixels_width - 1)
		{
			ft_line(pixels_arr[colums + (window->pixels_width * row)], pixels_arr[colums + (window->pixels_width * row) + 1], window, image, data_im_addr);
			ft_line(pixels_arr[colums + (window->pixels_width * row)], pixels_arr[colums + (window->pixels_width * row) + window->pixels_width], window, image, data_im_addr);
			colums++;
		}
		ft_line(pixels_arr[colums + (window->pixels_width * row)], pixels_arr[colums + (window->pixels_width * row) + window->pixels_width], window, image, data_im_addr);
		colums = 0;
		row++;
	}
	while (colums < window->pixels_width - 1)
	{
		ft_line(pixels_arr[colums + (window->pixels_width * row)], pixels_arr[colums + (window->pixels_width * row) + 1], window, image, data_im_addr);
		colums++;
	}
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
	image->max_x = 0;
	image->min_x = 0;
	image->max_y = 0;
	image->min_y = 0;
}

void	ft_use_img_setting(t_image *image, t_pixel_info **pixels_arr, t_window *window)
{
	int i;

	i = 0;
	image->max_x = 0;
	image->min_x = 0;
	image->max_y = 0;
	image->min_y = 0;

//	if (image->current_angle_x < 0)
//		image->current_angle_x = 720;

	while (i < window->pixels_width * window->pixels_hight)
	{
		pixels_arr[i]->current_x = pixels_arr[i]->default_x * image->current_zoom;
		pixels_arr[i]->current_y = pixels_arr[i]->default_y * image->current_zoom;
		pixels_arr[i]->current_z = pixels_arr[i]->default_z * image->current_zoom/2;

		pixels_arr[i]->current_color_r = pixels_arr[i]->default_color_r;
		pixels_arr[i]->current_color_g = pixels_arr[i]->default_color_g;
		pixels_arr[i]->current_color_b = pixels_arr[i]->default_color_b;

		ft_x_rotation(pixels_arr[i], image);
		ft_y_rotation(pixels_arr[i], image);
		ft_z_rotation(pixels_arr[i], image);
		if (image->max_x < pixels_arr[i]->current_x)
			image->max_x = pixels_arr[i]->current_x;
		if (image->min_x > pixels_arr[i]->current_x)
			image->min_x = pixels_arr[i]->current_x;
		if (image->max_y < pixels_arr[i]->current_y)
			image->max_y = pixels_arr[i]->current_y;
		if (image->min_y > pixels_arr[i]->current_y)
			image->min_y = pixels_arr[i]->current_y;
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
	t_allstruct		*allstruct;
	char 			**pixels_line_array;

	if (argc != 2)
		ft_error_number_of_params();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error_wrong_fd();
	allstruct = (t_allstruct*)malloc(sizeof(*allstruct));
	allstruct->window = (t_window*)malloc(sizeof(*allstruct->window));
	ft_count_lines(fd, allstruct->window);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	pixels_line_array = ft_pixels_line_to_array(line, allstruct->window);
	allstruct->window->pixels_width = ft_count_pixel_width(pixels_line_array);
	allstruct->pixels_arr = (t_pixel_info**)malloc(sizeof(t_pixel_info*) *  allstruct->window->pixels_hight * allstruct->window->pixels_width);

	ft_read_and_fill_pixel_arr(allstruct, pixels_line_array, fd);
	ft_fdf(allstruct->window, allstruct->pixels_arr, argv[1]);
	close(fd);
	return (0);
}