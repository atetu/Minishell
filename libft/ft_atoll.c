unsigned long long  		ft_atoll(const char *str)
{
	long long             i;
	long long             neg;
	unsigned long long total;
    unsigned long long  max;

	total = 0;
	neg = 1;
	i = 0;
    max = 9223372036854775807;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
    if ((neg < 0 && total > (max + 1)) || (neg > 0 && total > max))
        return (max + 2);
	return (total);
}