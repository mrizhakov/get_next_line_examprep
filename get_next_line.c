# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


size_t ft_strlen(char *str)
{
int i = 0;

while(str[i] != '\0')
	i++
	
return (i);
}


// 1. check if char *s doesnt exit(return NULL), or if c == '\0' (return (char *)&s[ft_strlen(s)])
// 2. iterate through char *s until (*s != (char)c) and (*s != '\0')
// 3. if character if *s = (char)c, then return (char *)s
// 4. if not - return (char*)NULL
char *ft_strchr(char *s, int c)
{
if (!s)
	return(NULL);
if (c == '\0')
	return((char*)&s[ft_strlen(s)]);
	
while ((*s != '\0') && (*s != (char)c)
	s++;
if (*s ==(char)c)
	return((char*)s)
return ((char*)NULL));
}

// 1.if s1 dpesnt exits malloc a \0 for it, 
// 2. check if s1 or s2 doesnt exits(ret NULL)
// 3. malloc size of new array (strlen s1+ strlen 2+1, check if malloced or return null
// 4. copy s1 to str, then copy s2 to str, put NULL at the end of str
// 5. free s1 and return str <- special strjoin
char *ft_strjoin(char *s1, char *s2)
{

size_t i = 0;
size_t c = 0;
char *str = NULL;

if (!s1)
{
s1 = (char *)malloc(sizeof(char));
s1[0] = '\0';
}

if (!s1 || !s2)
	return(NULL);
	
str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
if (str == NULL)
	return(NULL);
	
if (s1)
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
while (s2[c] != '\0')
	str[i++] = s2[c++];
str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
free(s1);
return(str);
}

//1. iterate through storage until storage[i] != '\n' and storage[i] exists
//2. mallloc cleaned_storage, size storage - i + 1 
//3. protection for no storage, no cleaned storage of no storage[i] -> free all, return NULL
//4. advance i++ once
//5. while storage[i] exists copy storage[i] to cleaned_storage[j}
//6. free storage, null terminate cleaned_storage and return it

char *clean_storage(char *storage)
{
char	*cleaned_storage;
int	i = 0;
int	j = 0;

while (storage[i] && storage[i] != '\n')
	i++;
cleaned_storage = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
if (!storage || !cleaned_storage || !storage[i])
{
	free(cleaned_storage);
	free(storage);
	return(NULL);
}
i++;
while(storage[i])
	cleaned_storage[j++] = storage[i++];
cleaned_storage[j] = '\0';
free(storage);
return(cleaned_storage);
}


//1. protection in case storage[i] doesnt exist -> return NULL
//2. iterate through storage using i while an new line is not found and  storage[i] still exists
//3. malloc new_line, size is i + 2(for new_line and null terminator), protect malloc
//4. reset i to 0 and iterage through storage again(until not nl or storage[i] exists, copying storage to newline)
//5. if storage[i] is nl, copy it to newline too and advance i
//6. null-terminate new_line and return it
char *return_line(char *storage)
{
char *new_line;
int i = 0;

if (!storage[i])
	return(NULL);
while(storage[i] && storage[i] != '\n')
	i++;
new_line = (char*)malloc(sizeof(char) *(i+2));
if (!new_line)
	return(NULL);
i=0;
while(storage[i] && storage[i] != '\n')
{
	new_line[i] = storage[i];
	i++;
}
if (storage[i] == '\n')
{
	new_line[i] = storage[i];
	i++;
}
new_line[i] = '\0';
return(new_line);
}
// 0. remember that read returns a buffer, but not a string(not \0-terminated)
// 1. malloc buf (BUFFER_SIZE+1), do a protection in case it fails(return NULL)
// 2. loop while you can't find nl in storage and size != 0(eof) 
// 3. loop will read into buf, add \0 to buf[size]m and strjoin to storage = ft_strjoin(storage, buf) <- we are using a modified strjoin which cleans storage
// 4. protection in case size == -1 - free all and return NULL
// 5. free buf and return storage

char *read_storage(char *storage, int fd)
{
size_t size;
char *buf;

size = 1;

buf = malloc(sizeof(char)) * (BUFFER_SIZE + 1));
if (!buf)
	return(NULL);
while (!ft_strchr(storage, '\n') && size != 0)
{
	size = read(fd, buf, BUFFER_SIZE);
	if ((int)size == -1)
	{
		free(buf);
		free(storage);
		return(NULL);
	}
	buf[size] = '\0';
	storage = ft_strjoin(storage, buf);

}
free(buf);
return (storage);
}


//1. check if fd is negative or BUFFER_SIZE is equal or less than 0, then return NULL
//2. save to static char* storage result of read_storage(storage, fd)
//3. if no storage, then return NULL
//4. run return_storage(storage) and save results to char *new_line
//5. run clean_storage(storage) and save results to storage
//6. return new_line

char *get_next_line(int fd)
{
char 		*new_line;
static char	*storage;

if (fd<0 || BUFFER_SIZE <= 0)
	return(NULL);

storage = read_storage(storage, fd);

if (!storage)
	return(NULL);
new_line = return_line(storage);
storage = clean_storage(storage);

return (new_line);
}

int main(void)
{
int fd;
int i;
char *read_bytes;

i = 0;
read_bytes = NULL;
fd = open("dict.txt, O_RDONLY);

while (i != 5)
{
read_bytes = get_next_line(fd);
printf("%s", read_bytes);
free(read_bytes);
i++;
}
close(fd);

return (0);
}

