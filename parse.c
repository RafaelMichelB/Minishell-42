#include "Pipex/libft/libft.h"
#include "Pipex/inc/pipex_bonus.h"

int is_in_str(char c, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void    parse4(char *cmd, int *i, t_list **lst, int *start)
{
    if (cmd[*i] == '$')
    {
        *start = *i;
        (*i)++;
        while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
            (*i)++;
        ft_lstadd_back(lst, ft_lstnew(ft_substr(cmd, *start, *i - *start + 1)));
        (*i)++;
    }
    else
    {
        *start = *i;
        (*i)++;
        while (is_in_str(cmd[*i], "'$<>| ") == 0 && cmd[*i] != '\0')
            (*i)++;
        ft_lstadd_back(lst, ft_lstnew(ft_substr(cmd, *start, *i - *start)));
    }
} // 17

void    parse3(char *cmd, int *i, t_list **lst, int *start)
{
    if (cmd[*i] == 34)
    {
        (*i)++;
        *start = *i;
        while (cmd[*i] != 34)
            (*i)++;
        ft_lstadd_back(lst, ft_lstnew(ft_substr(cmd, *start, *i - *start)));
        (*i)++;
    }
    else if (cmd[*i] == 39)
    {
        *start = *i;
        (*i)++;
        while (cmd[*i] != 39)
            (*i)++;
        ft_lstadd_back(lst, ft_lstnew(ft_substr(cmd, *start, *i - *start + 1)));
        (*i)++;
    }
    else
        parse4(cmd, i, lst, start);
} // 20

void    parse2(char *cmd, int *i, t_list **lst, int *start)
{
    if (cmd[*i] == '>')
    {
        if (cmd[*i + 1] == '>')
        {
            ft_lstadd_back(lst, ft_lstnew(ft_strdup(">>")));
            (*i)++;
        }
        else
            ft_lstadd_back(lst, ft_lstnew(ft_strdup(">")));
        (*i)++;
    }
    else if (cmd[*i] == '|')
    {
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("|")));
        (*i)++;
    }
    else
        parse3(cmd, i, lst, start);
} //17

t_list *parser(char *cmd, int i)
{
    t_list  *lst;
    char    *var1;
    char    *var2;
    int     start;

    lst = NULL;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == ' ')
            i++;
        else if (cmd[i] == '<')
        {
            if (cmd[i + 1] == '<')
            {
                ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<<")));
                i++;
            }
            else
                ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<")));
            i++;
        }
        else
            parse2(cmd, &i, &lst, &start);
    }
    return (lst);
} // 25 

#include <stdio.h>
void    check_parsing(t_list **lst)
{
    t_list *cpy;
    int     flag;

    flag = 0;
    cpy = *lst;
    if (ft_strlen((*lst)->content) != 1 || ((char *)((*lst)->content))[0] != '<')
    {
        ft_lstadd_front(lst, ft_lstnew(ft_strdup("/dev/stdin")));
        ft_lstadd_front(lst, ft_lstnew(ft_strdup("<")));
    }
    while (cpy != NULL)
    {
        if (((char *)(cpy->content))[0] == '|' )
            flag = 1;
        cpy = cpy->next;
    }
    if (flag == 0)
    {
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("|")));
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("cat")));
        ft_lstadd_back(lst, ft_lstnew(ft_strdup(">")));
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("/dev/stdout")));
    }
    cpy = *lst;
    while (cpy->next->next != NULL)
        cpy = cpy->next;
    if ((ft_strlen(cpy->content) != 1 || ((char *)(cpy->content))[0] != '>') && \
    (ft_strlen(cpy->content) != 2 || (((char *)(cpy->content))[0] != '>' && ((char *)(cpy->content))[1] != '>')))
    {
        ft_lstadd_back(lst, ft_lstnew(ft_strdup(">")));
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("/dev/stdout")));
    }
} // 31

static void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char    *join_space(char *str_f, char *strtemp)
{
    char *temp;
    char *to_ret;

    temp = ft_strjoin(str_f, " ");
    to_ret = ft_strjoin(temp, strtemp);
    free(str_f);
    free(strtemp);
    return (to_ret);
}

