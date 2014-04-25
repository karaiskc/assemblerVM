#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA_MEMORY 8192

struct Opcode {
  char name[4];
  unsigned int params;
};

int main(int argc, char** argv)
{
  if(argc != 3){
    printf("Usage: %s source.asm binary.bin\n", argv[0]);
    return EXIT_FAILURE;
  }

  //Read language information
  FILE* lang = fopen("lang.dat", "r");
  if (lang==NULL)
  {
    puts("cannot open lang.dat");
    return EXIT_FAILURE;
  }

  //Read supported opcodes and respective parameter numbers
  struct Opcode* opcodes = malloc(sizeof(struct Opcode));
  size_t size=0;
  while (fscanf(lang, "%s %u ", opcodes[size].name, &opcodes[size].params)==2)
  {
    size++;
    opcodes = realloc(opcodes, sizeof(struct Opcode)* (size+1));
  }
  fclose(lang);

  //Open the source and destination files
  FILE* src = fopen(argv[1], "r");
  FILE* dest = fopen(argv[2], "w");
  
  if(!src || !dest)
  {
    puts("cannot open file");
    free(opcodes);
    return EXIT_FAILURE;
  } 


  //Generate the binary code

  char instruction[12];
  unsigned int arr[DATA_MEMORY] = {0};
  int idx=0;

  while(fscanf(src, "%s ", instruction)!=EOF)
  {
    char* addr = strstr(instruction, "$");
    //printf("\ninstruction = %s ",instruction);

    if(addr!=NULL) 
    {
        *addr='0';
        idx=atoi(instruction);
        //printf("idx = %d\n",idx);
        continue;
    }

    //skip comments
    if(strstr(instruction, "//") != NULL)
    {
        while(fgetc(src)!='\n') {};
        continue;
    } 
    else 
    {
        //search for opcode in table
      for (size_t i=0;i<size;i++)
      {
        if(!strcmp(instruction, opcodes[i].name))
        {
          arr[idx++]=i;
	  //printf("idx = %d i = %zu arr[0] = %u\n",idx,i,arr[0]);

          for (unsigned int j=0;j<opcodes[i].params;j++){
            fscanf(src, "%u", &arr[idx++]);
	    //printf("%u ",arr[idx-1]);
	  }
          break;
        }
        if(i==(size-1))
        {
         // Invalid instruction
          printf("error: Invalid instruction \"%s\"\nAborting\n", instruction);
          fclose(src);
          fclose(dest);
          free(opcodes);
          return EXIT_FAILURE;
        }
      }
    }
  }

  // Write binary to file

  fwrite(arr, sizeof(unsigned int), DATA_MEMORY, dest);

  //for (i=0;i<(int)size;i++)printf("arr[%d] = %u\n",i,arr[i]);

  // Close files and free memory
  fclose(src);
  fclose(dest);
  free(opcodes);

  // All done
  puts("All Done...");
  return EXIT_SUCCESS;
}

