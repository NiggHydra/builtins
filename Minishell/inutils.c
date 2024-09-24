
char **assign_val2(char **str)
{
	int i = 0;

	printf ("hereeeeee\n");
	while (str[i] != NULL)
	{
		if (str[i][0] == '=' && str[i][1] != '"')
		{
			str[i] = ft_strjoin("\"", str[i]);
			str[i] = ft_strjoin(str[i], "\"");
		}
		i ++;
	}
	return (str);
}
char  *assign_val(char *s)
{
	int i ;
	int j;
	char *cpy;

	i = 0;
	j = 0;	
	cpy = malloc(sizeof(char ) * (ft_strlen(s) + 3));
	while (s[i] != '\0')
	{
		if (s[i] == '=')
		{
			cpy [j] = s[i];
			j ++;
			cpy[j] = '"';
			i ++;
			j ++;
		}
		else
		{
			cpy[j] = s[i];
			i++;
			j++;
		}
	}
	i++;
	cpy[i] = '"';
	cpy[i + 1] = '\0';

	return (cpy);
}