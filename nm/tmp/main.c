#include <stdlib.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

void print_all_sections(Elf64_Shdr *sections, char * strtab, int count)
{
  int i = 0;
  char * str;

  for (0 ; i < count ; i++)
    {
      
      printf("[%i] %s\n", i, &strtab[sections[i].sh_name]);
    }
}

int filesize(int fd)
{
  return lseek(fd, 0, SEEK_END);
}

int main(int ac, char **av)
{
  int fd = open(av[1], O_RDONLY);
  char *data;
  Elf64_Ehdr *elf;
  Elf64_Shdr *sections;

  char *strtab;
  
  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);

  elf = (Elf64_Ehdr *)data;

  sections = (Elf64_Shdr *)(data + elf->e_shoff);



  int count = elf->e_shnum;

  strtab = (char *)(data + sections[elf->e_shstrndx].sh_offset);  

  print_all_sections(sections, strtab, count);
  
  //  printf("");
  return 0;
}
