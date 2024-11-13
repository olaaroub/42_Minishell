/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:08:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/13 00:22:06 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int len_until_pipe(t_tokens *temp)
{
    t_tokens *tmp;
    int i = 0;
    int j;

    tmp = temp;
    while(tmp && tmp->type != PIPE)
    {
        if(tmp->word_after_exp && tmp->word_after_exp[1])
        {
            j = 0;
            while(tmp->word_after_exp[j])
            {
                j++;
                i++;
            }
        }
        else
            i++;
        tmp = tmp->next;
    }
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
