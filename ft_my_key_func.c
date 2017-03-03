#include "fdf.h"

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
	{
		allstruct->image->current_zoom += 1;
		allstruct->image->current_location_y -= allstruct->image->current_zoom/2;
		allstruct->image->current_location_x -= allstruct->image->current_zoom/2;
		ft_use_img_setting(allstruct->image, allstruct->pixels_arr, allstruct->window);
	}
	if ((keycode == 78 || keycode == 27) && allstruct->image->current_zoom > 1)
	{
		allstruct->image->current_zoom -= 1;
		allstruct->image->current_location_y += allstruct->image->current_zoom/2;
		allstruct->image->current_location_x += allstruct->image->current_zoom/2;
		ft_use_img_setting(allstruct->image, allstruct->pixels_arr, allstruct->window);
	}
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->window->width, allstruct->window->high);
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
	if (keycode == 12)
		allstruct->image->current_angle_x -= 5;
	if (keycode == 13)
		allstruct->image->current_angle_x += 5;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->window->width, allstruct->window->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
							allstruct->image->current_location_x, allstruct->image->current_location_y);
}

static void ft_rotate_y(int keycode, t_allstruct *allstruct)
{
	if (keycode == 0)
		allstruct->image->current_angle_y -= 3;
	if (keycode == 1)
		allstruct->image->current_angle_y += 3;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->window->width, allstruct->window->high);
	ft_draw_image(allstruct->window, allstruct->image, allstruct->pixels_arr);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
							allstruct->image->current_location_x, allstruct->image->current_location_y);
}

static void ft_rotate_z(int keycode, t_allstruct *allstruct)
{
	if (keycode == 6)
		allstruct->image->current_angle_z -= 3;
	if (keycode == 7)
		allstruct->image->current_angle_z += 3;
	mlx_destroy_image(allstruct->window->mlx, allstruct->image->img);
	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	allstruct->image->img = mlx_new_image(allstruct->window->mlx, allstruct->window->width, allstruct->window->high);
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
	if (keycode == 12 || keycode == 13)
		ft_rotate_x(keycode, allstruct);
	if (keycode == 0 || keycode == 1)
		ft_rotate_y(keycode, allstruct);
	if (keycode == 6 || keycode == 7)
		ft_rotate_z(keycode, allstruct);
	return (0);
}
