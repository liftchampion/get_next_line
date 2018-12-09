/*char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			act_len;
	size_t			src_len;
	unsigned int	i;

	if (!s)
		return (0);
	src_len = ft_strlen(s);
	if (src_len + 1 <= start)
		act_len = 0;
	else
		act_len = (len >= src_len + 1 - start ? src_len + 1 - start : len);
	str = (char*)malloc(act_len + 1);
	if (!str)
		return (0);
	i = 0;
	while (i++ < act_len)
		str[i - 1] = s[start + i - 1];
	str[i - 1] = 0;
	return (str);
}*/