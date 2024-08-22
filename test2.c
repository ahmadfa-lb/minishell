
#include "includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


ssize_t read_status_file(char *buffer, size_t size)
{
    int fd = open("/proc/self/status", O_RDONLY);
    ssize_t bytesRead = -1;
    if (fd != -1)
    {
        bytesRead = read(fd, buffer, size - 1);
        close(fd);
    }
    return (bytesRead);
}

pid_t ft_getuid()
{
    char buffer[256];
    ssize_t bytesRead;
    char *uid_line;
    pid_t uid = -1;

    bytesRead = read_status_file(buffer, sizeof(buffer));
    if (bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        uid_line = ft_strstr(buffer, "Uid:");
        if (uid_line)
        {
            uid_line = ft_strchr(uid_line, '\t');
            if (uid_line)
                uid = ft_atoi(uid_line + 1);
        }
    }
    return (uid);
}

int	get_int_length(int n)
{
	int		length;
	bool	is_negative;

	length = 0;
	is_negative = n < 0;
	if (n == 0)
		return (1);
	if (is_negative)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	if (is_negative)
		return (length + 1);
	else
		return (length);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*original_dest;
	int		i;

	original_dest = dest;
	i = 0;
	while (src[i])
	{
		dest[i] = src [i];
		i++;
	}
	original_dest[i] = '\0';
	return (original_dest);
}

int	get_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*nb;
	int		len;

	len = get_len(n);
	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	n = n * sign;
	nb = (char *)malloc((len + 1) * sizeof(char));
	if (!nb)
		return (NULL);
	nb[len--] = '\0';
	while (len >= 0)
	{
		nb[len--] = '0' + (n % 10);
		n = n / 10;
	}
	if (sign == -1)
		nb[0] = '-';
	return (nb);
}

char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (needle[0] == '\0')
		return (haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
		{
			if (needle[j + 1] == '\0')
				return (&haystack[i]);
			j++;
		}
		i++;
	}
	return (0);
}

size_t	check_len(size_t s_len, unsigned int start, size_t len)
{
	size_t	mlen;

	mlen = s_len - (size_t)start;
	if (mlen > len)
		mlen = len;
	return (mlen);
}

char	*check_alloc(size_t max_len)
{
	char	*s_str;

	s_str = (char *)malloc(max_len + 1);
	if (s_str == NULL)
		return (NULL);
	return (s_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	max_len;
	char	*sub_str;
	char	*empty_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		empty_str = ft_strdup("");
		return (empty_str);
	}
	max_len = check_len(s_len, start, len);
	sub_str = check_alloc(max_len);
	i = 0;
	while (i < max_len && s[start + i] != '\0')
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
	{
		sign = 1;
		i++;
	}
	else if (nptr [i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t length;
	
	length = 0;
	while (length < n && str[length] != '\0')
		length++;
	return (length);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len ++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	chr;
	int				i;

	chr = c;
	if (chr == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	while (*s != '\0')
	{
		if (*s == chr)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	res_d;
	unsigned int	res_s;

	i = ft_strlen(dest);
	j = 0;
	res_d = ft_strlen(dest);
	res_s = ft_strlen(src);
	if (size < 1)
		return (res_s + size);
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (size < res_d)
		return (res_s + size);
	else
		return (res_d + res_s);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little || ft_strlen(little) == 0 || !big)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && (i + j) < len)
				j++;
			if (j == ft_strlen(little))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

int	ft_strcmp(char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (c);
	return (0);
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

void	free_envp_list(t_env *head)
{
	t_env *current;
	
	while (head)
	{
		current = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = current;
	}
}
char	*get_env(t_env *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0) 
			return head->value;
		head = head->next;
	}
	return NULL;
}

int	set_env(t_env **head, const char *key, const char *value)
{
	t_env *current;
	t_env *new_node;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0) {
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	new_node = create_envp_node((char *)key, (char *)value);
	if (!new_node)
		return (-1);
	new_node->next = *head;
	*head = new_node;
	return (0);
}

int	unset_env(t_env **head, const char *key)
{
	t_env *current;
	t_env *previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous) 
				previous->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (-1);
}

t_env	*create_envp_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	split_envp(char *envp_str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp_str, '=');
	if (equal_sign)
	{
		*key = ft_strndup(envp_str, equal_sign - envp_str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(envp_str);
		*value = NULL;
	}
}

t_env	*create_envp_list_node(char *envp_str)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	split_envp(envp_str, &key, &value);
	new_node = create_envp_node(key, value);
	free(key);
	free(value);
	return (new_node);
}

