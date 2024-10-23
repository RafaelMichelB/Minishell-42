#include "pars.h"

t_command	*ft_init_node(void)
{
	t_command *node;

	node = malloc(sizeof(t_command));

	node->line = NULL;
	node->cmd_ex = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->flags = 0;
	node->next = NULL;
	return (node);
}