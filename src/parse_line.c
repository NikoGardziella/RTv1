/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:54:35 by ngardzie          #+#    #+#             */
/*   Updated: 2022/10/12 08:54:37 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

void	parse_light(t_scene *scene, char **line_arr)
{
	int	len;

	len = 0;
	while (line_arr[len] != 0)
		len++;
	if (len != 4)
		ft_fail_and_free("input error: wrong value for light", scene);
	check_numbers(line_arr, len, scene);
	scene->light.x = (double)ft_atoi(line_arr[1]);
	scene->light.y = (double)ft_atoi(line_arr[2]);
	scene->light.z = (double)ft_atoi(line_arr[3]);
}

void	parse_cam(t_scene *scene, char **line_arr)
{
	int	len;

	len = 0;
	while (line_arr[len] != 0)
		len++;
	if (len != 7)
		ft_fail_and_free("input error: wrong value for cam", scene);
	check_numbers(line_arr, len, scene);
	scene->cam.origin.x = (double)ft_atoi(line_arr[1]);
	scene->cam.origin.y = (double)ft_atoi(line_arr[2]);
	scene->cam.origin.z = (double)ft_atoi(line_arr[3]);
	scene->cam.direction.x = (double)ft_atoi(line_arr[4]);
	scene->cam.direction.y = (double)ft_atoi(line_arr[5]);
	scene->cam.direction.z = (double)ft_atoi(line_arr[6]);
}

void	parse_obj(t_scene *scene, char **line_arr, int count)
{
	int	len;

	len = 0;
	while (line_arr[len] != 0)
		len++;
	if (len != 12)
		ft_fail_and_free("input error: wrong value for object", scene);
	check_numbers(line_arr, len, scene);
	scene->obj[count].pos.x = (double)ft_atoi(line_arr[1]);
	scene->obj[count].pos.y = (double)ft_atoi(line_arr[2]);
	scene->obj[count].pos.z = (double)ft_atoi(line_arr[3]);
	scene->obj[count].dir.x = (double)ft_atoi(line_arr[4]);
	scene->obj[count].dir.y = (double)ft_atoi(line_arr[5]);
	scene->obj[count].dir.z = (double)ft_atoi(line_arr[6]);
	scene->obj[count].color.r = zero_to_255(ft_atoi(line_arr[7]));
	scene->obj[count].color.g = zero_to_255(ft_atoi(line_arr[8]));
	scene->obj[count].color.b = zero_to_255(ft_atoi(line_arr[9]));
	scene->obj[count].color.a = zero_to_255(ft_atoi(line_arr[10]));
	scene->obj[count].r = (double)ft_atoi(line_arr[11]);
}