void	add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

t_env	*init_copy_envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	char *UID;
	pid_t uid;

	uid = ft_getuid();
	UID = ft_itoa((int)uid);
	head = NULL;
	current = NULL;
	while (*envp)
	{
		new_node = create_envp_list_node(*envp);
		if (!new_node)
			free_envp_list(head);
		add_node_to_envp_list(&head, &current, new_node);
		envp++;
	}
	if (set_env(&head, "UID", UID) != 0)
    {
        free_envp_list(head);
        return NULL;
    }
	free(UID);
	return (head);
}

char	*read_pid_line(int fd)
{
	static char	buffer[256];
	ssize_t		bytesRead;

	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead <= 0) 
		return (NULL);
	buffer[bytesRead] = '\0';
	return (strstr(buffer, "Pid:"));
}

pid_t	ft_getpid()
{
	int		fd;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return (-1);
	}
	line = read_pid_line(fd);
	close(fd);
	if (line != NULL)
		return ((pid_t)ft_atoi(line + 4));
	else
		return (-1);
}


// void replace_dollar_dollar(char **input, char *old, char *new)
// {
// 	char *new_input;
// 	char *pos;
// 	int old_len;
// 	int new_len;
// 	int input_len;

//     if (!new)
//         return;
//     pos = ft_strnstr(*input, old, ft_strlen(*input));
//     if (!pos)
//         return;
//     old_len = ft_strlen(old);
//     new_len = ft_strlen(new);
//     input_len = ft_strlen(*input);
//     new_input = malloc(input_len - old_len + new_len + 1);
//     if (!new_input)
//         return;
//     ft_strlcpy(new_input, *input, pos - *input + 1);
//     ft_strlcat(new_input, new, (pos - *input) + new_len + 1);
//     ft_strlcat(new_input, pos + old_len, input_len - old_len + new_len + 1);
//     free(*input);
//     *input = new_input;
// }

// char *handle_double_dollar(char *input)
// {
//     char *pos;
//     char *pid_str;
//     pid_t pid;

//     pid = ft_getpid();
//     pid_str = ft_itoa(pid);
//     while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
//         replace_dollar_dollar(&input, "$$", pid_str);
//     free(pid_str);
//     return input;
// }
// Function to remove all occurrences of a specific character from a string
// char *remove_char(char *str, char char_to_remove)
// {
// 	int len;
// 	char *result;
// 	char *ptr;
// 	int i;

//     if (!str)
//         return NULL;
//     len = strlen(str);
//     result = malloc(len + 1);
//     if (!result)
//         return NULL;
//     ptr = result;
//     i = 0;
//     while (i < len)
//     {
//         if (ft_isspace(str[i + 1]) && str[i] == char_to_remove)
//         {
//             *ptr++ = str[i++];
//             *ptr++ = str[i++];
//         }
//         else if (str[i] != char_to_remove)
//             *ptr++ = str[i++];
//         else if (str[i] == char_to_remove && str[i + 1] == '\0')
//             *ptr++ = str[i++];
//         else
//             i++;
//     }
//     *ptr = '\0';
//     return result;
// }

// char *remove_char(char *str, char char_to_remove)
// {
//     int len;
//     char *result;
//     char *ptr;
//     int i;

//     if (!str)
//         return NULL;
    
//     result = malloc(strlen(str) + 1);
//     if (!result)
//         return NULL;

