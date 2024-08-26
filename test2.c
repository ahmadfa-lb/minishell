
// #include "includes/minishell.h"
// #include <readline/readline.h>
// #include <readline/history.h>


// ssize_t read_status_file(char *buffer, size_t size)
// {
//     int fd = open("/proc/self/status", O_RDONLY);
//     ssize_t bytesRead = -1;
//     if (fd != -1)
//     {
//         bytesRead = read(fd, buffer, size - 1);
//         close(fd);
//     }
//     return (bytesRead);
// }

// pid_t ft_getuid()
// {
//     char buffer[256];
//     ssize_t bytesRead;
//     char *uid_line;
//     pid_t uid = -1;

//     bytesRead = read_status_file(buffer, sizeof(buffer));
//     if (bytesRead > 0)
//     {
//         buffer[bytesRead] = '\0';
//         uid_line = ft_strstr(buffer, "Uid:");
//         if (uid_line)
//         {
//             uid_line = ft_strchr(uid_line, '\t');
//             if (uid_line)
//                 uid = ft_atoi(uid_line + 1);
//         }
//     }
//     return (uid);
// }

// int	get_int_length(int n)
// {
// 	int		length;
// 	bool	is_negative;

// 	length = 0;
// 	is_negative = n < 0;
// 	if (n == 0)
// 		return (1);
// 	if (is_negative)
// 		n = -n;
// 	while (n > 0)
// 	{
// 		n /= 10;
// 		length++;
// 	}
// 	if (is_negative)
// 		return (length + 1);
// 	else
// 		return (length);
// }

// char	*ft_strcpy(char *dest, const char *src)
// {
// 	char	*original_dest;
// 	int		i;

// 	original_dest = dest;
// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src [i];
// 		i++;
// 	}
// 	original_dest[i] = '\0';
// 	return (original_dest);
// }

// int	get_len(int n)
// {
// 	int	len;

// 	len = 0;
// 	if (n == 0)
// 	{
// 		return (1);
// 	}
// 	if (n < 0)
// 	{
// 		n *= -1;
// 		len++;
// 	}
// 	while (n > 0)
// 	{
// 		n /= 10;
// 		len++;
// 	}
// 	return (len);
// }

// char	*ft_itoa(int n)
// {
// 	int		sign;
// 	char	*nb;
// 	int		len;

// 	len = get_len(n);
// 	sign = 1;
// 	if (n == -2147483648)
// 		return (ft_strdup("-2147483648"));
// 	if (n < 0)
// 		sign = -1;
// 	n = n * sign;
// 	nb = (char *)malloc((len + 1) * sizeof(char));
// 	if (!nb)
// 		return (NULL);
// 	nb[len--] = '\0';
// 	while (len >= 0)
// 	{
// 		nb[len--] = '0' + (n % 10);
// 		n = n / 10;
// 	}
// 	if (sign == -1)
// 		nb[0] = '-';
// 	return (nb);
// }

// char	*ft_strstr(char *haystack, char *needle)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (needle[0] == '\0')
// 		return (haystack);
// 	while (haystack[i] != '\0')
// 	{
// 		j = 0;
// 		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
// 		{
// 			if (needle[j + 1] == '\0')
// 				return (&haystack[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// size_t	check_len(size_t s_len, unsigned int start, size_t len)
// {
// 	size_t	mlen;

// 	mlen = s_len - (size_t)start;
// 	if (mlen > len)
// 		mlen = len;
// 	return (mlen);
// }

// char	*check_alloc(size_t max_len)
// {
// 	char	*s_str;

// 	s_str = (char *)malloc(max_len + 1);
// 	if (s_str == NULL)
// 		return (NULL);
// 	return (s_str);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	s_len;
// 	size_t	max_len;
// 	char	*sub_str;
// 	char	*empty_str;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 	{
// 		empty_str = ft_strdup("");
// 		return (empty_str);
// 	}
// 	max_len = check_len(s_len, start, len);
// 	sub_str = check_alloc(max_len);
// 	i = 0;
// 	while (i < max_len && s[start + i] != '\0')
// 	{
// 		sub_str[i] = s[start + i];
// 		i++;
// 	}
// 	sub_str[i] = '\0';
// 	return (sub_str);
// }

