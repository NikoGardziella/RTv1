/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:43:26 by ngardzie          #+#    #+#             */
/*   Updated: 2022/06/22 11:43:29 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 640

# include "../SDL2-2.0.22/include/SDL.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include  "../includes/rtv1.h"
# include <stdio.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_variables
{
	t_vector	w;
	t_vector	h;
	double		vh;
	double		wh;
	double		m;
	double		a;
	double		b;
	double		c;
}	t_variables;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	end;
	t_vector	dir;
	t_vector	normal;
	t_vector	rv;
}	t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_object
{
	t_ray		ray;
	double		t;
	int			shape;
	t_vector	pos;
	t_vector	dir;
	double		r;
	t_color		color;
	int			*id;
	double		shadow;
	double		inshadow;	
	double		light;
	t_ray		lightray;
}	t_object;

typedef struct s_cam
{
	t_vector	origin;
	t_vector	direction;
	t_vector	forward;
	t_vector	up;
	t_vector	left;
}	t_cam;

typedef struct s_scene
{
	void		*data;
	t_cam		cam;
	t_vector	light;
	int			obj_count;
	t_object	*obj;
}	t_scene;

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Texture		*buffer;
}	t_sdl;

void		object_t(t_scene *s, t_ray ray);
int			get_closest(t_scene *scene);
int			ft_fail_and_free(char *message, t_scene *scene);
void		shutdown(SDL_Renderer *renderer, SDL_Window *window,
				t_scene *scene, char *message);
void		object_normal(t_scene *scene, t_ray ray);
int			add_color(float light, float shadow, t_object object);
void		put_pixel(void *data, int x, int y, int color);
void		check_numbers(char **line_arr, int len, t_scene *scene);
void		parse_obj(t_scene *scene, char **line_arr, int count);
void		parse_cam(t_scene *scene, char **line_arr);
void		parse_light(t_scene *scene, char **line_arr);
double		calculate_t(double a, double b, double c);
int			check_shadow(t_scene *scene, t_object object, t_ray lightRay);
void		draw(t_scene *scene);
t_ray		calculate_light(t_ray ray, t_vector lightPos);
t_vector	sphere_n(t_ray ray, double t, t_object object);
t_vector	cylinder_n(t_ray ray, double t, t_object object);
t_vector	cone_n(t_ray ray, double t, t_object cone);
t_vector	plane_n(t_object object);
double		sphere_intersect1(t_ray ray, double radius, t_ray sphere);
void		free_arr(char **line_arr);
void		parser(t_scene *scene, char *file);
double		plane_intersect(t_ray ray, t_object plane);
double		cone_intersect(t_ray ray, double radius, t_object cylinder);
double		cylinder_intersect(t_ray ray, double radius, t_object cylinder);
double		zero_to_255(double number);
double		ft_sqr(double nb);
t_color		gamma_correction(t_color color, double exposure, double gamma);
double		zero_to_one(double number);
t_ray		cam_make_ray(t_cam cam);
t_vector	calculate_hitpoint(t_ray ray, double t);
int			check_intersection(t_object object, t_vector normal);
double		sphere_intersect(t_ray ray, double radius, t_object sphere);
void		key_hook(t_sdl sdl, t_scene *scene);
t_vector	v_copy(t_vector v0);
t_vector	v_normalize(t_vector v0);
double		v_magnitude(t_vector v0);
t_vector	v_scale(t_vector v0, double multiplier);
t_vector	v_new(double x, double y, double z);
t_vector	v_sub(t_vector v0, t_vector v1);
t_vector	v_add(t_vector v0, t_vector v1);
double		v_dot(t_vector v0, t_vector v1);
t_vector	vector_cross_product(t_vector v0, t_vector v1);
t_vector	vector_negative(t_vector vector);
int			v_comapre(t_vector v1, t_vector v2);

#endif
