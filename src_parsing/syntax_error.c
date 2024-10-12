/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:03:36 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/27 13:31:54 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	syntax_error(void)
{
	t_tokens	*tmp;
	t_tokens	*next;

	tmp = g_data.token_list;
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
