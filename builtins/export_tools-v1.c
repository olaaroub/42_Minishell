/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools-v1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:26:39 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/19 09:01:40 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strlen_eq(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

int	compare(char *min_str, char *str)
{
	size_t	x;

	x = 0;
	if (!min_str || !str)
		return (0);
	while (str[x] && min_str[x] && str[x] == min_str[x])
	{
		if (str[x] != min_str[x])
			break ;
		x++;
	}
	if (str[x] >= min_str[x])
		return (1);
	return (0);
}

t_env	*get_min(t_env *env)
{
	t_env	*tmp;
	t_env	*min;

	tmp = env;
	while (tmp && tmp->index)
		tmp = tmp->next;
	min = tmp;
	tmp = env;
	while (tmp && min)
	{
		if (!tmp->index && !compare(min->name, tmp->name))
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

char	*get_var_name(char *line, int sign)
{
	char	*name;

	name = NULL;
	if (sign == 3)
		name = ft_strdup(line);
	else if (sign == 2)
		name = ft_substr(line, 0, ft_strlen_eq(line, '+'));
	else if (sign == 1)
		name = ft_substr(line, 0, ft_strlen_eq(line, '='));
	return (name);
}

void	print_exported_vars(void)
{
	int		index;
	int		y;
	t_env	*to_print;
	t_env	*tmp;

	y = list_size(g_data.env_list, 1);
	tmp = g_data.env_list;
	index = 0;
	while (++index <= y)
	{
		sort_env(&g_data.env_list);
		to_print = get_to_print(tmp, index);
		if (to_print && to_print->value)
			ft_printf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", \
			to_print->name, to_print->value);
		else if (to_print)
			ft_printf(STDOUT_FILENO, "declare -x %s\n", to_print->name);
		tmp = tmp->next;
	}
}
