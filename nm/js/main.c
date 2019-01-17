#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>
#include <unistd.h>
#include <stdio.h>

int		filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void		print_all(Elf64_Shdr *sections_h, char *strtab, int count)
{
  int i;

  i = 0;
  while (i < count)
    {
      printf("section header name = %s\n", strtab + sections_h[i].sh_name);
      i++;			      
    }
  
}

int		main(int ac, char **av)
{
  int		fd;
  void		*data;
  Elf64_Ehdr	*tmp;

  Elf64_Shdr *sections_h;
    
  if (ac < 2)
    return (0);
  fd = open(av[1], O_RDONLY);
  if (fd == -1)
    return (-1);
  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
  tmp = data;
  if (tmp->e_ident[0] == 127 && tmp->e_ident[1] == 'E'
      && tmp->e_ident[2] == 'L' && tmp->e_ident[3] == 'F')
    printf("CECI EST UN FICHIER ELF %d %d %d %d\n", tmp->e_ident[0],
	   tmp->e_ident[1], tmp->e_ident[2], tmp->e_ident[3]);


  sections_h = data + tmp->e_shoff;

  char *strtab;

  strtab = (char *)data + sections_h[tmp->e_shstrndx].sh_offset;


  int count = tmp->e_shnum;
  
  print_all(sections_h, strtab, count);
  
  return (0);
}
