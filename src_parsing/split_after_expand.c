/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:00:42 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/16 15:37:50 by olaaroub         ###   ########.fr       */
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

// static void    refill_tokens(void)
// {
//     t_tockens   *tmp;
//     int         i;

//     tmp = g_data.tocken_list;
//     g_data.tocken_list = NULL;
//     while(tmp)
//     {
//         i = 0;
//         while(tmp->word_after_exp && tmp->word_after_exp[i])
//         {
//             g_data.tocken_list = ft_add_tocken(tmp->word_after_exp[i], tmp->type, tmp->ambiguous, tmp->dollar);
//             i++;
//             if(!tmp->word_after_exp[i] && tmp->dollar)
//                 g_data.tocken_list = ft_add_tocken(NULL, tmp->type, tmp->ambiguous, tmp->dollar);

//         }
//         tmp = tmp->next;
//     }
// }

void    split_tokens(void)
{
    t_tockens   *tmp;

    tmp = g_data.tocken_list;
    while(tmp)
    {
        tmp->word_after_exp = split_mgem7a(tmp->word);
        tmp = tmp->next;
    }
    // refill_tokens();
}