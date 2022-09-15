/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:34:52 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 13:42:06 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
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
# define CYLINDRE 102
# define PLAN 103
# define KD 100
# define KS 100
# define KA 1

typedef struct s_color {
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	double			i;
}	t_color;

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
	double			(*ft_finder)(struct s_shapes *, t_line *);
	void			(*ft_norm)(struct s_shapes *, t_line *, double);
	t_line			norm;
	t_color			color;
	struct s_shapes	*next;
}	t_shapes;

typedef struct s_sphere {
	t_coord			pos;
	double			r;
	t_color			color;
}	t_sphere;

typedef struct s_cylindre {
	t_coord			pos;
	t_coord			dir;
	double			r;
	double			h;
	t_color			color;
}	t_cylindre;

typedef struct s_plan {
	t_coord			pos;
	t_coord			dir;
	t_color			color;
	double			r;
}	t_plan;

typedef struct s_light {
	t_coord			pos;
	t_color			color;
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
	t_color			*ambiant_light;
}	t_env;

void			put_pixel(t_data *img, int x, int y, ...);
t_vars			*init_vars(void);

//Ray Caster
int	minirt(t_env *env, unsigned int tab_color[W_HEIGHT][W_WIDTH]);

//Cylinder Utils
double			get_t(t_shapes *shape, t_line *line);
double			check_collision(t_cylindre *cy, t_line *sline, t_line *line, double t);

//Shapes Finder
double			sphere_finder(t_shapes *shape, t_line *line);
double			cylinder_finder(t_shapes *shape, t_line *line);
double			plan_finder(t_shapes *shape, t_line *line);
unsigned int	shapes_finder(t_env *env, t_shapes *shapes, t_line *line);
void			plan_norm(t_shapes *shape, t_line *line, double t);
void			cylinder_norm(t_shapes *shape, t_line *line, double t);
void			sphere_norm(t_shapes *shape, t_line *line, double t);

//Colors
unsigned int	get_shape_color(t_env *env, t_line *line, t_shapes *shape);

//t_shapes Utils
t_shapes	*shapes_new(void *content, t_color *color,
	double (*ft_finder)(t_shapes *, t_line *),
	void (*ft_norm)(struct s_shapes *, t_line *, double));
void			shapes_add(t_env *env, t_shapes *new);
void			shapes_free(t_shapes *shapes);

//t_light Utils
void			light_free(t_light *light);

//Geometry Utils
double			get_angle(t_coord *v1, t_coord *v2);
double			get_dist(t_coord *a, t_coord *b);
double			max(double a, double b);
void			norm_vector(t_coord *v);
void			vector_product(t_coord *a, t_coord *b, t_coord *res);
void			coord_sub(t_coord *a, t_coord *b, t_coord *c);
void			coord_cpy(t_coord *a, t_coord *b);
t_coord			*get_vector_perp(t_coord *a, t_coord *b);
unsigned int	min(unsigned int x, unsigned int y);

//Matrix Rotation
void			matrix_rotation(t_coord *p, double ax, double ay);

//Colors Utils
void			color_addition(t_color *c1, t_color *c2, t_color *res);
void			color_product(t_color *c1, t_color *c2, t_color *res);
void			color_ratio(t_color *c1, double ratio, t_color *res);
unsigned int	color_to_ui(t_color color);
void			color_cpy(t_color *c1, t_color *c2);
void			color_add(t_color *res, t_color *to_add);
void			color_sub(t_color *c1, t_color *c2, t_color *res);

//Env Utils
void			env_free(t_env *env);

t_env			*get_env(void);

//Parsing
char			**split_spaces(char *str);
double			atod(char *str, int *error);
t_env			*parser(char *filename);
void			parsing_error(char *msg);

int				parse_ambiantlight(t_env *env, char **tab);
int				parse_light(t_env *env, char **tab);
int				parse_camera(t_env *env, char **tab);
int				parse_sphere(t_env *env, char **tab);
int				parse_cylindre(t_env *env, char **tab);
int				parse_plan(t_env *env, char **tab);

// Read Color
int				read_color(char *str, t_color *color);

// Read Coord
int				check_dir(t_coord *dir);
int				read_coord(char *str, t_coord *coord);

#endif