// char	*ft_strncpy(char *dest, const char *src, size_t n) 
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (src[i] != '\0') 
// 			dest[i] = src[i];
// 		else
// 			dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

// int	ft_atoi(const char *nptr)
// {
// 	int	i;
// 	int	result;
// 	int	sign;

// 	i = 0;
// 	result = 0;
// 	sign = 1;
// 	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
// 		i++;
// 	if (nptr[i] == '+')
// 	{
// 		sign = 1;
// 		i++;
// 	}
// 	else if (nptr [i] == '-')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		result = result * 10 + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (result * sign);
// }

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

// int ft_isspace(char c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
// }

// size_t	ft_strnlen(const char *str, size_t n)
// {
// 	size_t length;
	
// 	length = 0;
// 	while (length < n && str[length] != '\0')
// 		length++;
// 	return (length);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 	{
// 		len ++;
// 	}
// 	return (len);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	unsigned char	chr;
// 	int				i;

// 	chr = c;
// 	if (chr == '\0')
// 	{
// 		i = ft_strlen(s);
// 		return ((char *)s + i++);
// 	}
// 	while (*s != '\0')
// 	{
// 		if (*s == chr)
// 			return ((char *)s);
// 		s++;
// 	}
// 	return (NULL);
// }
// size_t	ft_strlcat(char *dest, const char *src, size_t size)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	unsigned int	res_d;
// 	unsigned int	res_s;

// 	i = ft_strlen(dest);
// 	j = 0;
// 	res_d = ft_strlen(dest);
// 	res_s = ft_strlen(src);
// 	if (size < 1)
// 		return (res_s + size);
// 	while (src[j] && i < size - 1)
// 	{
// 		dest[i] = src[j];
// 		i++;
// 		j++;
// 	}
// 	dest[i] = '\0';
// 	if (size < res_d)
// 		return (res_s + size);
// 	else
// 		return (res_d + res_s);
// }

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (!little || ft_strlen(little) == 0 || !big)
// 		return ((char *)big);
// 	i = 0;
// 	while (big[i] && i < len)
// 	{
// 		if (big[i] == little[0])
// 		{
// 			j = 0;
// 			while (big[i + j] == little[j] && (i + j) < len)
// 				j++;
// 			if (j == ft_strlen(little))
// 				return ((char *)big + i);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// int ft_is_delimiter(char c)
// {
// 	if (c == '$')
// 	{
// 		return 1;
// 	}
// 	if (c == '|' || c == '>' || c == '<')
// 	{
// 		return 1;
// 	}
// 	if (c == '\'' || c == '"')
// 	{
// 		return 1;
// 	}
// 	return 0;
// }

// char	*ft_strndup(const char *s, size_t n)
// {
// 	size_t len;
// 	char *new_str;

// 	len = ft_strnlen(s, n);
// 	new_str = malloc(len + 1);
// 	if (!new_str)
// 		return NULL; 
// 	ft_strncpy(new_str, s, len);       
// 	new_str[len] = '\0';        
// 	return (new_str);
// }

// size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
// 	size_t		i;
// 	size_t		src_len;

// 	src_len = ft_strlen(src);
// 	if (size == 0)
// 		return (src_len);
// 	i = 0;
// 	while (src[i] && i < size - 1)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (src_len);
// }

// int	ft_strcmp(char *s1, const char *s2)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0')
// 		i++;
// 	return (s1[i] - s2[i]);
// }

// int	ft_isalpha(int c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	else
// 		return (0);
// }

// int	ft_isalnum(int c)
// {
// 	if (ft_isalpha(c) || ft_isdigit(c))
// 		return (c);
// 	return (0);
// }
// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*d;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	d = (char *) malloc ((i + 1) * sizeof (char));
// 	if (!d)
// 		return (0);
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	d[i] = '\0';
// 	return (d);
// }

// void	free_envp_list(t_env *head)
// {
// 	t_env *current;
	
