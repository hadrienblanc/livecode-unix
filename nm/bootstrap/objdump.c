
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

void print_sh_name(Elf64_Shdr *shdr, char *strtab, int shnum)
{
  int i = 0;

  i = 0;
  while (i < shnum)
    {
      printf("%03d: %s\n", i, &strtab[shdr[i].sh_name]);
      i++;
    }
  
}


int filesize(int fd)
{
  return lseek(fd, 0, SEEK_END);
}

int main(int ac, char **av)
{
  void *data;
  Elf64_Ehdr *elf;
  Elf64_Shdr *shdr;
  int fd;
  
  char *strtab;

  fd = open(av[1], O_RDONLY);


  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);

  elf = (Elf64_Ehdr *)data;

  shdr = (Elf64_Shdr *)(data + elf->e_shoff);

  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  
  print_sh_name(shdr, strtab, elf->e_shnum);
  close(fd);
  return (0);
}