//     ptr = result;
//     for (i = 0; str[i]; i++)
//     {
//         if (str[i] != char_to_remove || (ft_isspace(str[i + 1]) || str[i + 1] == '\0'))
//             *ptr++ = str[i];
//     }
    
//     *ptr = '\0';
//     return result;
// }


char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

// char *strjoin_free(char *s1, const char *s2)
// {
//     char *joined = ft_strjoin(s1, s2);  // Join the two strings
//     //free(s1);  // Free the old string
//     return joined;
// }



// // Function to parse and replace environment variables
// char *handle_dollar_sign(char *input, t_env *envp_head)
// {
//     int		i;
//     int		start;
// 	int		end;
//     char	*sub_env;
//     char	*result;
// 	char	*env_value;
// 	char	tmp[2];
	
// 	i = 0;
// 	result = strdup("");
//     input = handle_double_dollar(input);
//     while (input[i])
//     {
//         if (input[i] == '$')
//         {
//             if (ft_isdigit(input[i + 1]))
//             {
//                 i += 2;  // Skip the $ and digit
//                 continue;
//             }
//             i++;
//             start = i;
//             while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
//                 i++;
//             end = i;

//             if (start != end)  // If a valid variable name was found
//             {
//                 sub_env = ft_substr(input, start, end - start);
//                 env_value = get_env(envp_head, sub_env);
//                 if (env_value)
//                     result = ft_strjoin(result, env_value);  // Append the env value to result
//                 free(sub_env);
//             }
//             else
//                 result = ft_strjoin(result, "$");
//         }
//         else
//         {
//             tmp[0] = input[i];
//             tmp[1] = '\0';
//             result = ft_strjoin(result, tmp);
//             i++;
//         }
//     }
//     return (result);
// }

void handle_normal_variable(char *input, int *i, char **result, t_env *env)
{
	int start;
	int end;
	char *sub_env;
	char *env_value;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	end = *i;
	if (start != end)
	{
		sub_env = ft_substr(input, start, end - start);
        env_value = get_env(env, sub_env);
        if (env_value)
            *result = ft_strjoin(*result, env_value);
        free(sub_env);
	}
	else
        *result = ft_strjoin(*result, "$");
}

void	handle_two_dollar(char **result, int *i)
{
	char	*num_str;
	//char	*temp;

	num_str = ft_itoa(getpid());
	//temp = *result;
	*result = ft_strjoin(*result, num_str);
	//free(temp);
	*i += 2; // Move past the $$ symbols
	free(num_str);
}

char	*handle_dollar_sign(char *input, t_env *env)
{
	int		i;
	char	*result;
	char	tmp[2];
	//char	*temp;
	//free(temp);
	i = 0;
	result = ft_strdup("");
	while (i < ft_strlen(input) && input[i])
		if (input[i] == '$')
		{
			// if (input[i + 1] == '?')
				// handle_exit..
			if (input[i + 1] == '$')
				handle_two_dollar(&result, &i);
			else if (ft_isdigit(input[i + 1]))
				i += 2;
			else
				handle_normal_variable(input, &i, &result, env);
		}
		else
		{
			ft_strlcpy(tmp, input + i, 2);
			result = ft_strjoin(result, tmp);
			i++;
		}
	return (result);
}





int main(int argc, char **argv, char **envp)
{
    // Step 1: Initialize the environment variable list from envp
    t_env *envp_list = init_copy_envp_to_list(envp);

    // Step 2: Start a readline loop to process user input
    char *input;
    while ((input = readline("minishell> ")) != NULL)
    {
        // Add input to history
        add_history(input);

        // If the user types "exit", break the loop
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }

        // Process the input string
        char *processed_input = handle_dollar_sign(input, envp_list);

        // Print the final output
        printf("Processed Input: %s\n", processed_input);

        // Clean up for this iteration
        free(processed_input);
        //free(input);
    }

    // Step 3: Clean up before exiting
    free_envp_list(envp_list);

    return 0;
}