// 	while (head)
// 	{
// 		current = head->next;
// 		free(head->key);
// 		free(head->value);
// 		free(head);
// 		head = current;
// 	}
// }
// char	*get_env(t_env *head, const char *key)
// {
// 	while (head)
// 	{
// 		if (ft_strcmp(head->key, key) == 0) 
// 			return head->value;
// 		head = head->next;
// 	}
// 	return NULL;
// }

// int	set_env(t_env **head, const char *key, const char *value)
// {
// 	t_env *current;
// 	t_env *new_node;

// 	current = *head;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0) {
// 			free(current->value);
// 			current->value = ft_strdup(value);
// 			return (0);
// 		}
// 		current = current->next;
// 	}
// 	new_node = create_envp_node((char *)key, (char *)value);
// 	if (!new_node)
// 		return (-1);
// 	new_node->next = *head;
// 	*head = new_node;
// 	return (0);
// }

// int	unset_env(t_env **head, const char *key)
// {
// 	t_env *current;
// 	t_env *previous;

// 	current = *head;
// 	previous = NULL;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 		{
// 			if (previous) 
// 				previous->next = current->next;
// 			else
// 				*head = current->next;
// 			free(current->key);
// 			free(current->value);
// 			free(current);
// 			return (0);
// 		}
// 		previous = current;
// 		current = current->next;
// 	}
// 	return (-1);
// }

// t_env	*create_envp_node(char *key, char *value)
// {
// 	t_env	*new_node;

// 	new_node = (t_env *)malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->key = ft_strdup(key);
// 	new_node->value = ft_strdup(value);
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void	split_envp(char *envp_str, char **key, char **value)
// {
// 	char	*equal_sign;

// 	equal_sign = ft_strchr(envp_str, '=');
// 	if (equal_sign)
// 	{
// 		*key = ft_strndup(envp_str, equal_sign - envp_str);
// 		*value = ft_strdup(equal_sign + 1);
// 	}
// 	else
// 	{
// 		*key = ft_strdup(envp_str);
// 		*value = NULL;
// 	}
// }

// t_env	*create_envp_list_node(char *envp_str)
// {
// 	char	*key;
// 	char	*value;
// 	t_env	*new_node;

// 	split_envp(envp_str, &key, &value);
// 	new_node = create_envp_node(key, value);
// 	free(key);
// 	free(value);
// 	return (new_node);
// }

// void	add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node)
// {
// 	if (!*head)
// 		*head = new_node;
// 	else
// 		(*current)->next = new_node;
// 	*current = new_node;
// }

// t_env	*init_copy_envp_to_list(char **envp)
// {
// 	t_env	*head;
// 	t_env	*current;
// 	t_env	*new_node;
// 	char *UID;
// 	pid_t uid;

// 	uid = ft_getuid();
// 	UID = ft_itoa((int)uid);
// 	head = NULL;
// 	current = NULL;
// 	while (*envp)
// 	{
// 		new_node = create_envp_list_node(*envp);
// 		if (!new_node)
// 			free_envp_list(head);
// 		add_node_to_envp_list(&head, &current, new_node);
// 		envp++;
// 	}
// 	if (set_env(&head, "UID", UID) != 0)
//     {
//         free_envp_list(head);
//         return NULL;
//     }
// 	free(UID);
// 	return (head);
// }

// char	*read_pid_line(int fd)
// {
// 	static char	buffer[256];
// 	ssize_t		bytesRead;

// 	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
// 	if (bytesRead <= 0) 
// 		return (NULL);
// 	buffer[bytesRead] = '\0';
// 	return (strstr(buffer, "Pid:"));
// }

// pid_t	ft_getpid()
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("/proc/self/status", O_RDONLY);
// 	if (fd == -1) {
// 		perror("open");
// 		return (-1);
// 	}
// 	line = read_pid_line(fd);
// 	close(fd);
// 	if (line != NULL)
// 		return ((pid_t)ft_atoi(line + 4));
// 	else
// 		return (-1);
// }


// // void replace_dollar_dollar(char **input, char *old, char *new)
// // {
// // 	char *new_input;
// // 	char *pos;
// // 	int old_len;
// // 	int new_len;
// // 	int input_len;

