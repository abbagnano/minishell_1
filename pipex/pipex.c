#include "pipex.h"

char	**ft_opt_to_sort(char *s1, char **sort_av, int y, int z)
{
	int		x;
	char	**new;

	x = 0;
	new = (char **)malloc(sizeof(char *) * (y + 1));
	while (x < y)
	{
		new[x] = sort_av[x];
		x++;
	}
	x = 0;
	new[y - 1] = (char *)malloc(sizeof(char) * (z + 1));
	while (x < z)
	{
		 new[y - 1][x] = s1[x];
		 x++;
	}
	new[y - 1][x] = '\0';
	new[y] = NULL;
	free(sort_av);
	return (new);
}


int	ft_change_path(char *cmd, t_data *data, int *x, char *env)
{
	int	y;
	int	z;
	int	len;

	y = 0;
	z = 0;
	if (!env[*x])
		ft_exit("cmd not found\n", data);
	if (env[*x] == ':')
		(*x)++;
	while (env[*x + y] && env[*x + y] != ':')
		y++;
	len = ft_strchr(' ', cmd);
	if (len == -1)
		len = ft_strlen(cmd);
	y += len;
	if (*x > 5)
		free(data->sort_av[0]);
	data->sort_av[0] = (char *)malloc(sizeof(char) * (y + 2));
	y = 0;
	while (env[*x] && env[*x] != ':')
		data->sort_av[0][y++] = env[(*x)++];
	data->sort_av[0][y++] = '/';
	while (cmd && cmd[z] && cmd[z] != ' ')
		data->sort_av[0][y++] = cmd[z++];
	data->sort_av[0][y] = '\0';
	return (z);
}

void	ft_get_cmd_options(char *cmd, t_data *data)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	y = 1;
	z = 0;
	while (cmd[x + z])
	{
		z = 0;
		while (cmd[x + z] == ' ')
			x++;
		while (cmd[x + z] && cmd[x + z] != ' ')
			z++;
		
			//sort_av[y] = (char *)malloc(sizeof(char) * (z + 1));
		y++;
		data->sort_av = ft_opt_to_sort(cmd + x, data->sort_av, y, z);			
		
		x += z;
	}

}

void	ft_find_cmd(char *cmd, char *env, t_data *data)
{
	int		r;
	int		x;
	int		z;
	//char	*cmd_path;

	r = -1;
	x = 5;
	while (r == -1) // && env[x])
	{
	//	printf("qwe\n");
		//cmd_path = 
		z = ft_change_path(cmd, data, &x, env);
		r = open(data->sort_av[0], O_RDONLY);
	}
//	printf("cmd: %s\n", data->cmd_path);
	//ft_sort_av(cmd_path, sort_av, 0);
	if (cmd[z])
		ft_get_cmd_options(cmd + z, data);
}

// av[0] == pipex	/	av[1] == outfile	/	av[2] == cmd1(con le opzioni che vanno separate)	
//	av[3] == cmd2	/	av[4] == outfile
int	main(int ac, char **av, char **env)
{
	int		path_env;	
	t_data	data;

	if (ac < 3)
		ft_exit("wrong args\n", &data);
	data.dup_stdout = open("outfile", O_RDWR | O_TRUNC | O_CREAT, 0666);
	data.dup_stdout =  dup2(data.dup_stdout, 1);
	data.sort_av = (char **)malloc(sizeof(char *) * 2);
	data.sort_av[0] = NULL;
	data.sort_av[1] = NULL;
	ft_find_path_env(&path_env, env);
	ft_find_cmd(av[2], env[path_env], &data);
	ft_infile_to_sort(&data, av[1]);
	// int x = 0;
	// while (data.sort_av[x])
	// {
	// 	printf("sort_av[%d] : %s\n", x, data.sort_av[x]);
	// 	x++;
	// }
//	int f = fork();

	if (f != 0)
		execve(data.sort_av[0], data.sort_av, env);
	else
		ft_pipe(av, &data);
	close(data.dup_stdout);
	ft_exit("", &data);
}
