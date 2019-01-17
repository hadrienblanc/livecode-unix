
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

void print_from_index(char *strtab, uint32_t idx)
{
  printf(">> %s\n", &strtab[idx]);
  
}

int filesize(int fd)
{
  return lseek(fd, 0, SEEK_END);
}

int main(int ac, char **av)
{
  void *data;
  Elf64_Ehdr *elf;
  Elf64_Shdr *sections;
  Elf64_Shdr *symbol_table;
  int fd;
  
  char *strtab;

  fd = open(av[1], O_RDONLY);


  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);

  elf = (Elf64_Ehdr *)data;


  
  sections = (Elf64_Shdr *)(data + elf->e_shoff);

  symbol_table = NULL;

  for (int i = 0; i < elf->e_shnum ; i++)
    {
      if (sections[i].sh_type == SHT_SYMTAB) {
	symbol_table = (Elf64_Shdr *)((char *)data + sections[i].sh_offset);
      }
    }

  //  return 0;

  strtab = (char *)(data + sections[elf->e_shstrndx].sh_offset);
  
  Elf64_Sym ** st = (Elf64_Sym *)symbol_table;
  int count = 1; 
  for (int ii = 0 ; ii < count ; ii++)
    {
           printf("%i: %s \n", ii, strtab[st[ii]->st_name]);
      // print_from_index(strtab, st[ii].st_name);
    }
  
  close(fd);
  return (0);
}
