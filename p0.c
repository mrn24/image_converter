//Project 1- graphics

#include <stdio.h>
#include <stdlib.h>


typedef struct RGBpixel {
	unsigned char r, g, b;
} RGBpixel;

typedef struct Image{
  int width, height, format, range;
  RGBpixel *buffer;
}Image;

Image image;

int main(int argc, char **argv){

  //if(argc < 2){
  //  return 0;
  //}
  char mn_buffer[8];
  char buffer[100];

  int i = read_image("./SamplePPMAscii.ppm");
  printf("%d\n", i);
  return 1;
}

int read_image(char* input){
  FILE* fp = fopen(input, "r");
  int c;
  c = fgetc(fp);
  printf("%c\n", c);
  if(c!= 'P'){
    printf("Not a PPM File\n");
    return 0;
  }else if(c == 'P'){
    printf("Is a PPM File\n");
  }else{
    printf("I dunno");
    return 0;
  }
  c = fgetc(fp);
  image.format = c;
  c = fgetc(fp);
  c = fgetc(fp);
  printf("%c\n", c);

  while (c == '#'){
    while(c != '\n'){
      c = fgetc(fp);
    }
  }
  while(c == ' '){
    c = fgetc(fp);
  }
  //c = fgetc(fp);
  fscanf(fp, "%d %d %d", &image.width, &image.height, &image.range);
  printf("%d - %d - %d\n", image.width, image.height, image.range);
  
  return 0;
}
