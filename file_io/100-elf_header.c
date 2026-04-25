#include "main.h"

/**
 * print_magic - Prints the ELF magic bytes.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_magic(unsigned char *e_ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", e_ident[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_class - Prints the ELF class.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	switch (e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	case ELFCLASSNONE:
		printf("none\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_data - Prints the ELF data encoding.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	switch (e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	case ELFDATANONE:
		printf("none\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_DATA]);
	}
}

/**
 * print_version - Prints the ELF version.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_version(unsigned char *e_ident)
{
	printf("  Version:                           %d", e_ident[EI_VERSION]);
	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
}

/**
 * print_osabi - Prints the ELF OS/ABI.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_osabi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n"); break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n"); break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n"); break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n"); break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n"); break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n"); break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n"); break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n"); break;
	case ELFOSABI_ARM:
		printf("ARM\n"); break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n"); break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_abiversion - Prints the ELF ABI version.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_abiversion(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
 * print_type - Prints the ELF type.
 * @e_type: The ELF type value.
 * @e_ident: The ELF identification array (for endianness).
 *
 * Return: void
 */
void print_type(uint16_t e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type = (e_type >> 8) | (e_type << 8);

	printf("  Type:                              ");
	switch (e_type)
	{
	case ET_NONE:
		printf("NONE (None)\n"); break;
	case ET_REL:
		printf("REL (Relocatable file)\n"); break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n"); break;
	case ET_DYN:
		printf("DYN (Shared object file)\n"); break;
	case ET_CORE:
		printf("CORE (Core file)\n"); break;
	default:
		printf("<unknown: %x>\n", e_type);
	}
}

/**
 * print_entry - Prints the ELF entry point address.
 * @e_entry: The entry point address.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void print_entry(unsigned long e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");
	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("0x%x\n", (unsigned int)e_entry);
	else
		printf("0x%lx\n", e_entry);
}

/**
 * check_elf - Checks if file is a valid ELF and exits if not.
 * @e_ident: The ELF identification array.
 *
 * Return: void
 */
void check_elf(unsigned char *e_ident)
{
	if (e_ident[0] != 0x7f || e_ident[1] != 'E' ||
		e_ident[2] != 'L' || e_ident[3] != 'F')
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
}

/**
 * main - Displays ELF header information.
 * @argc: The number of arguments.
 * @argv: Array of argument strings.
 *
 * Return: 0 on success, 98 on failure.
 */
int main(int argc, char *argv[])
{
	int fd;
	Elf64_Ehdr header;
	ssize_t n;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	n = read(fd, &header, sizeof(header));
	if (n < 1 || n != sizeof(header))
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		close(fd);
		exit(98);
	}

	check_elf(header.e_ident);

	printf("ELF Header:\n");
	print_magic(header.e_ident);
	print_class(header.e_ident);
	print_data(header.e_ident);
	print_version(header.e_ident);
	print_osabi(header.e_ident);
	print_abiversion(header.e_ident);
	print_type(header.e_type, header.e_ident);
	print_entry(header.e_entry, header.e_ident);

	close(fd);
	return (0);
}
