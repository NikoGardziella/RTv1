/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:00:59 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/12 10:01:01 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

int	add_color(float light, float shadow, t_object object)
{
	int		ret;
	t_color	color;

	color.r = zero_to_255(object.color.r * (light * shadow));
	color.b = zero_to_255(object.color.b * (light * shadow));
	color.g = zero_to_255(object.color.g * (light * shadow));
	color.a = zero_to_255(object.color.a * (light * shadow));
	ret = ((color.a << 24) | (color.b << 16) | (color.g << 8) | color.r);
	return (ret);
}

void	put_pixel(void *data, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return ;
	*(int *)(data + (x + y * SCREEN_WIDTH) * 4) = color;
}
