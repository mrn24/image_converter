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

int read_image(char* input);

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
  unsigned int s;
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
  printf("comment while\n");
  while (c == '#'){
    while(c != '\n'){
      c = fgetc(fp);
    }
  }
  printf("out of comment while\n");
  while(c == ' '){
    c = fgetc(fp);
  }
  //c = fgetc(fp);
  fscanf(fp, "%d %d %d ", &image.width, &image.height, &image.range);
  printf("%d - %d - %d - %c\n", image.width, image.height, image.range, image.format);
  //<------HERE!
  printf("Setting up while");
  //image.buffer = malloc(sizeof(image));
  int j = 0;
  int i = 0;
  while(fscanf(fp, " %u ", s) != EOF){
    c = atoi(s);
    printf("While\n");
    if(i == 0){
      image.buffer[j].r = c;
      i++;
    }else if(i == 1){
      image.buffer[j].g = c;
      i++;
    }else{
      image.buffer[j].b = c;
      i = 0;
      j++;
    }
  }

  /*for(i = 0; i<j; i++){
    printf("%d, %d, %d\n", image.buffer[i].r, image.buffer[i].g, image.buffer[i].b);
  }*/

  return 0;
}
