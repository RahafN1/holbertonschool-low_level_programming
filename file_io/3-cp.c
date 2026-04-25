#define _GNU_SOURCE
#include "main.h"
#include <stdio.h>

/**
 * close_fd - Closes a file descriptor and exits on failure.
 * @fd: The file descriptor to close.
 *
 * Return: void
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * open_files - Opens source and destination files.
 * @file_from: Name of the source file.
 * @file_to: Name of the destination file.
 * @fd_from: Pointer to store source file descriptor.
 * @fd_to: Pointer to store destination file descriptor.
 *
 * Return: void
 */
void open_files(char *file_from, char *file_to, int *fd_from, int *fd_to)
{
	*fd_from = open(file_from, O_RDONLY);
	if (*fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		exit(98);
	}

	*fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		close_fd(*fd_from);
		exit(99);
	}
}

/**
 * copy_content - Copies content from one fd to another.
 * @fd_from: Source file descriptor.
 * @fd_to: Destination file descriptor.
 * @file_from: Name of source file (for error message).
 * @file_to: Name of destination file (for error message).
 *
 * Return: void
 */
void copy_content(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t bytes_read, bytes_written;
	char buffer[1024];

	while ((bytes_read = read(fd_from, buffer, 1024)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written == -1 || bytes_written != bytes_read)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
			close_fd(fd_from);
			close_fd(fd_to);
			exit(99);
		}
	}
	if (bytes_read == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		close_fd(fd_from);
		close_fd(fd_to);
		exit(98);
	}
}

/**
 * main - Copies content of a file to another file.
 * @argc: The number of arguments.
 * @argv: Array of argument strings.
 *
 * Return: 0 on success, exits with error code on failure.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	open_files(argv[1], argv[2], &fd_from, &fd_to);
	copy_content(fd_from, fd_to, argv[1], argv[2]);
	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}
