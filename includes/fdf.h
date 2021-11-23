#ifndef FDF_H
#define FDF_H 
#include <stdio.h> //for size_t

#define ERROR -1
#define WIDTH 800
#define HEIGHT 600
#define W_RECT 20

typedef struct mlx
{
	void *ptr;
	void *win;
	void *img;
	char *addr;
	int bpp;
	int size_line;
	int endian;
}	t_mlx;

typedef struct map
{
	char **map;
}	t_map;

typedef struct keys
{
	int esc;
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
	int up;
	int down;
}	t_keys;

typedef struct fdf
{
	t_mlx *mlx;
	t_map *map;
	t_keys *keys;
	int pos_x;
	int pos_y;
}	t_fdf;

char	**ft_split(char const *s, char c);
int			ft_strlen(char *s);
char **malloc_bzero(size_t count);
int error(char *s);
int size(char **splitted);
void free_split(char **map);
int cross_hook(t_map *map);
int key_down_hook(int key, t_keys *keys);
int key_up_hook(int key, t_keys *keys);
//int draw(t_fdf *fdf);
int draw(t_fdf *fdf, t_mlx *mlx);
//void	pixel_put(t_fdf *fdf, int x, int y, int color);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
int		rgb_make(int t, int r, int g, int b);

#endif
