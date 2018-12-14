#include "imports.h"

int main(int argc, char * argv[]){
  key_t key = ftok("story.txt",999);
  process(argv[1],key);
  return 0;
}
