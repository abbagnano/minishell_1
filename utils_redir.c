#include "my_minishell.h"

void	ft_charrr(t_char **qwe)
{
	t_char	*tmp;
	t_char	*new;

	new = (t_char *)malloc(sizeof(t_char) * 1);
	new->buf = '\n';
	new->next = NULL;
	if (!*qwe)
	{
		*qwe = new;
		return ;
	}
	tmp = *qwe;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_ctr_c(int *fd)
{
	close(*fd);
	*fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (*fd < 0)
		return (0);
	write(*fd, "\0", 1);
	return (1);
}

// void	ft_flag4_reading(t_data *data, int fd, char *file)
// {
// 	t_char	*qwe;
// 	char	*buf[2];
// 	int		len;

// 	qwe = NULL;
// 	len = 0;
// 	tcsetattr(0, 0, &data->my_term);
// 	while (ft_reading(&qwe, &len, data))
// 	{
// 		if (len == 0 && ft_ctr_c(&fd))
// 			break ;
// 		ft_charrr(&qwe);
// 		ft_linod_to_line(&buf[0], &buf[1], len, &qwe);
// 		len = ft_strlen(file);
// 		if ((ft_strncmp(buf[0], file, len + 1) == '\n'
// 				&& ft_strncmp(buf[0], file, len) == 0) || buf[0][0] == '\0')
// 		{
// 			free(buf[0]);
// 			free(buf[1]);
// 			break ;
// 		}
// 		write(fd, buf[0], ft_strlen(buf[0]));
// 		write(data->std_fd[1], ">", 1);
// 		free(buf[0]);
// 		free(buf[1]);
// 	}
// }


