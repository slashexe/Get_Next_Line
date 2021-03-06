static int			ft_check(char **buffer, char **line)
{
	char			*tmp;

	tmp = ft_strchr(*buffer, '\n');
	if (tmp)
	{
		*line = ft_strsub(*buffer, 0, tmp - *buffer);
		ft_memmove(*buffer, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

static	int			ft_read(int fd, char **buffer, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = NULL;
		if (*buffer)
		{
			tmp = ft_strdup(*buffer);
			ft_memdel((void **)buffer);
			*buffer = ft_strjoin(tmp, buf);
			ft_memdel((void **)&tmp);
		}
		else
			*buffer = ft_strdup(buf);
		if (ft_check(buffer, line))
			return (1);
	}
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static char		*buffer[2147483647];
	int				result;

	if (!line || fd < 0 || fd > 255)
		return (-1);
	if (buffer[fd] && ft_check(&buffer[fd], line))
		return (1);
	result = ft_read(fd, &buffer[fd], line);
	if (result != 0)
		return (result);
	if (buffer[fd] == NULL || buffer[fd][0] == '\0')
		return (0);
	*line = buffer[fd];
	buffer[fd] = NULL;
	return (1);
}