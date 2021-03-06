#include "fdf.h"
#include <stdlib.h>
#include <time.h>

void check_keys(t_fdf *fdf, t_keys *keys)
{
	if (!keys->shift && keys->plus)
	{
		fdf->map->square_size += 1;
		fdf->camera->offset_y -= fdf->map->height_map / 3;
	}
	if (!keys->shift && keys->minus)
		if (fdf->map->square_size >= 2)
		{
			fdf->map->square_size -= 1;
			fdf->camera->offset_y += fdf->map->height_map / 3;
		}
	if (keys->a || keys->left)
			fdf->camera->offset_x -= 3;
	if (keys->d || keys->right)
			fdf->camera->offset_x += 3;
	if (keys->w || keys->up)
			fdf->camera->offset_y -= 3;
	if (keys->s || keys->down)
			fdf->camera->offset_y += 3;
	if (keys->alpha_plus || fdf->keys->j)
		fdf->camera->alpha += 0.05;
	if (keys->alpha_minus || fdf->keys->k)
		fdf->camera->alpha -= 0.05;
	if (keys->beta_plus || (!fdf->keys->shift && fdf->keys->l))
		fdf->camera->beta += 0.05;
	if (keys->beta_minus || (!fdf->keys->shift && fdf->keys->h))
		fdf->camera->beta -= 0.05;
	if (keys->gamma_plus || (fdf->keys->shift && fdf->keys->l))
		fdf->camera->gamma += 0.05;
	if (keys->gamma_minus || (fdf->keys->shift && fdf->keys->h))
		fdf->camera->gamma -= 0.05;
	if (keys->rotate)
	{
		/*printf("%f, %d\n", fdf->camera->speed_rotate, fdf->camera->acceleration);*/
		if (fdf->camera->speed_rotate < 1.0 && fdf->camera->acceleration == 1)
			fdf->camera->speed_rotate += 0.002;
		if (fdf->camera->speed_rotate > 1 || fdf->camera->acceleration == -1)
		{
			fdf->camera->acceleration = -1;
			fdf->camera->speed_rotate -= 0.001;
			if (fdf->camera->speed_rotate < -1)
				fdf->camera->acceleration = 1;
		}
		fdf->camera->alpha += 0.04 * fdf->camera->speed_rotate;
		fdf->camera->beta += 0.04 * fdf->camera->speed_rotate;
		fdf->camera->gamma += 0.04 * fdf->camera->speed_rotate;
	}
	else if (keys->gamma_rotate)
		fdf->camera->gamma += 0.01;
	//инвертировать цвет
	if (!keys->option && !keys->shift && !keys->ctrl && keys->invert_color)
	{
		t_point **points;
		points = fdf->points;
		for (int i = 0; i < fdf->map->height_map; i++)
		{
			for (int j = 0; j < fdf->map->width_map; j++)
			{
				if (points[i][j].color != 0xFFFFFF)
					points[i][j].color = 0xFFFFFF - points[i][j].color;
			}
		}
		keys->invert_color = 0;
	}
	//вся карта рандомного цвета
	if (keys->shift && keys->invert_color)
	{
		t_point **points;
		points = fdf->points;
		srand(time(0));
		int new_color  = rand() % 0xFFFFFF;
		for (int i = 0; i < fdf->map->height_map; i++)
		{
			for (int j = 0; j < fdf->map->width_map; j++)
					points[i][j].color = new_color;
		}
		keys->invert_color = 0;
	}
	//рандомный цвет радуга- шум телека
	if (keys->ctrl && keys->invert_color)
	{
		t_point **points;
		points = fdf->points;
		srand(time(0));
		for (int i = 0; i < fdf->map->height_map; i++)
		{
			for (int j = 0; j < fdf->map->width_map; j++)
				if (points[i][j].color != 0xFFFFFF)
					points[i][j].color = rand() % 0xFFFFFF;
		}
		keys->invert_color = 0;
	}
	// увеличить координату z
	if (keys->shift && keys->plus)
	{
		if (fdf->camera->z_coefficient < 10)
			fdf->camera->z_coefficient += 0.05;
	}
	// уменьшить координату z
	if (keys->shift && keys->minus)
	{
		if (fdf->camera->z_coefficient > -0.5)
			fdf->camera->z_coefficient -= 0.05;
	}
	// вернуть первоначальные цвета
	if ((keys->is_isometric) || (keys->option && keys->invert_color))
	{
		for (int i = 0; i < fdf->map->height_map; i++)
		{
			for (int j = 0; j < fdf->map->width_map; j++)
			{
				if (fdf->points[i][j].color != 0xFFFFFF)
					fdf->points[i][j].color = fdf->points[i][j].first_color;
			}
		}
		keys->invert_color = 0;
	}
	//обработка зума мышкой
	static int time = 0;
	if (keys->mouse_zoom == 1 && time != 5)
	{
		fdf->map->square_size += 1;
		fdf->camera->offset_y -= fdf->map->height_map / 3;
		time++;
		if (time == 5)
		{
			time = 0;
			keys->mouse_zoom = 0;
		}
	}
	if (keys->mouse_zoom == -1 && time != 5)
	{
		if (fdf->map->square_size >= 2)
		{
			fdf->map->square_size -= 1;
			fdf->camera->offset_y += fdf->map->height_map / 3;
		}
		time++;
		if (time == 5)
		{
			time = 0;
			keys->mouse_zoom = 0;
		}
	}
}

