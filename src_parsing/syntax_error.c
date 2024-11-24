/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:03:36 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/14 12:06:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(int flag, char *to_print)
{
	if (1 == flag)
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
	else
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n",
			to_print);
}

int	syntax_error(void)
{
	t_tokens	*tmp;
	t_tokens	*next;

	tmp = g_data.token_list;
	if (!tmp)
		return (0);
	if (tmp->type == PIPE)
		return (print_error(1, NULL), -1);
	while (tmp)
	{
		next = tmp->next;
		if (next == NULL)
			if (tmp->type == PIPE)
				return (ft_printf(2,
						"minishell: syntax error near unexpected token '|'\n"),
					-1);
		if (tmp->type != WORD && tmp->type != PIPE && !next)
			return (print_error(2, "newline"), -1);
		else if ((tmp->type != WORD && tmp->type != PIPE && next->type != WORD)
			|| (tmp->type == PIPE && next->type == PIPE))
			return (print_error(2, next->word), -1);
		tmp = next;
	}
	return (0);
}
