/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:21:06 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/11 14:21:07 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

double	sphere_intersect(t_ray ray, double radius, t_object sphere)
{
	t_variables	var;

	var.w = v_sub(ray.origin, sphere.pos);
	var.a = v_dot(ray.dir, ray.dir);
	var.b = 2 * v_dot(ray.dir, var.w);
	var.c = v_dot(var.w, var.w) - (radius * radius);
	sphere.t = calculate_t(var.a, var.b, var.c);
	return (sphere.t);
}

double	cone_intersect(t_ray ray, double radius, t_object cone)
{
	t_variables	var;

	cone.dir = v_normalize(cone.dir);
	cone.dir = v_add(cone.dir, cone.pos);
	var.w = v_sub(ray.origin, cone.pos);
	var.h = v_sub(cone.dir, cone.pos);
	radius = ft_sqr(radius) / ft_sqr(v_magnitude(var.h));
	var.wh = v_dot(var.w, v_normalize(var.h));
	var.vh = v_dot(ray.dir, v_normalize(var.h));
	var.a = v_dot(ray.dir, ray.dir) - radius
		* ft_sqr(var.vh) - ft_sqr(var.vh);
	var.b = 2 * (v_dot(ray.dir, var.w) - (radius
				* (var.vh * var.wh)) - (var.vh * var.wh));
	var.c = v_dot(var.w, var.w) - (radius
			* ft_sqr(var.wh)) - ft_sqr(var.wh);
	cone.t = calculate_t(var.a, var.b, var.c);
	return (cone.t);
}

double	cylinder_intersect(t_ray ray, double radius, t_object cylinder)
{
	t_variables	var;

	cylinder.dir = (v_add(cylinder.dir, cylinder.pos));
	var.w = v_sub(ray.origin, cylinder.pos);
	var.h = v_sub(cylinder.dir, cylinder.pos);
	var.wh = v_dot(var.w, v_normalize(var.h));
	var.vh = v_dot(ray.dir, v_normalize(var.h));
	var.a = v_dot(ray.dir, ray.dir) - ft_sqr(var.vh);
	var.b = 2 * (v_dot(ray.dir, var.w) - (var.vh * var.wh));
	var.c = v_dot(var.w, var.w) - ft_sqr(var.wh) - ft_sqr(radius);
	cylinder.t = calculate_t(var.a, var.b, var.c);
	return (cylinder.t);
}

double	plane_intersect(t_ray ray, t_object plane)
{
	t_variables	var;

	var.a = v_dot(v_sub(ray.origin, plane.pos), plane.dir);
	var.b = v_dot(ray.dir, plane.dir);
	plane.t = -var.a / var.b;
	if (plane.t < 0)
		return (0);
	return (plane.t);
}
