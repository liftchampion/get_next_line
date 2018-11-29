int		ft_numlen(int num)
{
	int len;

	len = num > 0 ? 0 : 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}