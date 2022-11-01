/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:52 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/17 14:05:53 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

int	calculate_shadow(t_scene *scene, t_ray lightRay, double shadow)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->obj[i].shape == 1)
			scene->obj[i].shadow = sphere_intersect
				(lightRay, scene->obj[i].r, scene->obj[i]);
		else if (scene->obj[i].shape == 2)
			scene->obj[i].shadow = cone_intersect
				(lightRay, scene->obj[i].r, scene->obj[i]);
		else if (scene->obj[i].shape == 3)
			scene->obj[i].shadow = cylinder_intersect
				(lightRay, scene->obj[i].r, scene->obj[i]);
		else if (scene->obj[i].shape == 4)
			scene->obj[i].shadow = plane_intersect
				(lightRay, scene->obj[i]);
		if (scene->obj[i].shadow < shadow && scene->obj[i].shadow > 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_shadow(t_scene *scene, t_object object, t_ray lightRay)
{
	int		i;
	double	shadow;

	i = 0;
	shadow = 0;
	if (object.shape == 1)
		shadow = sphere_intersect(lightRay, object.r, object);
	else if (object.shape == 2)
		shadow = cone_intersect(lightRay, object.r, object);
	else if (object.shape == 3)
		shadow = cylinder_intersect(lightRay, object.r, object);
	else if (object.shape == 4)
		shadow = plane_intersect(lightRay, object);
	if (!calculate_shadow(scene, lightRay, shadow))
		return (0);
	return (1);
}

void	object_t(t_scene *s, t_ray ray)
{
	int	i;

	i = 0;
	while (i < s->obj_count)
	{
		if (s->obj[i].shape == 1)
			s->obj[i].t = (sphere_intersect(ray, s->obj[i].r, s->obj[i]));
		else if (s->obj[i].shape == 2)
			s->obj[i].t = cone_intersect(ray, s->obj[i].r, s->obj[i]);
		else if (s->obj[i].shape == 3)
			s->obj[i].t = cylinder_intersect(ray, s->obj[i].r, s->obj[i]);
		else if (s->obj[i].shape == 4)
			s->obj[i].t = plane_intersect(ray, s->obj[i]);
		else
			s->obj[i].t = 0;
		i++;
	}
}

int	get_closest(t_scene *scene)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < scene->obj_count)
	{
		if (scene->obj[i].t < scene->obj[res].t && scene->obj[i].t != 0)
			res = i;
		else if (scene->obj[res].t == 0 && scene->obj[i].t != 0)
			res = i;
		i++;
	}
	return (res);
}

double	calculate_t(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = (b * b) - 4.0f * a * c;
	if (discriminant < 0)
		return (0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (t2);
	else
		return (0);
}
