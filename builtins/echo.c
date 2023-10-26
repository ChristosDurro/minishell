/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:20:55 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 14:23:29 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_quotes(char *str)
{
	int	d_quote;
	int	s_quote;
	int	i;
	int	j;
	int len;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	len = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (str[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		// printf("d_quote=%d | s_quote=%d | i=%d | j=%d\n", d_quote, s_quote, i, j);
		i++;
	}
	if ((s_quote % 2) || (d_quote % 2))
		return (0);
	return (1);
}

static char	*expand(char *str, int *k, t_shell shell)
{
	char *env;
	int i;
	int len;

	// printf("str got: %s\n", str);
	len = ft_strlen(str);
	i = 1;
	// in here i count till get a character other than alphanumerical or _ so that i can then form the correct name of my variable being created
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	// printf("value: %d\n", i);
	str = ft_substr(str, 0, i);
	// printf("new str: %s\n", str);
	*k += ft_strlen(str);
	// printf("k value: %d\n", *k);
	env = get_env(str + 1, shell);
	// printf("env got: %s\n", env);
	free(str);
	if (!env)
		return ("");
	return (env);
}

void	echo(t_token *start, t_shell shell)
{
	t_token *current;
	int i;
	int j;
	int k;
	int len;
	int n_flag;

	if (start->next)
		current = start->next;
	else
	{
		printf("\n");
		return ;
	}

	i = 1;
	n_flag = 0;
	while (current)
	{
		len = 0;
		j = 0;
		// if it starts with double quote, then check if it also ends with it and check each character of the argument, if i have something like echo "Hello there $USER, you are in $PATH", then i will iterate through the string print every character until i meet the '$', then expand (basically get the value of the variable), and also change the position of k to be after the $USER variable so i can continue printing all the characters just fine.
		if (current->value[0] == '"')
		{
			if (!valid_quotes(current->value))
			{
				printf("Unmatched brackets!");
				break;
			}
			k = 1;
			while (current->value[k])
			{
				if (current->value[k] == '$')
				{
					printf("%s", expand(current->value + k, &k, shell));
				}
				if (current->value[k] == '"')
					k++;
				if (current->value[k] == '\0')
					break;
				else
					printf("%c", current->value[k]);
				k++;
			}
		}
		else if (current->value[0] == '$' && current->value[1] == '?' && current->value[2] == '\0')
			printf("%d\n", g_status);
		// this is the case that only something like echo $USER $PATH is given as input
		else if (current->value[0] == '$')
			printf("%s", expand(current->value, &k, shell));
		// this is the case i have single quotes, echo 'Hello there $USER, you are in $PATH', should give back - Hello there $USER, you are in $PATH
		else if (current->value[0] == '\'')
		{
			if (!valid_quotes(current->value))
			{
				printf("Unmatched brackets!");
				break;
			}
			k = 1;
			while (current->value[k])
			{
				if (current->value[k] == '\'')
					break;
				printf("%c", current->value[k]);
				k++;
			}
		}
		// here i check if the -n flag is given as parameter and is located at the second place
		else if ((current->value[0] == '-' && current->value[1] == 'n' && current->value[2] == '\0') && current->index == 1)
		{
			n_flag = 1;
			current = current->next;
			continue;
		}
		// here just print the message if it's something simple like echo Hello there without quotes or $
		else
			printf("%s", current->value);
		// this is just putting a space at the end of every word except for the last one
		if (current->next != NULL && (current->value[0] != '\'' && current->value[0] != '"' && current->next->value[0] != '\'' && current->next->value[0] != '"'))
			printf(" ");
		current = current->next;
	}
	if (!n_flag)
		printf("\n");
}
