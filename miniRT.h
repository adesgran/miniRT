/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:34:52 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 19:58:32 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <mlx.h>
# include <math.h>

# define KEY_UP 119
# define KEY_LEFT 100
# define KEY_DOWN 115
# define KEY_RIGHT 97
# define KEY_ESCAPE 65307
# define KEY_ZOOM_IN 65451
# define KEY_ZOOM_OUT 65453
# define KEY_ROT_LEFT 113
# define KEY_ROT_RIGHT 101
# define W_HEIGHT 1000
# define W_WIDTH 1000
# define SPHERE 101

typedef struct s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;
}	t_vars;

typedef struct s_coord {
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_line {
	t_coord	pos;
	t_coord	dir;
}	t_line;

typedef struct s_shapes {
	void			*content;
	int				type;
	struct s_shapes	*next;
}	t_shapes;

typedef struct s_sphere {
	t_coord			pos;
	double			r;
	unsigned int	color;
}	t_sphere;

typedef struct s_pixel {
	double			dist;
	unsigned int	color;
}	t_pixel;

typedef struct s_light {
	t_coord			pos;
	double			color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera {
	t_coord	pos;
	t_coord	dir;
	double	fov;
}	t_camera;

typedef struct s_env {
	t_camera		*camera;
	t_light			*light;
	t_shapes		*shapes;
	unsigned int	ambiant_light;
}	t_env;

void			put_pixel(t_data *img, int x, int y, ...);
t_vars			*init_vars(void);

//t_shapes Utils
t_shapes		*shapes_init(void *content, int type);
void			shapes_free(t_shapes *shapes);
void			shapes_add(t_shapes *shapes, void *content, int type);

//t_light Utils
void	light_free(t_light *light);

//Geometry Utils
double			get_angle(t_line *v1, t_line *v2);
void			matrix_rotation(t_coord *p, double ax, double ay);

//Colors Utils
unsigned int	color_addition(unsigned int c1, unsigned int c2);
unsigned int	color_product(unsigned int c1, unsigned int c2, double alpha);
unsigned int	color_ratio(unsigned int color, double ratio);

//Env Utils
void	env_free(t_env *env);

t_env	*get_env(void);
#endif
