/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:34:14 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/02 15:28:38 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	fill_env(char *line, t_env *env)
{
	static int	al_set;
	char		**tab;

	if (!al_set)
		al_set = 0;
	tab = split_spaces(line);
	if (!tab)
		return (1);
	if (!ft_strcmp(tab[0], "A"))
	{
		al_set = 1;
		return (parse_ambiantlight(env, tab));
	}
	else if (!ft_strcmp(tab[0], "L"))
		return (parse_light(env, tab));
	else if (!ft_strcmp(tab[0], "C"))
		return (parse_camera(env, tab));
	else if (!ft_strcmp(tab[0], "sp"))
		return (parse_sphere(env, tab));
	else if (!ft_strcmp(tab[0], "cy"))
		return (parse_cylindre(env, tab));
	else if (!ft_strcmp(tab[0], "pl"))
		return (parse_plan(env, tab));
	ft_free_tabstr(tab);
	return (1);
}

t_env	*parser(char *filename)
{
	int		fd;
	t_env	*res;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (parsing_error("Can't read file"), NULL);
	res = malloc(sizeof(t_env));
	if (!res)
		return (close(fd), res);
	res->light = NULL;
	res->shapes = NULL;
	res->camera = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		printf("Parsing..\n");
		if (fill_env(line, res))
			return (env_free(res), close(fd), free(line) \
					, parsing_error("Please send a valid .rt file"), NULL);
		free(line);
		line = ft_get_next_line(fd);
	}
	if (!res->light || !res->camera)
		return (env_free(res), close(fd), free(line) \
			, parsing_error("Please send a valid .rt file"), NULL);
	return (close(fd), res);
}
