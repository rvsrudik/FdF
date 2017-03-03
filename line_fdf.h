

typedef struct		s_pix
{
	int				x;
	int				y;
	int				x0;
	int				y0;
	int				z;
	int				c;
	struct s_pix	*n;
}					t_pix;

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	char			*name;
	int				width;
	int				height;
	int				krok;
	int				vidx;
	int				vidy;
	t_pix			*pix;
}					t_window;

typedef struct		s_len
{
	int				len;
}					t_len;

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



#endif
