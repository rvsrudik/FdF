//#include "fdf.h"
//
//static void	ft_exit_program(t_window *window)
//{
//	mlx_clear_window (window->mlx, window->win);
//	mlx_destroy_window(window->mlx, window->win);
//	free(window);
//	exit(0);
//}
//
//static void ft_clear_window(t_window *window)
//{
//	mlx_clear_window (window->mlx, window->win);
//	mlx_string_put ( window->mlx, window->win, 10, 10 , 111111, "Exit = Q");
//}
//
//static void ft_move_image(int keycode, t_window *window)
//{
//	if (keycode == 126 && window->position_y > 0)
//		window->position_y -= 15;
//	if (keycode == 125 && window->position_y < window->hight - 15)
//		window->position_y += 15;
//	if (keycode == 123 && window->position_x > 0)
//		window->position_x -= 15;
//	if (keycode == 124 && window->position_x < window->width - 15)
//		window->position_x += 15;
//
//	mlx_clear_window(window->mlx, window->win);
//	mlx_put_image_to_window(window->mlx, window->win, window->img, window->position_x, window->position_y);
//	mlx_string_put ( window->mlx, window->win, 10, 10 , 111111, "Exit = Q");
//
//}
//
//int			ft_my_key_func(int keycode, t_window *window)
//{
//	printf("key event %d\n", keycode);
//	if (keycode == 12)
//		ft_exit_program(window);
//	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
//		ft_move_image(keycode, window);
//	if (keycode == 8)
//		ft_clear_window(window);
//	return (0);
//}