// //     if (!new)
// //         return;
// //     pos = ft_strnstr(*input, old, ft_strlen(*input));
// //     if (!pos)
// //         return;
// //     old_len = ft_strlen(old);
// //     new_len = ft_strlen(new);
// //     input_len = ft_strlen(*input);
// //     new_input = malloc(input_len - old_len + new_len + 1);
// //     if (!new_input)
// //         return;
// //     ft_strlcpy(new_input, *input, pos - *input + 1);
// //     ft_strlcat(new_input, new, (pos - *input) + new_len + 1);
// //     ft_strlcat(new_input, pos + old_len, input_len - old_len + new_len + 1);
// //     free(*input);
// //     *input = new_input;
// // }

// // char *handle_double_dollar(char *input)
// // {
// //     char *pos;
// //     char *pid_str;
// //     pid_t pid;

// //     pid = ft_getpid();
// //     pid_str = ft_itoa(pid);
// //     while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
// //         replace_dollar_dollar(&input, "$$", pid_str);
// //     free(pid_str);
// //     return input;
// // }
// // Function to remove all occurrences of a specific character from a string
// // char *remove_char(char *str, char char_to_remove)
// // {
// // 	int len;
// // 	char *result;
// // 	char *ptr;
// // 	int i;

// //     if (!str)
// //         return NULL;
// //     len = strlen(str);
// //     result = malloc(len + 1);
// //     if (!result)
// //         return NULL;
// //     ptr = result;
// //     i = 0;
// //     while (i < len)
// //     {
// //         if (ft_isspace(str[i + 1]) && str[i] == char_to_remove)
// //         {
// //             *ptr++ = str[i++];
// //             *ptr++ = str[i++];
// //         }
// //         else if (str[i] != char_to_remove)
// //             *ptr++ = str[i++];
// //         else if (str[i] == char_to_remove && str[i + 1] == '\0')
// //             *ptr++ = str[i++];
// //         else
// //             i++;
// //     }
// //     *ptr = '\0';
// //     return result;
// // }

// // char *remove_char(char *str, char char_to_remove)
// // {
// //     int len;
// //     char *result;
// //     char *ptr;
// //     int i;

// //     if (!str)
// //         return NULL;
    
// //     result = malloc(strlen(str) + 1);
// //     if (!result)
// //         return NULL;

// //     ptr = result;
// //     for (i = 0; str[i]; i++)
// //     {
// //         if (str[i] != char_to_remove || (ft_isspace(str[i + 1]) || str[i + 1] == '\0'))
// //             *ptr++ = str[i];
// //     }
    
// //     *ptr = '\0';
// //     return result;
// // }


// char	*ft_strjoin(char *s1, char const *s2)
// {
// 	size_t	len1;
// 	size_t	len2;
// 	size_t	i;
// 	size_t	j;
// 	char	*result;

// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	if (!s1 || !s2)
// 		return (NULL);
// 	result = (char *)malloc(len1 + len2 + 1);
// 	if (!result)
// 		return (NULL);
// 	i = -1;
// 	while (s1[++i])
// 		result[i] = s1[i];
// 	j = 0;
// 	while (s2[j])
// 	{
// 		result[i + j] = s2[j];
// 		j++;
// 	}
// 	result[i + j] = '\0';
// 	free(s1);
// 	return (result);
// }

// // char *strjoin_free(char *s1, const char *s2)
// // {
// //     char *joined = ft_strjoin(s1, s2);  // Join the two strings
// //     //free(s1);  // Free the old string
// //     return joined;
// // }



// // // Function to parse and replace environment variables
// // char *handle_dollar_sign(char *input, t_env *envp_head)
// // {
// //     int		i;
// //     int		start;
// // 	int		end;
// //     char	*sub_env;
// //     char	*result;
// // 	char	*env_value;
// // 	char	tmp[2];
	
// // 	i = 0;
// // 	result = strdup("");
// //     input = handle_double_dollar(input);
// //     while (input[i])
// //     {
// //         if (input[i] == '$')
// //         {
// //             if (ft_isdigit(input[i + 1]))
// //             {
// //                 i += 2;  // Skip the $ and digit
// //                 continue;
// //             }
// //             i++;
// //             start = i;
// //             while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
// //                 i++;
// //             end = i;

