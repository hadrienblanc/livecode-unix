#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>

int filesize(int fd)
{
  return lseek(fd, 0, SEEK_END);
}

void print_all(char * strtab, Elf64_Shdr *sections, int count)
{
  int i = 0;
  char * str;
  
  while (i < count)
    {
      printf("%i : %s\n", i , &strtab[sections[i].sh_name]);
      i++;
    }
}

int main(int ac, char **av)
{
  Elf64_Ehdr *elf;
  Elf64_Shdr *sections;

  char *data;
  char * strtab;

  int fd = open(av[1], O_RDONLY);

  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
  

  elf = (Elf64_Ehdr *)data;

  sections = (Elf64_Shdr *)(data + elf->e_shoff);

  strtab = (char *)(data + sections[elf->e_shstrndx].sh_offset);

  int count = elf->e_shnum;
    
  print_all(strtab, sections, count);  
  
  return 0;
}