char    *join_space_nof(char *str_f, char *strtemp)
{
    char *temp;
    char *to_ret;

    temp = ft_strjoin(str_f, " ");
    to_ret = ft_strjoin(temp, strtemp);
    free(str_f);
    return (to_ret);
}

t_list *create_args(t_list *lst, int f)
{
    t_list *tmp;
    t_list *ret;
    char    **tab;
    char    *str_temp;
    char    *str[2];
    char    *str_f;
    int     flag;
    int     n;

    str[0] = ft_calloc(1, sizeof(char));
    ret = NULL;
    tmp = NULL;
    while (lst != NULL)
    {
        str_f = ft_calloc(1, sizeof(char));
        tab = ft_split(lst->content, ' ');
        n = 0;
        flag = 0;
        while (tab[n])
        {
            if (tab[n][0] == 39)
            {
                flag = 1;
                str_temp = ft_strdup(tab[n]);
            }
            else if (tab[n][ft_strlen(tab[n]) - 1] == 39 && flag == 1)
            {
                flag = 0;
                str_temp = ft_strdup(tab[n]);
            }
            else if (tab[n][0] == '$' && tab[n][1] == '?')
                str_temp = ft_itoa(f);
            else if (tab[n][0] == '$' && flag == 0)
                str_temp = ft_strdup(getenv(&tab[n][1]));
            else
                str_temp = ft_strdup(tab[n]);
            str_f = join_space(str_f, str_temp);
            n++;
        }
        ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(str_f)));
        free(str_f);
        lst = lst->next;
    }
    tmp = tmp->next;
    ft_lstadd_back(&ret, ft_lstnew(ft_strdup(tmp->content)));
    tmp = tmp->next;
    while (((char *)(tmp->content))[1] != '>')
    {
        if (((char *)(tmp->content))[1] != '|' && ((char *)(tmp->content))[1] != '>')
            str[0] = join_space_nof(str[0], &((char *)(tmp->content))[1]);
        else
        {
            ft_lstadd_back(&ret, ft_lstnew(ft_strdup(str[0])));
            free(str[0]);
            str[0] = ft_calloc(1, sizeof(char));
        }
        tmp = tmp->next;
    }
    ft_lstadd_back(&ret, ft_lstnew(ft_strdup(str[0])));
    tmp = tmp->next;
    ft_lstadd_back(&ret, ft_lstnew(ft_strdup(tmp->content)));
    return (ret);
}

#include <fcntl.h>
int main2(char *v, char **env, int *flag)
{
    t_list *lst;
    t_list *cpy;
    t_list *ret;
    int fd[4];
    char **tab;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (0);
    if (pid == 0)
    {
        lst = parser(v, 0);
        check_parsing(&lst);
        cpy = lst;
        while (cpy != NULL)
            cpy = cpy->next;
        ret = create_args(lst, *flag);
        tab = ft_calloc(ft_lstsize(ret) + 1, sizeof(char *));
        tab[0] = "Start";
        fd[2] = 1;
        while (ret != NULL)
        {
            tab[fd[2]] = &(((char *)(ret->content))[1]);
            ret = ret->next;
            fd[2]++;
        }
        pimain(fd[2], tab, env);
    }
    else
    {
        waitpid(pid, &status, 0);
        *flag = status;
    }
}

int main3(int c, char **v, char **env, int *flag)
{
    t_list *lst;
    t_list *cpy;
    t_list *ret;
    int fd[4];
    char **tab;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (0);
    if (pid == 0)
    {
        lst = parser("echo 'Hello $?'", 0);
        check_parsing(&lst);
        cpy = lst;
        while (cpy != NULL)
            cpy = cpy->next;
        ret = create_args(lst, *flag);
        tab = ft_calloc(ft_lstsize(ret) + 1, sizeof(char *));
        tab[0] = "Start";
        fd[2] = 1;
        while (ret != NULL)
        {
            tab[fd[2]] = &(((char *)(ret->content))[1]);
            ret = ret->next;
            fd[2]++;
        }
        pimain(fd[2], tab, env);
    }
    else
    {
        waitpid(pid, &status, 0);
        *flag = status;
    }
}

#include <readline/readline.h>
#include <readline/history.h>

int main(int c, char **v, char **env)
{
    int flag;
    char *str;

    flag = -1;
    while (1)
    {
        str = readline(">> ");
        main2(str, env, &flag);
    }
}