// //             if (start != end)  // If a valid variable name was found
// //             {
// //                 sub_env = ft_substr(input, start, end - start);
// //                 env_value = get_env(envp_head, sub_env);
// //                 if (env_value)
// //                     result = ft_strjoin(result, env_value);  // Append the env value to result
// //                 free(sub_env);
// //             }
// //             else
// //                 result = ft_strjoin(result, "$");
// //         }
// //         else
// //         {
// //             tmp[0] = input[i];
// //             tmp[1] = '\0';
// //             result = ft_strjoin(result, tmp);
// //             i++;
// //         }
// //     }
// //     return (result);
// // }

// void handle_normal_variable(char *input, int *i, char **result, t_env *env)
// {
// 	int start;
// 	int end;
// 	char *sub_env;
// 	char *env_value;

// 	(*i)++;
// 	start = *i;
// 	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
// 		(*i)++;
// 	end = *i;
// 	if (start != end)
// 	{
// 		sub_env = ft_substr(input, start, end - start);
//         env_value = get_env(env, sub_env);
//         if (env_value)
//             *result = ft_strjoin(*result, env_value);
//         free(sub_env);
// 	}
// 	else
//         *result = ft_strjoin(*result, "$");
// }

// void	handle_two_dollar(char **result, int *i)
// {
// 	char	*num_str;
// 	//char	*temp;

// 	num_str = ft_itoa(getpid());
// 	//temp = *result;
// 	*result = ft_strjoin(*result, num_str);
// 	//free(temp);
// 	*i += 2; // Move past the $$ symbols
// 	free(num_str);
// }

// char	*handle_dollar_sign(char *input, t_env *env)
// {
// 	int		i;
// 	char	*result;
// 	char	tmp[2];
// 	//char	*temp;
// 	//free(temp);
// 	i = 0;
// 	result = ft_strdup("");
// 	while (i < ft_strlen(input) && input[i])
// 		if (input[i] == '$')
// 		{
// 			// if (input[i + 1] == '?')
// 				// handle_exit..
// 			if (input[i + 1] == '$')
// 				handle_two_dollar(&result, &i);
// 			else if (ft_isdigit(input[i + 1]))
// 				i += 2;
// 			else
// 				handle_normal_variable(input, &i, &result, env);
// 		}
// 		else
// 		{
// 			ft_strlcpy(tmp, input + i, 2);
// 			result = ft_strjoin(result, tmp);
// 			i++;
// 		}
// 	return (result);
// }





// int main(int argc, char **argv, char **envp)
// {
//     // Step 1: Initialize the environment variable list from envp
//     t_env *envp_list = init_copy_envp_to_list(envp);

//     // Step 2: Start a readline loop to process user input
//     char *input;
//     while ((input = readline("minishell> ")) != NULL)
//     {
//         // Add input to history
//         add_history(input);

//         // If the user types "exit", break the loop
//         if (strcmp(input, "exit") == 0)
//         {
//             free(input);
//             break;
//         }

//         // Process the input string
//         char *processed_input = handle_dollar_sign(input, envp_list);

//         // Print the final output
//         printf("Processed Input: %s\n", processed_input);

//         // Clean up for this iteration
//         free(processed_input);
//         //free(input);
//     }

//     // Step 3: Clean up before exiting
//     free_envp_list(envp_list);

//     return 0;
// }


#include "includes/minishell.h"


size_t	ft_strnlen(const char *str, size_t n)
{
	size_t length;
	
	length = 0;
	while (length < n && str[length] != '\0')
		length++;
	return (length);
}
char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = 0;
	while (s[i] != '\0')
		i++;
	d = (char *) malloc ((i + 1) * sizeof (char));
	if (!d)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}


char	*ft_strndup(const char *s, size_t n)
{
	size_t len;
	char *new_str;

	len = ft_strnlen(s, n);
	new_str = malloc(len + 1);
	if (!new_str)
		return NULL; 
	ft_strncpy(new_str, s, len);       
	new_str[len] = '\0';
	return (new_str);
}
int ft_is_delimiter(char c)
{
    if (c == '$')
    {
        return 1;
    }
    if (c == '|' || c == '>' || c == '<')
    {
        return 1;
    }
    if (c == '\'' || c == '"')
    {
        return 1;
    }
    return 0;
}



