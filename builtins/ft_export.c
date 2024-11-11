/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:02:51 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/17 22:44:29 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isset(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_strlen_eq(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	return (i);
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
void	env_modify(t_env **env, char *name, char *value)
{
	t_env	*temp;

	temp = *env;
	char *tmp;

	while(temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			free(temp->value);
			temp->value = value;
			free(temp->line);
			tmp = ft_strjoin(name, "=");
			temp->line = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		temp = temp->next;
	}
}

void	export_modify(t_env *env, char *line, char *name, int sign)
{
	char	*value;
	char	*tmp;

	if (sign == 3)
		return ;
	else
	{
		value = ft_substr(line, ft_strlen_eq(line, '=') + 1, ft_strlen(line));
		if (sign == 2)
		{
			tmp = ft_strjoin(env->value, value);
			// free(value);
			env_modify(&g_data.env_list, name, tmp);
			free(value);
			// free(tmp);
			return ;
		}
		else if (sign == 1)
			env_modify(&g_data.env_list, name, value);
		// free(value);
	}
	return ;
}

t_env	*env_new_node(char *line, int flag)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (printf("ERROR: ENV Node malloc failed!\n"), NULL);
	if (flag == 0)
	{
		new_node->line = ft_strdup(line);
		new_node->name = ft_strdup(line);
		new_node->value = NULL;
	}
	else
	{
		len = ft_strlen(line);
		new_node->name = ft_substr(line, 0, ft_strlen_eq(line, '+'));
		new_node->value = ft_substr(line, ft_strlen_eq(line, '=') + 1, len);
		temp = ft_strjoin(new_node->name, "=");
		new_node->line = ft_strjoin(temp, new_node->value);
		free(temp);
	}
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}
t_env *env_newnode(char *line)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (printf("ERROR: ENV Node malloc failed!\n"), NULL);
	len = ft_strlen(line);
	new_node->name = ft_substr(line, 0, ft_strlen_eq(line, '='));
	new_node->value = ft_substr(line, ft_strlen_eq(line, '=') + 1, len);
	temp = ft_strjoin(new_node->name, "=");
	new_node->line = ft_strjoin(temp, new_node->value);
	free(temp);
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

int	export_to_env(char *line, int sign)
{
	t_env	*temp;
	char	*name;

	temp = g_data.env_list;
	name = get_var_name(line, sign);
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			export_modify(temp, line, name, sign);
			free(name);
			return (0);
		}
		temp = temp->next;
	}
	free(name);
	if (sign == 3)
		env_add_back(&g_data.env_list, env_new_node(line, 0));
	else if (sign == 2)
		env_add_back(&g_data.env_list, env_new_node(line, 1));
	else if (sign == 1)
		env_add_back(&g_data.env_list, env_newnode(line));
	return (0);
}

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (str[i] >= '0' && str[i] <= '9')
		|| str[i] == '=' || str[i] == '+')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isset(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (3);
	if (str[i] == '+')
	{
		if (!str[i + 1] || (str[i + 1] && str[i + 1] != '='))
			return (0);
		else
			return (2);
	}
	return (1);
}
size_t	list_size(void *lst, int s)
{
	size_t	x;
	t_env	*lst1;
	t_command	*lst2;

	x = 0;
	if (s)
		lst1 = (t_env *)lst;
	if (!s)
		lst2 = (t_command *)lst;
	while (s && lst1)
	{
		x++;
		lst1 = lst1->next;
	}
	while (!s && lst2)
	{
		x++;
		lst2 = lst2->next;
	}
	return (x);
}

t_env	*get_to_print(t_env *env, int index)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->index == index)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
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
	// long	x;
	t_env	*tmp;
	t_env	*min;

	// x = 0;
	tmp = env;
	while (tmp && tmp->index)
		tmp = tmp->next;
	min = tmp;
	// x = 0;
	tmp = env;
	while (tmp && min)
	{
		if (!tmp->index && !compare(min->name, tmp->name))
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

void	sort_env(t_env **env)
{
	int		x;
	int		y;
	t_env	*min;
	t_env	*tmp;

	x = 1;
	y = list_size(*env, 1) + 1;
	tmp = *env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	while (x < y)
	{
		min = get_min(*env);
		if (min)
			min->index = x++;
	}
}

int ft_export(char **cmd)
{
	int	status;
    int y;
	int index;
	t_env	*to_print;
	t_env	*tmp;

	status = 0;
	index = 0;
    y = 0;
    while(cmd[++y])
    {
        if (!check_export(cmd[y]))
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", cmd[y]);
			g_data.ret_value = 1;
		}
        else
        {
			if (status == 1)
				export_to_env(cmd[y], check_export(cmd[y]));
			else
				status = export_to_env(cmd[y], check_export(cmd[y]));
		}
    }
	y = list_size(g_data.env_list, 1);
	tmp = g_data.env_list;
	while(!cmd[1] && ++index <= y)
	{
		sort_env(&g_data.env_list);
		// ft_printf(STDOUT_FILENO, "Debug\n");
		to_print = get_to_print(tmp, index);
		if (to_print && to_print->value)
			ft_printf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", to_print->name, to_print->value);
		else if (to_print)
			ft_printf(STDOUT_FILENO, "declare -x %s\n", to_print->name);
		tmp = tmp->next;
		// index++;
	}
	return (status);
}
