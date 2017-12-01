#include "../includes/libft.h"
#include "../includes/get_next_line.h"

char	*joinchar(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

static	int		ft_copyuntil(char **dst, char *src, char c)
{
	int		i;
	int		count;
	int		pos;

	i = -1;
	count = 0;
	while (src[++i])
		if (src[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[count] && count < i)
	{
		if (!(*dst = joinchar(*dst, src[count])))
			return (0);
		count++;
	}
	return (pos);
}

static	t_list	*ft_savedata(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	t_list			*curr;
	static t_list	*file;
	int				ret;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);
	//curr = NULL;
	//printf("%s||\n\n", curr);
	//fct pour curr rest du text mit apres length
	curr = ft_savedata(&file, fd);
	if ((*line = ft_strnew(1)) == 0)
		return (-1)
	if ((curr->content = ft_strjoin(curr->content, buf)) == 0)
			return (-1);
	//curr = ft_lstnew("\0", fd);
	if ((*line = ft_strnew(1)) == 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		//printf(" |%d|%s|| \n", ret,buf);
		if ((curr->content = ft_strjoin(curr->content, buf)) == 0)
			return (-1);
		if (strchr(buf, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(curr->content))
		return (0);
	ret = ft_copyuntil(line, curr->content, '\n');
	if (ret < (int)ft_strlen(curr->content))
		curr->content += (ret + 1);
	else
		ft_strclr(curr->content);
	return (1);
}