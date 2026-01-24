*This project has been created as part of the 42 curriculum by adiallo.*

# Get Next Line

## Description

Get Next Line is a project that implements a function to read a line from a file descriptor. The function `get_next_line()` reads from any file descriptor (file, stdin, etc.) and returns one line at a time, including the newline character `\n` when present.

The main goal of this project is to learn about **static variables** in C and how to manage memory efficiently when reading files of unknown size with a fixed buffer.

## Instructions

### Compilation

Compile the project with the following command:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can change `BUFFER_SIZE` to any positive value. If not specified, the default value is `10000`.

### Usage

Include the header in your code and call the function:

```c
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Return values

- Returns the line read (including `\n` if present)
- Returns `NULL` when there is nothing left to read or if an error occurred

## Algorithm

The algorithm uses a **static variable** to keep track of the remaining data between function calls. Here is how it works:

### Step 1: Read and accumulate data

The function reads `BUFFER_SIZE` bytes at a time from the file descriptor and concatenates them into a buffer. It continues reading until it finds a newline character `\n` or reaches the end of file.

### Step 2: Extract the line

Once a newline is found (or EOF is reached), the function extracts everything from the start of the buffer up to and including the `\n` character. This becomes the returned line.

### Step 3: Update the buffer

The remaining data after the newline is kept in the static buffer for the next call. This ensures that data read beyond the current line is not lost.

### Why this approach?

- **Memory efficient**: We only allocate what we need for each line
- **Works with any BUFFER_SIZE**: Whether it's 1 or 10000000, the logic remains the same
- **Handles edge cases**: Empty files, files without final newline, very long lines

### Helper functions

- `ft_strlen`: Calculate string length
- `ft_strchr`: Find a character in a string
- `ft_strdup`: Duplicate a string
- `ft_strjoin`: Concatenate two strings
- `ft_substr`: Extract a substring

## Resources

### Documentation and references

- [man read(2)](https://man7.org/linux/man-pages/man2/read.2.html) - Linux manual for the read() system call
- [Static variables in C](https://www.geeksforgeeks.org/static-variables-in-c/) - Understanding static keyword
- [File descriptors](https://en.wikipedia.org/wiki/File_descriptor) - Wikipedia article on file descriptors

### AI usage

I used AI (Claude) to help me understand the requirements of the README file and to verify that my README conforms to the subject's specifications. The code implementation was done by myself through research and peer discussions.
