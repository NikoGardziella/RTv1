/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:00:07 by ngardzie          #+#    #+#             */
/*   Updated: 2022/09/22 11:00:09 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

double	zero_to_255(double number)
{
	if (number > 255)
		return (255);
	else if (number < 0)
		return (0);
	else
		return (number);
}

t_ray	calculate_light(t_ray ray, t_vector lightPos)
{
	t_ray	light_ray;

	light_ray.origin = lightPos;
	light_ray.dir = v_normalize(v_sub(ray.end, lightPos));
	return (light_ray);
}

void	free_arr(char **line_arr)
{
	int	i;

	i = 0;
	while (line_arr[i])
	{
		free (line_arr[i]);
		i++;
	}
	free (line_arr);
}

void	shutdown(SDL_Renderer *renderer, SDL_Window
*window, t_scene *scene, char *message)
{
	if (scene->obj != NULL)
		free(scene->obj);
	if (scene != NULL)
		free(scene);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	ft_putstr(message);
	exit(0);
}

int	ft_fail_and_free(char *message, t_scene *scene)
{
	if (scene->obj != NULL)
		free(scene->obj);
	if (scene != NULL)
		free(scene);
	ft_putendl(message);
	exit(0);
}
