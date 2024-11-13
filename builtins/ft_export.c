/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:02:51 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/12 23:03:31 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	env_modify(t_env **env, char *name, char *value)
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

static void	export_modify(t_env *env, char *line, char *name, int sign)
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
			env_modify(&g_data.env_list, name, tmp);
			free(value);
			return ;
		}
		else if (sign == 1)
			env_modify(&g_data.env_list, name, value);
	}
	return ;
}

static int	export_to_env(char *line, int sign)
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

static int	check_export(char *str)
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

int ft_export(char **cmd)
{
	int	status;
    int y;

	status = 0;
    y = 0;
    while(cmd[++y])
    {
        if (!check_export(cmd[y]))
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", cmd[y]);
			status = 1;
		}
        else
        {
			if (status == 1)
				export_to_env(cmd[y], check_export(cmd[y]));
			else
				status = export_to_env(cmd[y], check_export(cmd[y]));
		}
    }
	if (!cmd[1])
		print_exported_vars();
	return status;
}
