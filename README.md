# get_next_line

A function that reads a text file (or any file descriptor) line by line, one call at a time. This is a project from the 42 core curriculum.

## 📋 Description

**get_next_line** returns the next line of a file each time it is called, without re-reading the whole file from the start. It uses a static variable to keep track of what has already been read but not yet returned, and reads the file descriptor in chunks of `BUFFER_SIZE` bytes.

## 🛠️ Build

There is no Makefile provided — compile the sources directly with your project, defining `BUFFER_SIZE` if you want to override the default:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o main
```

If `BUFFER_SIZE` is not defined at compile time, it defaults to `42` (set in the header).

## 🚀 Usage

Include the header in your source file:

```c
#include "get_next_line.h"
```

Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

## ⚙️ How it works

1. `get_next_line` keeps a `static` buffer (`storage`) between calls, holding whatever has already been read from the file but not yet returned as a line.
2. `ft_read_file` / `ft_read_and_join` read the file descriptor in chunks of `BUFFER_SIZE` bytes and append them to `storage` until a `\n` is found or `read` returns `0`/an error.
3. `ft_extract_line` extracts the next line (up to and including the `\n`, or up to EOF) from `storage` and returns it to the caller.
4. `ft_save_rest` keeps whatever is left in `storage` after the extracted line, ready for the next call, or frees it and resets to `NULL` if nothing remains.
5. If `read` fails, `fd` is invalid, or `BUFFER_SIZE` is invalid, the static buffer is freed and `NULL` is returned.

> Note: this implementation uses a single static variable, so it reads one file descriptor at a time (calling it on a second fd in the middle of reading the first one is not supported).

## 📁 Project structure

```
get_next_line/
├── get_next_line.h         # Main header (prototypes, BUFFER_SIZE)
├── get_next_line.c         # Core reading/extraction logic
├── get_next_line_utils.c   # String helper functions (strlen, strchr, strdup, strjoin, substr)
└── README.md
```

## 📚 Functions

| Function | Description |
|---|---|
| `get_next_line` | Returns the next line read from the given file descriptor |
| `ft_strlen` | Computes the length of a string |
| `ft_strchr` | Locates a character in a string |
| `ft_strdup` | Duplicates a string |
| `ft_strjoin` | Concatenates two strings into a newly allocated one |
| `ft_substr` | Extracts a substring |

## ✅ Norm

The project follows the **42 Norm** (Norminette).
