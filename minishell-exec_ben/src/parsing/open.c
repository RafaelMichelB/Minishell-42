
#include "pars.h"
//FONCTION POUR LES REDIRECTIONS open etc
//open ouvre dans le file racine du dossier
//faire les fonctions pour gere le cas heredoc
void    open_redir(t_command *node, int i, int fd)
{
	printf("\nstart redir\nfd_out value %d\n", node->fd_out);
	while(node->cmd_ex[++i] != NULL)
	{
		if (node->cmd_ex[i][0] == '<' && node->cmd_ex[i][1] == '<')
			heredoc(node, i);
		else if (node->cmd_ex[i][0] == '<')
		{
			printf("\"%s\" namefile IN\n", node->cmd_ex[i + 1]);
			fd = open(node->cmd_ex[i + 1], O_RDONLY);
			if (fd == -1)
			{
				perror("open");//return (), set_error(), data->index++ pas fou; skip la commande
				node->fd_in = -2;
			}
			else
			{
				if (node->fd_in > -1)
				{
					close(node->fd_in);
					printf("close fd_in\n");
				}
				node->fd_in = fd;
			}
			printf("%d FD_IN\n", node->fd_in);
		}
		if (node->cmd_ex[i][0] == '>')
			handle_output(node, i, fd);
	}
	supr_redir(node, 0, 0);
	printf("FINISH_REDIR\n");
}

void handle_output(t_command *node, int i, int fd)
{
	printf("\"%s\" namefile OUT\n", node->cmd_ex[i + 1]);
	if (node->cmd_ex[i][0] == '>' && node->cmd_ex[i][1] == '>')
		fd = open(node->cmd_ex[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(node->cmd_ex[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		node->fd_out = -2;
	}
	if (node->fd_out > -1)
	{
		close(node->fd_out);
		printf("close fd_OUT %s\n", node->cmd_ex[i - 1]);
	}
	node->fd_out = fd;
	printf("%d FD_OUT\n", node->fd_out);
}

void	supr_redir(t_command *node, int i, int pos)
{
	int nb; // nbr a supr du tab

	while (node->cmd_ex[i] != NULL)
	{
		nb = -1;
		if ((node->cmd_ex[i][0] == '<' && node->cmd_ex[i][1] == '<') ||
			(node->cmd_ex[i][0] == '>' && node->cmd_ex[i][1] == '>') ||
			(node->cmd_ex[i][0] == '<' && node->cmd_ex[i][1] != '<') ||
			(node->cmd_ex[i][0] == '>' && node->cmd_ex[i][1] != '>'))
		{
			pos = i;
			nb = 1;
		}
		if (nb == -1)
			i++;
		while (nb != -1)
		{
			// printf("ligne a supr \"%s\"\n", node->cmd_ex[pos]);
			node->cmd_ex = suprin_tab(node->cmd_ex, 0, pos);
			nb--;
		}
	}
	i = -1;
	while (node->cmd_ex[++i] != NULL)
		printf("test final supr \n%s\n", node->cmd_ex[i]);
}

char	**suprin_tab(char **tab, int i, int pos)
{
	char	**cpy;
	int		tlen;
	int		len;

	tlen = 0;
	len = -1;

	while (tab[tlen] != NULL)
		tlen++;
	cpy = (char **)malloc(sizeof(char *) * tlen);
	while (++len < tlen)
	{
		if (len == pos)
		{
			printf("Suprintab \"%s\"\n", tab[len]);
			len++;
		}
		if (len < tlen)
		{
			cpy[i] = ft_strdup(tab[len]);
			i++;
		}
	}
	cpy[i] = NULL;
	free_split_str(tab);
	return cpy;
}

int	heredoc(t_command *node, int i)
{
	char	*stack;
	int		len;

	len = ft_strlen(node->cmd_ex[i + 1]);
	node->fd_in = open(".here_doc", O_RDWR | O_CREAT | O_APPEND, 0777);
	printf("value fd_in %d\n", node->fd_in);
	node->flags = 1;
	while (1)
	{
		stack = readline("heredoc:");
		if (!stack)
			return (0);
		if (compare_str(stack, node->cmd_ex[i + 1], len) == 0)
			return (free(stack), lseek(node->fd_in, 0, SEEK_SET), 0);
		ft_putstr_fd(stack, node->fd_in);
		ft_putstr_fd("\n", node->fd_in);
		free(stack);
	}
	return (0);
}
