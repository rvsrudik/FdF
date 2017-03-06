#include "includes/fdf.h"

static void	ft_exit_program(t_allstruct *allstruct)
{
	int	i;

	i = 0;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window (allstruct->window->mlx, allstruct->window->win);
	mlx_destroy_window(allstruct->window->mlx, allstruct->window->win);
	while (i < allstruct->window->pixels_width * allstruct->window->pixels_hight)
	{
		free(allstruct->pixels_arr[i]);
		i++;
	}
	free(allstruct->pixels_arr);
	exit(0);
}

static void	ft_zoom(int keycode, t_allstruct *allstruct)
{

	if (keycode == 69 || keycode == 24)
		allstruct->image->current_zoom += 1;
	if ((keycode == 78 || keycode == 27) && allstruct->image->current_zoom > 1)
		allstruct->image->current_zoom -= 1;
	if (!(ft_use_img_setting(allstruct->image, allstruct->pixels_arr, allstruct->window)))
	{
		allstruct->image->current_zoom -= 1;
		return;
	}
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->image->width, allstruct->image->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
	allstruct->image->current_location_x, allstruct->image->current_location_y);
}

static void ft_move_image(int keycode, t_allstruct *allstruct)
{
	if (keycode == 126)
		allstruct->image->current_location_y -= 3;
	if (keycode == 125)
		allstruct->image->current_location_y += 3;
	if (keycode == 124)
		allstruct->image->current_location_x += 3;
	if (keycode == 123)
		allstruct->image->current_location_x -= 3;
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
	allstruct->image->current_location_x, allstruct->image->current_location_y);

}

static void ft_rotate_x(int keycode, t_allstruct *allstruct)
{
	if (keycode == 12 || keycode == 4 || keycode == 84)
		allstruct->image->current_angle_x -= 6;
	if (keycode == 13 || keycode == 5 || keycode == 91)
		allstruct->image->current_angle_x += 6;

	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->image->width, allstruct->image->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
							allstruct->image->current_location_x, allstruct->image->current_location_y);
}

static void ft_rotate_y(int keycode, t_allstruct *allstruct)
{
	if (keycode == 1 || keycode == 6 || keycode == 88)
		allstruct->image->current_angle_y -= 6;
	if (keycode == 0 || keycode == 7 || keycode == 86)
		allstruct->image->current_angle_y += 6;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->image->width, allstruct->image->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
							allstruct->image->current_location_x, allstruct->image->current_location_y);
}

void		ft_change_color(int keycode, t_allstruct *allstruct)
{
	if (keycode == 14 && allstruct->image->add_to_color_r > 0)
		allstruct->image->add_to_color_r += 5;
	if (keycode == 15 && allstruct->image->add_to_color_r < 255)
		allstruct->image->add_to_color_r += 5;

	if (keycode == 3 && allstruct->image->add_to_color_g > 0)
		allstruct->image->add_to_color_g -= 5;
	if (keycode == 5 && allstruct->image->add_to_color_g < 255)
		allstruct->image->add_to_color_g += 5;

	if (keycode == 9 && allstruct->image->add_to_color_b > 0)
		allstruct->image->add_to_color_b -= 5;
	if (keycode == 11 && allstruct->image->add_to_color_b < 255)
		allstruct->image->add_to_color_b += 5;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->image->width, allstruct->image->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
							allstruct->image->current_location_x, allstruct->image->current_location_y);
}

int			ft_my_key_func(int keycode, t_allstruct *allstruct)
{
	printf("key event %d\n", keycode);
	if (keycode == 53)
		ft_exit_program(allstruct);
	if (keycode == 78 || keycode == 69 || keycode == 27 || keycode == 24)
		ft_zoom(keycode, allstruct);
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		ft_move_image(keycode, allstruct);
	if (keycode == 12 || keycode == 13 || keycode == 84 || keycode == 91)
		ft_rotate_x(keycode, allstruct);
	if (keycode == 0 || keycode == 1 || keycode == 86 || keycode == 88)
		ft_rotate_y(keycode, allstruct);
	if (keycode == 14 || keycode == 3 || keycode == 9 || keycode == 15 || keycode == 5 || keycode == 11)
		ft_change_color(keycode, allstruct);
	return (0);
}

int			ft_my_mouse_func(int buttom, int x, int y, t_allstruct *allstruct)
{
	if (buttom == 4 || buttom == 5)
		ft_rotate_x(buttom, allstruct);
	if (buttom == 7 || buttom == 6)
		ft_rotate_y(buttom, allstruct);
	return (0);
}

