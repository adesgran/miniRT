/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:34:14 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:29:21 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static t_env	*env_new(void)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->light = NULL;
	res->shapes = NULL;
	res->camera = NULL;
	res->ambiant_light = NULL;
	return (res);
}

static int	fill_env(char *line, t_env *env)
{
	char		**tab;
	int			ret;

	tab = split_spaces(line);
	if (!tab)
		return (1);
	if (!ft_strcmp(tab[0], "A"))
		ret = parse_ambiantlight(env, tab);
	else if (!ft_strcmp(tab[0], "L"))
		ret = parse_light(env, tab);
	else if (!ft_strcmp(tab[0], "C"))
		ret = parse_camera(env, tab);
	else if (!ft_strcmp(tab[0], "sp"))
		ret = parse_sphere(env, tab);
	else if (!ft_strcmp(tab[0], "cy"))
		ret = parse_cylindre(env, tab);
	else if (!ft_strcmp(tab[0], "pl"))
		ret = parse_plan(env, tab);
	else
		ret = 1;
	return (ft_free_tabstr(tab), ret);
}

int	check_mandatory(t_env *env)
{
	if (!env->camera)
		return (parsing_error("Camera: not defined"), 1);
	else if (!env->light)
		return (parsing_error("Light: not defined"), 1);
	else if (!env->ambiant_light)
		return (parsing_error("Ambiant Light: not defined"), 1);
	return (0);
}

t_env	*parser(char *filename)
{
	int		fd;
	t_env	*res;
	char	*line;

	if (ft_strrncmp(filename, ".rt", 3))
		return (parsing_error("File is not of type .rt"), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (parsing_error("Can't open file"), NULL);
	res = env_new();
	if (!res)
		return (close(fd), NULL);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (fill_env(line, res))
			return (env_free(res), close(fd), free(line), NULL);
		free(line);
		line = ft_get_next_line(fd);
	}
	if (check_mandatory(res))
		return (env_free(res), close(fd), free(line), NULL);
	return (close(fd), free(line), res);
}