int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_skip_whitespace(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

char	*ft_strncpy(char *dest, const char *src, size_t n) 
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (src[i] != '\0') 
			dest[i] = src[i];
		else
			dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_ptr;

	dest_ptr = dest;
	while (*src)
		*dest_ptr++ = *src++;
	*dest_ptr = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_ptr;

	dest_ptr = dest;
	while (*dest_ptr)
		dest_ptr++;
	while (*src)
		*dest_ptr++ = *src++;
	*dest_ptr = '\0';
	return (dest);
}


// Convert token type to string
const char *token_type_to_string(t_tokens_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return "TOKEN_WORD";
	case TOKEN_PIPE:
		return "TOKEN_PIPE";
	case TOKEN_REDIRECT_IN:
		return "TOKEN_REDIRECT_IN";
	case TOKEN_REDIRECT_OUT:
		return "TOKEN_REDIRECT_OUT";
	case TOKEN_APPEND:
		return "TOKEN_APPEND";
	case TOKEN_HEREDOC:
		return "TOKEN_HEREDOC";
	case TOKEN_ERROR:
		return "TOKEN_ERROR";
	default:
		return "UNKNOWN";
	}
}

char	*process_quoted_string(char **input, char quote_type, bool *space)
{
	char *start; // Skip the opening quote
	char *end;
	char *result;
	size_t len;

	start = ++(*input);
	*space = true;
	// non gere
	while (**input && **input != quote_type)
	{
		if (**input == '\\' && (*(*input + 1) == quote_type || *(*input + 1) == '\\'))
			(*input)++;
		(*input)++;
	}
	end = *input;
	
	// if (**input == quote_type)
	// {
	// 	(*input)++; // Skip closing quote
	// }
	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return NULL;
	ft_strncpy(result, start, len);
	result[len] = '\0';

	(void)space;
	 if (*(*input + 1) && !ft_isspace(*(*input + 1)) && *(*input + 1) != '>' && *(*input + 1) != '<' && *(*input + 1) != '|')
	 	*space = false;
	// start = result;
	// free(result);
	return (result);
}

const char *quote_type_to_string(t_quote_type quote_type)
{
	switch (quote_type)
	{
	case DOUBLE_QUOTE:
		return "DOUBLE_QUOTE";
	case SINGLE_QUOTE:
		return "SINGLE_QUOTE";
	default:
		return "NO_QUOTE";
	}
}


static void handle_pipe_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char *pipe;

	pipe = ft_strdup("|");
	new_token = create_token_node(TOKEN_PIPE, NO_QUOTE, pipe, true);
	if (!new_token)
	{
		free(pipe);
		return;
	}

	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle redirection tokens
static void handle_redirection_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char redirect_char;
	size_t len;

	len = 1;
	redirect_char = **current;
	if (*(*current + 1) == redirect_char)
	{
		len++;
		(*current)++;
	}
	new_token = create_token_node(
		(len == 2) ? (redirect_char == '<' ? TOKEN_HEREDOC : TOKEN_APPEND) : (redirect_char == '<' ? TOKEN_REDIRECT_IN : TOKEN_REDIRECT_OUT),
		NO_QUOTE,
		ft_strndup(*current - len + 1, len),
		true);
	if (!new_token)
		return;

	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle quoted string tokens
static void handle_quoted_string_token(char **current, t_list_tokens **tokens)
{
	char quote_type;
	char *quoted_string;
	t_list_tokens *new_token;
	bool space;

	quote_type = **current;
	quoted_string = process_quoted_string(current, quote_type, &space);
	if (!quoted_string)
		return;

	new_token = create_token_node(
		TOKEN_WORD,
		(quote_type == '"') ? DOUBLE_QUOTE : SINGLE_QUOTE,
		quoted_string,
		space);
	if (!new_token)
	{
		free(quoted_string);
		return;
	}
	// free(quoted_string);
	append_token(tokens, new_token);
	(*current)++;
}


