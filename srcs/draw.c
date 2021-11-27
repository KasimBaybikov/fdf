#include "fdf.h"
#include "mlx.h"

void init_map_mlx_keys(t_fdf *fdf, t_map **map, t_mlx **mlx, t_keys **keys)
{
	*map = fdf->map;
	*mlx = fdf->mlx;
	*keys = fdf->keys;
}

void fill_image(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;

	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			pixel_put(mlx, x, y, 0);
			y++;
		}
		y = 0;
		x++;
	}
}


#include <stdlib.h>
#include <time.h>
#include <math.h>
void put_rect(t_fdf *fdf, t_mlx *mlx)
{
	int x =	fdf->pos_x - (W_RECT / 2);
	int y =	fdf->pos_y - (W_RECT / 2);

	/*int c = color(200, 100, 200);*/
	int red = 200;
	int green = 100;
	int blue = 200;
	while (x < fdf->pos_x + W_RECT / 2)
	{
		while (y < fdf->pos_y + W_RECT / 2)
		{
			/*pixel_put(mlx, x, y, color(0, rand() % 200, rand() % 100, rand() % 200));*/
			pixel_put(mlx, x, y, color(red--, green++, blue));
			if (green == 255)
				green = 100;
			if (red == 0)
				red = 200;
			y++;
		}
		y = fdf->pos_y - (W_RECT / 2);
		x++;
	}
}

t_point make_point(int x, int y)
{
	t_point point;
	point.x = x;
	point.y = y;
	return (point);
}

void check_keys(t_fdf *fdf, t_keys *keys)
{
	/*printf("x = %d, y = %d\n", fdf->pos_x, fdf->pos_y);*/
	if (keys->w)
		fdf->pos_y -= 10;
	if (keys->s)
		fdf->pos_y += 10;
	if (keys->a)
		fdf->pos_x -= 10;
	if (keys->d)
		fdf->pos_x += 10;

	if (fdf->pos_y <= 0)
		fdf->pos_y = HEIGHT;
	if (fdf->pos_y >= HEIGHT + 4)
		fdf->pos_y = 0;

	if (fdf->pos_x <= 0)
		fdf->pos_x = WIDTH;
	if (fdf->pos_x >= WIDTH + 4)
		fdf->pos_x = 0;
}

int draw(t_fdf *fdf, t_mlx *mlx)
{
	t_map *map;
	t_keys *keys;
	t_point point1;
	t_point point2;

	init_map_mlx_keys(fdf, &map, &mlx, &keys);
	check_keys(fdf, keys);

	fill_image(mlx);


	/*point1 = make_point(0, 0);*/
	/*point2 = make_point(WIDTH, HEIGHT);*/
	point1 = make_point(WIDTH, 0);
	point2 = make_point(0, HEIGHT);

	/*point1.color = 0x00FF00;*/
	/*point2.color = 0xFFFF99;*/

	int i = 0;
	for (int i = 0; i < 10; i++)
	{
		point1 = make_point(0 + i, 0);
		point2 = make_point(WIDTH + i, HEIGHT);
		point1.color = 0xFF0099;
		point2.color = 0xFFFF00;
		draw_line_xiaolin_wu(mlx, point1, point2);
	}

	/*for (int i = 0; i < 10; i++)*/
	/*{*/
		point1 = make_point(30 + i, 0);
		point2 = make_point(WIDTH + 30 + i, HEIGHT);
		point1.color = 0xFF0099;
		point2.color = 0xFFFF00;
		draw_line_bresenham(mlx, point1, point2);
	/*}*/

	/*for (int i = 0; i < 10; i++)*/
	/*{*/
		/*point1 = make_point(WIDTH + i, 0);*/
		/*point2 = make_point(0 + i, HEIGHT);*/
		/*point1.color = 0x00FF00;*/
		/*point2.color = 0xFFFF99;*/
		/*draw_line_xiaolin_wu(mlx, point1, point2);*/
	/*}*/
	/*for (int i = 0; i < 10; i++)*/
	/*{*/
		/*point1 = make_point(WIDTH + 15 + i, 0);*/
		/*point2 = make_point(15 + i, HEIGHT);*/
		/*point1.color = 0x00FF00;*/
		/*point2.color = 0xFFFF99;*/
		/*draw_line_bresenham(mlx, point1, point2);*/
	/*}*/
	/*for (int i = 0; i < 10; i++)*/
	/*draw_line_bresenham(mlx, point1, point2);*/
	/*while (point1.x < WIDTH)*/
	/*{*/
		/*draw_line_bresenham(mlx, point1, point2);*/
		/*point1.x++;*/
		/*point2.x++;*/
	/*}*/
	/*put_rect(fdf, mlx);*/
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	return 1;
}
