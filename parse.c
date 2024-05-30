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

t_list *parser(char *cmd)
{
    t_list  *lst;
    int     i;
    int     start;

    i = 0;
    lst = NULL;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == ' ' || cmd[i] == '\"')
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
        else if (cmd[i] == '>')
        {
            if (cmd[i + 1] == '>')
            {
                ft_lstadd_back(&lst, ft_lstnew(ft_strdup(">>")));
                i++;
            }
            else
                ft_lstadd_back(&lst, ft_lstnew(ft_strdup(">")));
            i++;
        }
        else if (cmd[i] == '|')
        {
            ft_lstadd_back(&lst, ft_lstnew(ft_strdup("|")));
            i++;
        }
        else if (cmd[i] == '\'')
        {
            start = i;
            i++;
            while (cmd[i] != '\'')
                i++;
            ft_lstadd_back(&lst, ft_lstnew(ft_substr(cmd, start, i - start + 1)));
            i++;
        }
        else if (cmd[i] == '$')
        {
            start = i;
            i++;
            while (ft_isalnum(cmd[i]) || cmd[i] == '_')
                i++;
            ft_lstadd_back(&lst, ft_lstnew(ft_substr(cmd, start, i - start + 1)));
            i++;
        }
        else
        {
            start = i;
            i++;
            while (is_in_str(cmd[i], "\"\'$<>| ") == 0 && cmd[i] != '\0')
                i++;
            ft_lstadd_back(&lst, ft_lstnew(ft_substr(cmd, start, i - start)));
        }
    }
    return (lst);
}

#include <stdio.h>
void    check_parsing(t_list **lst)
{
    t_list *cpy;
    int     flag;

    flag = 0;
    cpy = *lst;
   // printf("len :%ld\n", ft_strlen((*lst)->content));
    if (ft_strlen((*lst)->content) != 1 || ((char *)((*lst)->content))[0] != '<')
    {
        ft_lstadd_front(lst, ft_lstnew(ft_strdup("/dev/stdin")));
        ft_lstadd_front(lst, ft_lstnew(ft_strdup("<")));
    }
  //  write(1, "B\n", 2);
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
   // write(1, "A\n", 2);
    while (cpy->next->next != NULL)
        cpy = cpy->next;
  //  printf("char: %s\n", (char *)(cpy->content));
    if ((ft_strlen(cpy->content) != 1 || ((char *)(cpy->content))[0] != '>') && \
    (ft_strlen(cpy->content) != 2 || (((char *)(cpy->content))[0] != '>' && ((char *)(cpy->content))[1] != '>')))
    {
        ft_lstadd_back(lst, ft_lstnew(ft_strdup(">")));
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("/dev/stdout")));
    }

}

t_list *create_args(t_list *lst)
{
    t_list *ret;
    t_list *cpy;
    char    *str[3];

    str[0] = ft_calloc(1, sizeof(char));
    ret = NULL;
    cpy = lst;
    cpy = cpy->next;
    ft_lstadd_back(&ret, ft_lstnew(ft_strdup(cpy->content)));
    cpy = cpy->next;
    while (((char *)(cpy->content))[0] != '>')
    {
        while (((char *)(cpy->content))[0] != '|' && ((char *)(cpy->content))[0] != '>')
        {
            str[1] = ft_strjoin(str[0], cpy->content);
            free(str[0]);
            str[0] = ft_strjoin(str[1], " ");
            free(str[1]);
            cpy = cpy->next;
        }
        ft_lstadd_back(&ret, ft_lstnew(ft_strdup(str[0])));
       // ft_putstr_fd(str[0], 1);
       // ft_putchar_fd('\n', 1);
        free(str[0]);
        str[0] = ft_calloc(1, sizeof(char));
        if (((char *)(cpy->content))[0] != '>')
            cpy = cpy->next;
    }
    cpy = cpy->next;
    ft_lstadd_back(&ret, ft_lstnew(ft_strdup(cpy->content)));
    return (ret);
}

#include <fcntl.h>
int main(int c, char **v, char **env)
{
    t_list *lst;
    t_list *cpy;
    t_list *ret;
    int fd[4];
    char **tab;

    lst = parser(v[1]);
    check_parsing(&lst);
    cpy = lst;
    /*while (cpy != NULL)
    {
        printf("%s ", (char *)(cpy->content));
        cpy = cpy->next;
    }*/
    //fd[0] = open("/dev/stdin", O_RDONLY);
   // fd[1] = open("/dev/stdout", O_WRONLY);
   // printf("Fds open: %d, %d\n", fd[0], fd[1]);
    ret = create_args(lst);
    tab = ft_calloc(ft_lstsize(ret) + 1, sizeof(char *));
    tab[0] = "Start";
    fd[2] = 1;
    while (ret != NULL)
    {
        tab[fd[2]] = (char *)(ret->content);
        ret = ret->next;
        fd[2]++;
    }
    pimain(fd[2], tab, env);
}