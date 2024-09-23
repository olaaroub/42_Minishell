/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:03:36 by olaaroub          #+#    #+#             */
/*   Updated: 2024/08/29 23:59:48 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	syntax_error(void)
{
	t_tockens	*tmp;
	t_tockens	*next;

	tmp = g_data.tocken_list;
	if(!tmp)
		return 0;
	if (tmp->type == PIPE)
		return (printf("minishell: syntax error near unexpected token '|'\n"),
			-1);
	while (tmp)
	{
		next = tmp->next;
		if (next == NULL)
			if (tmp->type == PIPE)
				return (printf("minishell: syntax error near unexpected token '|'\n"),
					-1);
		if (tmp->type != WORD && tmp->type != PIPE && !next)
		{
			printf("minishell: syntax error near ");
			printf("unexpected token 'newline'\n");
			return (-1);
		}
		else if ((tmp->type != WORD && tmp->type != PIPE && next->type != WORD)
			|| (tmp->type == PIPE && next->type == PIPE))
		{
			printf("minishell: syntax error near unexpected token '%s'\n",
				next->word);
			return (-1);
		}
		tmp = next;
	}
	return (0);
}
