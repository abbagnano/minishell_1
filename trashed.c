
/*
pos:16          TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n00000rh000064/T/
pos:12          SHELL=/bin/zsh
pos:5           HOME=/Users/fgradia
pos:12          SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.h4qe5qPz3a/Listeners
pos:1           Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.z9tZ8yGPgZ/Render
pos:6           LOGNAME=fgradia
pos:10          PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
pos:24          XPC_SERVICE_NAME=0
pos:2           COMMAND_MODE=unix2003
pos:20          USER=fgradia
pos:12          SECURITYSESSIONID=186a8
pos:24          XPC_FLAGS=0x0
pos:26          __CF_USER_TEXT_ENCODING=0xC4:0x0:0x0
pos:8           ORIGINAL_XDG_CURRENT_DESKTOP=undefined
pos:12          SHLVL=1
pos:10          PWD=/Users/fgradia/Desktop/minishell_1
pos:8           OLDPWD=/Users/fgradia/Desktop/minishell_1
pos:16          TERM_PROGRAM=vscode
pos:16          TERM_PROGRAM_VERSION=1.56.2
pos:6           LANG=en_US.UTF-8
pos:2           COLORTERM=truecolor
pos:21          VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n00000rh000064/T/vscode-git-d3cbbd0723.sock
pos:4           GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
pos:21          VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Renderer).app/Contents/MacOS/Code Helper (Renderer)
pos:21          VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
pos:16          TERM=xterm-256color
pos:26          _=/Users/fgradia/Desktop/minishell_1/./minishell
*/


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