/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:23:51 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/02 17:06:33 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int get_len(char *exp)
{
    t_env   *tmp;
    
    tmp = g_data.env_list;
    while(tmp)
    {
        if(!ft_strcmp(exp, tmp->name))
            return(ft_strlen(tmp->value));
        tmp = tmp->next;
    }
    return 0;
}
char* mini_getenv(char *exp)
{
    t_env   *tmp;

    tmp = g_data.env_list;
    while(tmp)
    {
        if(!ft_strcmp(exp, tmp->name))
            return(ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return NULL;
}

char *ret_new_word(char *word, char *exp)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int len;
    char *env_val;
    char *new_word;

    len = get_len(exp);
    new_word = malloc((sizeof(char) * ft_strlen(word) + len) + 1);
    g_data.trash_list = ft_add_trash(&g_data.trash_list, new_word);
    env_val = mini_getenv(exp);
    if(!env_val)
        env_val = NULL;
    else
        g_data.trash_list = ft_add_trash(&g_data.trash_list, env_val);
    while(word[i])
    {
        if(word[i] && word[i] == '$')
        {
            i++;
            while(env_val && env_val[j])
                new_word[k++] = env_val[j++];
            while(ft_isalnum(word[i]))
                i++;
        }
        else
            new_word[k++] = word[i++];
    }
    new_word[k] = '\0';
    return new_word;
}


void    expanding(void)
{
    t_tockens *tmp;
    int i;
    int j;
    char buff[2048];
    
    buff[0] = '\0';
    tmp = g_data.tocken_list;
    while(tmp)
    {
        i = 0;
        while(tmp->word[i])
        {
            if(tmp->word[i] == '$')
            {
                j = 0;
                i++;
                while(tmp->word[i] && ft_isalnum(tmp->word[i]))
                    buff[j++] = tmp->word[i++];
                buff[j] = '\0';
            }
            else
                i++;
        }
        if(buff[0] != '\0')
            tmp->word = ret_new_word(tmp->word, buff);
        tmp = tmp->next;
    }
    
}
