#include "my_minishell.h"

int	ft_strchr(char c, char *s1)
{
	int	x;

	x = 0;
	while (s1 && s1[x])
	{
		if (s1[x] == c)
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
/*
int	ft_read(t_list **head)
{
	int		r;

	(*head)->cmd = (char *)malloc(sizeof(char) * 10240);
	(*head)->cmd[10239] = '\0';
	r = read(0, (*head)->cmd, 10239);
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
*/

void	ft_free_read(t_read **head)
{
	t_read	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
}

void	ft_exit(char *str, t_data *data)
{
	ft_write(str);
	ft_free_read(&data->cmd_head);
	free(data->cmd_head);
//	printf("xxxxxxxxxxx\n");
	read(0, &str, 1);
	exit(0);
}

int	ft_buf_to_node(int len, int x, char *buf, t_read *new)
{
	int	y;

	y = 0;
//	if (!ft_check_buf(buf + x, len))
//		return (-1);
	new->line = (char *)malloc(sizeof(char) * (len + 1));
	new->line[len] = '\0';
	while (buf[x] != '\n' && buf[x] != '\0')
	{
		new->line[y++] = buf[x];
		x++;
	}
	new->line[y] = '\0';
	new->next = NULL;
	x++;
	return (x);
}

void	ft_append_read(t_read *new, t_read **head)
{
	t_read	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_buf_to_list(char *buf, t_data *data)
{
	int		len;
	int		x;
	t_read	*new;

	x = 0;
	len = 0;
	while (buf && buf[x])
	{
		len = ft_strchr('\n', buf + x);
		if (len < 0)
			break ;
		//else if (len > 3 || len < 2)
		//	ft_exit("Error: wrong op!\n", data);
		new = (t_read *)malloc(sizeof(t_read) * 1);
		x = ft_buf_to_node(len, x, buf, new);
	//	if (x < 0)
	//		ft_exit("Error:!\n", data);
		ft_append_read(new, &data->cmd_head);
		new = new->next;
	}
}

void	ft_read_ops(t_data *data)
{
	char	*buf;
	int		r;

	buf = (char *)malloc(sizeof(char) * 1024);
	buf[1023] = '\0';
	r = 1;
	while (r > 0)
	{
		r = read(0, buf, 1023);
		buf[r] = '\0';
		if (buf[0] == '\0')
		{
			free(buf);
			return ;
		}
		ft_buf_to_list(buf, data);
		ft_write("minishell% ");
	}
	free(buf);
}

void	ft_print_cmd(t_read **head)
{
	t_read *tmp;

	tmp = *head;
	while (tmp)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}
void	ft_no_arg(t_data *data)
{
//	t_list	*head;
//	int		r;

//	head = (t_list *)malloc(sizeof(t_list) * 1);
//	head->cmd = (char *)malloc(sizeof(char) * 1024);
//	head->cmd[1023] = '\0';
//	r = 1;
//	while (r)
//	{
		ft_write("minishell% ");
	//	r =
	 ft_read_ops(data);
	//	printf("\tcmd: -%s-\n", head->cmd);
		//ft_exec_cmd();
	//}
	ft_write("exit\n");
	ft_print_cmd(&data->cmd_head);
}


int	main(int ac, char **av)
{
	t_data	data;

	data.cmd_head = (t_read *)malloc(sizeof(t_read) * 1);
	data.cmd_head = NULL;
	if (ac == 1)
		ft_no_arg(&data);
	(void)av;
	ft_exit("", &data);
}