#include "my_minishell.h"

int	ft_strchr(char *str, char c)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (x);
		x++;
	}
	return (-1);
}
/*
void	ft_buf_to_list(char *buf, t_list **head, int n)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
		tmp = tmp->next;
	tmp = (t_list *)malloc(sizeof(t_list) * 1);
	tmp->cmd = (char *)malloc(sizeof(char) * n);
	/// .... .... while ft_strchr(buf, '\n') >= 0 
}
*/
int		ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_write(char *str)
{
	int len;

	len = ft_strlen(str);
	write(0, str, len);
}
/*
void	ft_read(t_list **head)
{
	char	*buf;
	int		r;
	int		n;

//	r = read(0, (*head)->cmd, 1023);
//	(*head)->cmd[r] = '\0';
	r = 1;
	n = 1;
	buf = (char *)malloc(sizeof(char) * 1024);
	buf[1023] = '\0';
	while (r > 0 && n >= 0)
	{
		buf = NULL;
		r = read(0, buf, 1023);
		buf[r] = '\0';
		printf("ft_buf_to_cmd(buf, cmd);\n");
		n = ft_strchr(buf, '\n');
		ft_buf_to_list(buf, head, n);
	}
	free(buf);
}
*/

int	ft_read(t_list **head)
{
	int		r;

	(*head)->cmd = (char *)malloc(sizeof(char) * 1024);
	(*head)->cmd[1023] = '\0';
	r = read(0, (*head)->cmd, 1023);
	if (r > 1)
		(*head)->cmd[r - 1] = '\0';
	if ((*head)->cmd[0] == '\0')
		return (0);
	return (1);
}

void	ft_no_arg()
{
	t_list	*head;
	int		r;

	head = (t_list *)malloc(sizeof(t_list) * 1);
//	head->cmd = (char *)malloc(sizeof(char) * 1024);
//	head->cmd[1023] = '\0';
	r = 1;
	while (r)
	{
		ft_write("minishell% ");
		r = ft_read(&head);
	//	printf("\tcmd: -%s-\n", head->cmd);
		//ft_exec_cmd();
	}
	ft_write("exit\n");
}

int	main(int ac, char **av)
{
	if (ac == 1)
		ft_no_arg();
	(void)av;
}