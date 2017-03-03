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

	if (keycode == 69)
	{
		allstruct->image->current_zoom += 1;
		ft_use_img_setting(allstruct->image, allstruct->pixels_arr, allstruct->window);
	}
	if (keycode == 78 && allstruct->image->current_zoom > 1)
	{
		allstruct->image->current_zoom -= 1;
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
//	if (keycode == 125 && allstruct->i->position_y)
//		allstruct->image->current_location_x += 1;
//	if (keycode == 123 && window->position_x > 0)
//		allstruct->image->current_location_x += 1;
//	if (keycode == 124 && window->position_x)
//		allstruct->image->current_location_x += 1;

	mlx_clear_window(allstruct->window->mlx, allstruct->window->win);
	mlx_put_image_to_window(allstruct->window->mlx, allstruct->window->win, allstruct->image->img,
	allstruct->image->current_location_x, allstruct->image->current_location_y);

}


int			ft_my_key_func(int keycode, t_allstruct *allstruct)
{
	printf("key event %d\n", keycode);
	if (keycode == 53)
		ft_exit_program(allstruct);
	if (keycode == 78 || keycode == 69)
		ft_zoom(keycode, allstruct);
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		ft_move_image(keycode, allstruct);
;
	return (0);
}
