/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:23:57 by ngardzie          #+#    #+#             */
/*   Updated: 2022/08/08 12:23:58 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

t_vector	calculate_hitpoint(t_ray ray, double t)
{
	t_vector	hitpoint;

	hitpoint.x = ray.origin.x + ray.dir.x * t;
	hitpoint.y = ray.origin.y + ray.dir.y * t;
	hitpoint.z = ray.origin.z + ray.dir.z * t;
	return (hitpoint);
}

t_vector	v_normalize(t_vector v0)
{
	return (v_scale(v0, 1.0 / v_magnitude(v0)));
}

double	v_magnitude(t_vector v0)
{
	return (sqrt(v0.x * v0.x + v0.y * v0.y + v0.z * v0.z));
}

t_vector	v_scale(t_vector v0, double multiplier)
{
	v0.x = v0.x * multiplier;
	v0.y = v0.y * multiplier;
	v0.z = v0.z * multiplier;
	return (v0);
}

t_vector	v_new(double x, double y, double z)
{
	t_vector	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}
