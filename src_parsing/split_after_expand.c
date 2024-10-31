/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:00:42 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/31 18:11:46 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int words_len(char **words)
{
    int i;

    i = 0;
    while(words[i])
        i++;
    return i;
}

void    split_tokens(void)
{
    t_tokens   *tmp;

    tmp = g_data.token_list;
    while(tmp)
    {
        tmp->word_after_exp = split_mgem7a(tmp->word);
        tmp = tmp->next;
    }
}