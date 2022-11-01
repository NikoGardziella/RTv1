/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vectors1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:29:14 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/12 09:29:16 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

t_vector	v_sub(t_vector v0, t_vector v1)
{
	v0.x = v0.x - v1.x;
	v0.y = v0.y - v1.y;
	v0.z = v0.z - v1.z;
	return (v0);
}

t_vector	v_add(t_vector v0, t_vector v1)
{
	v0.x = v0.x + v1.x;
	v0.y = v0.y + v1.y;
	v0.z = v0.z + v1.z;
	return (v0);
}

double	v_dot(t_vector v0, t_vector v1)
{
	return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

t_vector	vector_negative(t_vector vector)
{
	vector.x *= -1;
	vector.y *= -1;
	vector.z *= -1;
	return (vector);
}

t_vector	vector_cross_product(t_vector v0, t_vector v1)
{
	t_vector	v2;

	v2.x = v0.y * v1.z - v0.z * v1.y;
	v2.y = v0.z * v1.x - v0.x * v1.z;
	v2.z = v0.x * v1.y - v0.y * v1.x;
	return (v2);
}
