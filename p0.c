//Project 1- graphics

#include <stdio.h>
#include <stdlib.h>


typedef struct RGBApixel {
	unsigned char r, g, b, a;
} RGBApixel;


int main(argv[], argc){
  if(argc < 2){
    return 0;
  }
  char mn_buffer[8];
  char buffer[100];
  FILE* fp = fopen(argv[1], "r");
  

  return 1;
}
