
*This project has been created as part of the 42 curriculum by decabral.*

# **Description:**
- The goal of this project is to create a function that reads a text pointed to by `fd` (file descriptor) one line at a time, followd by a `\n` (new line), except when the end of the file is reached and does not end with `\n` character. `get_next_line` returns the line that was read and if there is nothing left to read or an error occurs, it should return `NULL`.

# **Instructions:**
##  For compilation.
> Create a main.c file to call the function.

> In terminal, run the following command: 
Note: You must define the BUFFER_SIZE flag during compilation.
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```
> Run the executable:
```
./a.out
```
> To test with the bonus part (multiple file descriptors):
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```
> Run the executable:
```
./a.out
```

# **Explanation and Justification of Data and Structure**:
- Static Variables: The core of this project relies on the use of a static variable. Unlike standard local variables which are destroyed after a function returns, a static variable remains in memory. This allows the function to "remember" the text read from the file that appeared after the newline character (\n), storing it for the next function call.

- Buffer Management: The function reads the file in chunks defined by BUFFER_SIZE. It uses a temporary buffer to collect raw bytes from the read() system call. These bytes are immediately converted into a valid C-string (null-terminated) and joined with the accumulated static backup string.

- Optimization (Blocking I/O Prevention): To ensure efficiency, the function checks if a newline (\n) already exists in the static backup before attempting to read from the file again. This prevents unnecessary system calls and ensures the program doesn't "hang" or block waiting for input if a line is already available in memory.

- Memory Management: Great care was taken to prevent memory leaks. Every time the backup string is expanded (via ft_strjoin) or trimmed (via ft_store_rest), the old memory blocks are freed.

- Multiple File Descriptors (Bonus): To handle multiple files simultaneously, the static variable was implemented as an array of pointers (static char *backup[FD_MAX]). The File Descriptor (fd) integer serves as the index for the array, giving each open file its own dedicated memory space.

# **Resources:**
## Tutorial Videos
- For this project I watched some videos on youtube that helped me understand how static variables and file descriptors works.
- Here are some links:
> - [Get Next Line 42 | Part 1](https://www.youtube.com/watch?v=kR4FyNzVDBE)
> - [get_next_line explained : develop a function that reads a file line by line](https://www.youtube.com/watch?v=8E9siq7apUU&t=1569s)
> - [What is a static variable?](https://www.youtube.com/watch?v=OngGUoENgWo&t=1s)
> - [Inside Linux File Descriptors - Mastering the Basics](https://www.youtube.com/watch?v=saMebwRO-Q8)

Also I consulted the Manuals for file control: man 2 read, man 2 open, and man 3 malloc.

## AI
 - Used AI to help me visualize the logic of static variables, explaining how memory persists between function calls "like I'm five".

- It helped clarify how to handle edge cases, such as reading binary files or handling the End Of File (EOF) correctly without leaks.

- Also assisted in optimizing the logic to avoid timeouts on large files by checking the buffer for newlines more efficiently.