static void handle_unquoted_word_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char *start;
	char *value;
	char *val_dup;
	bool space;

	start = *current;
	while (**current && !ft_isspace(**current) && **current != '|' &&
		   **current != '<' && **current != '>' && **current != '"' && **current != '\'')
		(*current)++;
	if (*current > start)
	{
		space = !(*(*current) && (*(*current) == '\'' || *(*current) == '"'));
		value = ft_strndup(start, *current - start);
		if (!value) // Check if memory allocation failed
			return;
		val_dup = ft_strdup(value);
		new_token = create_token_node(TOKEN_WORD, NO_QUOTE, val_dup, space);
		if (!new_token)
			return (free(value), (void)0);
		(append_token(tokens, new_token), free(value));
	}
}

// Tokenize the input string into tokens
void tokenize(char *input, t_list_tokens **tokens)
{
	char *current;

	current = input;
	while (*current)
	{
		while (ft_isspace(*current))
			current++;
		if (*current == '|')
		{
			handle_pipe_token(&current, tokens);
			continue;
		}
		if (*current == '<' || *current == '>')
		{
			handle_redirection_token(&current, tokens);
			continue;
		}
		if (*current == '"' || *current == '\'')
		{
			handle_quoted_string_token(&current, tokens);
			continue;
		}
		handle_unquoted_word_token(&current, tokens);
	}
}
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+
// +_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+

int is_redirector(int type) {
    return (type == TOKEN_REDIRECT_IN || 
            type == TOKEN_HEREDOC || 
            type == TOKEN_REDIRECT_OUT || 
            type == TOKEN_APPEND);
}

// Create a new token node
t_list_tokens *create_token_node(t_tokens_type type, t_quote_type quote_type, char *value, bool space) {
    t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
    if (!new_token) return NULL;
    new_token->type = type;
    new_token->quote_type = quote_type;
    new_token->value = ft_strdup(value);
    new_token->space = space;
    new_token->next = NULL;
    return new_token;
}

// Remove a token from the token list
t_list_tokens	*remove_token(t_list_tokens **tokens_list, t_list_tokens *token)
{
	t_list_tokens *current;

	current = *tokens_list;
	if (current == token)
	{
		*tokens_list = token->next;
		free(token->value);
		free(token);
		return (*tokens_list);
	}
	while (current && current->next != token)
		current = current->next;
	if (current && current->next == token)
	{
		current->next = token->next;
		free(token->value);
		free(token);
	}
	return (current ? current->next : NULL);
}

// Append a token to the end of the token list
void append_token(t_list_tokens **tokens, t_list_tokens *new_token) {
    t_list_tokens *last = *tokens;
    if (!last) {
        *tokens = new_token;
        return;
    }
    while (last->next) {
        last = last->next;
    }
    last->next = new_token;
}

// Append a command node to the command list
void append_cmd_node(t_cmd **cmd_list, t_cmd *new_cmd) {
    t_cmd *last = *cmd_list;
    if (!last) {
        *cmd_list = new_cmd;
        return;
    }
    while (last->next) {
        last = last->next;
    }
    last->next = new_cmd;  // Append the new command
}

// Create a new command node
t_cmd *create_cmd_node(t_list_tokens *tokens_list) {
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd) return NULL; // Handle malloc failure
    new_cmd->tokens_list = tokens_list;
    new_cmd->list_redirectors = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}


void split_tokens_by_pipe(t_list_tokens *tokens_list, t_cmd **cmd_list)
{
    t_list_tokens	*current_token;
    t_list_tokens	*command_start;
    t_list_tokens	*previous_token;
	t_list_tokens	*next_command;
	t_cmd			*new_cmd;

	current_token = tokens_list;
	command_start = tokens_list;
	previous_token = NULL;
    while (current_token)
	{
        if (current_token->type == TOKEN_PIPE)
		{
            // Temporarily break the link at the pipe
            next_command = current_token->next;
            // If there's a previous token, it should point to NULL to end the current command
            if (previous_token) {
                previous_token->next = NULL;
            }
            // Create a new command node for the current command
            new_cmd = create_cmd_node(command_start);
            append_cmd_node(cmd_list, new_cmd);
            // Move to the next command after the pipe
            command_start = next_command;
            current_token = next_command->next;
        } else
		{
            previous_token = current_token;
            current_token = current_token->next;
        }
    }
    // Add the last command as a command node if there is one
    if (command_start)
	{
        t_cmd *new_cmd = create_cmd_node(command_start);
        append_cmd_node(cmd_list, new_cmd);
    }
}




