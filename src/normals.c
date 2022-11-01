/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:20:39 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/11 14:20:41 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

double	ft_sqr(double nb)
{
	return (nb * nb);
}

t_vector	sphere_n(t_ray ray, double t, t_object object)
{
	t_vector	normal;
	t_vector	hit_position;

	hit_position = calculate_hitpoint(ray, t);
	normal = v_normalize(v_sub(hit_position, object.pos));
	return (normal);
}

t_vector	cylinder_n(t_ray ray, double t, t_object cylinder)
{
	t_vector	normal;
	t_vector	hit_position;
	double		a;

	cylinder.dir = v_normalize(cylinder.dir);
	a = v_dot(ray.dir, cylinder.dir) * t
		+ v_dot(v_sub(ray.origin, cylinder.pos), cylinder.dir);
	hit_position = calculate_hitpoint(ray, t);
	normal = v_normalize(v_sub(v_sub(hit_position, cylinder.pos),
				v_scale(cylinder.dir, a)));
	return (normal);
}

t_vector	cone_n(t_ray ray, double t, t_object cone)
{
	t_vector	hit_point;
	t_vector	normal;
	t_vector	vect;
	double		dotproduct;

	cone.dir = v_normalize(cone.dir);
	hit_point = calculate_hitpoint(ray, t);
	vect = v_normalize(v_sub(hit_point, cone.pos));
	dotproduct = (double)fabs(acos(v_dot(vect, cone.dir)));
	dotproduct = (double)v_magnitude(v_sub(hit_point, cone.pos))
		/ cos(dotproduct);
	normal = v_add(cone.dir, v_scale(cone.dir, dotproduct));
	normal = v_normalize(v_sub(hit_point, normal));
	return (normal);
}

void	object_normal(t_scene *scene, t_ray ray)
{
	int			i;
	t_vector	n;

	i = 0;
	while (i < scene->obj_count)
	{
		ray.end = calculate_hitpoint(ray, scene->obj[i].t);
		scene->obj[i].lightray = calculate_light(ray, scene->light);
		if (scene->obj[i].shape == 1)
			n = v_scale(sphere_n(ray, scene->obj[i].t, scene->obj[i]), -1);
		else if (scene->obj[i].shape == 2)
			n = v_scale(cone_n(ray, scene->obj[i].t, scene->obj[i]), -1);
		else if (scene->obj[i].shape == 3)
			n = v_scale(cylinder_n(ray, scene->obj[i].t, scene->obj[i]), -1);
		else
			n = scene->obj[i].dir;
		scene->obj[i].light = v_dot(n, scene->obj[i].lightray.dir);
		i++;
	}
}
