cc -o fdf_vrud \
\
 help_func/libmlx.a \
 help_func/libft.a \
 help_func/get_next_line.c \
\
 reading_data/ft_hex_to_dig.c \
 reading_data/ft_errors.c \
 reading_data/ft_read_and_fill_pixel_arr.c \
 reading_data/ft_determ_pixel_info.c \
\
 line_ft_line.c \
 ft_my_key_func.c \
 main.c \
 \
 -Iincludes -framework OpenGL -framework AppKit