// Parse all redirections for each command in the command list
void	parse_all_redirections(t_cmd *cmd_list)
{
    t_cmd			*current_cmd;
	t_list_tokens	*token;
	t_list_tokens	*file_token;
	t_list_tokens	*redir_node;
	t_list_tokens	*file_node;
	
	current_cmd = cmd_list;
    while (current_cmd)
	{
        token = current_cmd->tokens_list;
        while (token)
		{
            if (is_redirector(token->type)) {
                file_token = token->next;
                if (!file_token)
				{
                    printf("Syntax error: expected a file after redirector.\n");
                    break;
                }
                // Create new nodes for the redirector and its associated file
				redir_node = create_token_node(token->type, NO_QUOTE, token->value, false);
				file_node = create_token_node(file_token->type, file_token->quote_type, file_token->value, file_token->space);
            
	            // Append them to the redirectors list in the current command node
	            append_token(&(current_cmd->list_redirectors), redir_node);
	            append_token(&(current_cmd->list_redirectors), file_node);

	            // Remove the redirector and its associated file from the tokens list
	            token = remove_token(&(current_cmd->tokens_list), token);     // Remove redirector
	            token = remove_token(&(current_cmd->tokens_list), file_token); // Remove associated file
	        } else 
	            token = token->next;
	    }
	    // Move to the next command node
	    current_cmd = current_cmd->next;
	}
}

// Function to print the token list
void print_tokens_list(t_list_tokens *tokens_list) {
    t_list_tokens *current = tokens_list;
    while (current) {
        printf("Token: type=%d, value=%s\n", current->type, current->value);
        current = current->next;
    }
}

// Function to print the command list
void print_cmd_list(t_cmd *cmd_list) {
    t_cmd *current_cmd = cmd_list;
    int cmd_index = 1;

    while (current_cmd) {
        printf("Command Node %d:\n", cmd_index);
        printf("Tokens List:\n");
        print_tokens_list(current_cmd->tokens_list);
        printf("Redirectors List:\n");
        print_tokens_list(current_cmd->list_redirectors);
        printf("\n");

        current_cmd = current_cmd->next;
        cmd_index++;
    }
}

void free_parser_list(t_cmd *parser_list) {
    t_cmd *current;
    t_cmd *next;

    current = parser_list;
    while (current != NULL) {
        next = current->next;

        // Free the tokens list
        t_list_tokens *token_current = current->tokens_list;
        t_list_tokens *token_next;
        while (token_current != NULL) {
            token_next = token_current->next;
            free(token_current->value);
            free(token_current);
            token_current = token_next;
        }

        // Free the redirections list
        t_list_tokens *redir_current = current->list_redirectors;
        t_list_tokens *redir_next;
        while (redir_current != NULL) {
            redir_next = redir_current->next;
            free(redir_current->value);
            free(redir_current);
            redir_current = redir_next;
        }

        // Free the parser node itself
        free(current);

        current = next;
    }
}


// Main function
int main() {
    char *input;
    t_list_tokens *tokens_list = NULL;
    t_cmd *cmd_list = NULL;

    while ((input = readline("minishell> ")) != NULL) {
        if (*input == '\0') {
            free(input);
            continue;
        }
        add_history(input);

        tokenize(input, &tokens_list);

        // Split the tokens by pipes and create command nodes
        split_tokens_by_pipe(tokens_list, &cmd_list);

        // Parse redirections for all command nodes
        parse_all_redirections(cmd_list);

        // Print the command list to check the results
        print_cmd_list(cmd_list);

        // Free the input string
        free(input);

        // Free the command list and tokens_list if needed
        // free_cmd_list(cmd_list);
        // cmd_list = NULL;
		free_parser_list(cmd_list);
		cmd_list = NULL;
    }
    return 0;
}



//ls -l > file | ahmad | farachi << heredoc | echo "ahmad" | cat -e > file