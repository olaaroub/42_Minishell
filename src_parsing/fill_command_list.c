/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:24:13 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/18 23:00:12 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int len_until_pipe(t_tockens *temp)
{
    t_tockens *tmp;
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

static char *trim_quotes(char *word)
{
    char *ret;
    char quote;

    g_data.i = 0;
    g_data.j = 0;
    if(!word)
        return NULL;
    ret = malloc(sizeof(char) * (ft_strlen(word) + 1));
    g_data.trash_list = ft_add_trash(&g_data.trash_list, ret);
    while (word[g_data.i])
    {
        if (word[g_data.i] == '"' || word[g_data.i] == '\'')
        {
            quote = word[g_data.i++];
            while (word[g_data.i] && word[g_data.i] != quote)
                ret[g_data.j++] = word[g_data.i++];
            if (word[g_data.i] == quote)
                g_data.i++;
        }
         else
            ret[g_data.j++] = word[g_data.i++];
    }
    ret[g_data.j] = '\0';
    return ret;
}

static int fill_commands_redirs(t_tockens **temp, t_redir **redir, char **commands)
{
    int i;
    int j;

    i = 0;
    while(*temp && (*temp)->type != PIPE)
    {
        if((*temp)->type == INPUT || (*temp)->type == OUTPUT || (*temp)->type == APPEND || (*temp)->type == HEREDOC)
        {
            if( (*temp)->next && (*temp)->next->ambiguous == false)
                *redir = ft_add_redir(redir, (*temp)->next->word, (*temp)->type);
            else if((*temp)->next)
            {
                printf("minishell: %s: AMBIGUOUS REDIRECT\n", (*temp)->next->dollar);
                g_data.ret_value = 1;
                *redir = ft_add_redir(redir, NULL, AMBIG);
                commands[i] = NULL;
                while((*temp) && (*temp)->type != PIPE)
                    (*temp) = (*temp)->next;
                return -1;
            }
            (*temp) = (*temp)->next->next;
        }
        else
        {
            if((*temp)->word_after_exp && (*temp)->word_after_exp[1] != NULL)
            {
                j = 0;
                while((*temp)->word_after_exp[j])
                {
                    commands[i] = ft_strdup(trim_quotes((*temp)->word_after_exp[j++]));
                    g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[i++]);
                }
            }
            else
            {
                (*temp)->word = trim_quotes((*temp)->word);
                commands[i] = ft_strdup((*temp)->word);
                g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[i++]);
            }
            (*temp) = (*temp)->next;
        }
    }
    commands[i] = 0;
    return 0;
}

void    fill_command_list(void)
{
    t_tockens   *temp;
    t_redir     *redir;
    char        **commands;
    int len;

    temp = g_data.tocken_list;
    while (temp)
    {
        len = len_until_pipe(temp);
        commands = (char **)malloc(sizeof(char *) * (len + 1));
        g_data.trash_list = ft_add_trash(&g_data.trash_list, commands);
        redir = NULL;
        fill_commands_redirs(&temp, &redir, commands);
            // continue;
        g_data.command_list = ft_add_command(&g_data.command_list, commands, redir);
        if(temp)
            temp = temp->next;
    }
}
