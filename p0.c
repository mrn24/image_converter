//Project 1- graphics

#include <stdio.h>
#include <stdlib.h>


typedef struct RGBpixel {
	unsigned char r, g, b;
} RGBpixel;

typedef struct Image{
  int width, height, format, range, count;
  RGBpixel *buffer;
}Image;

int read_p6(char* input);
int read_p3(char* input);
int write_p6(char* input);
int write_p3(char* input);

Image image;

int main(int argc, char *argv[]){

  if(argc < 4){
		fprintf(stderr, "Not enough input arguments\n");
    return -1;
  }
	int writeType = atoi(argv[1]);

  FILE* fp = fopen(argv[2], "rb");
	if(fp == 0){
		fprintf(stderr, "Input file invalid\n");
		exit(9);
	}
  int c;
  int s;
  c = fgetc(fp);
  if(c != 'P'){
    fprintf(stderr, "Not a PPM File\n");
    return -1;
  }else if(c == 'P'){
    printf("PPM File");
  }else{
    fprintf(stderr, "Something went wrong\n");
    return -1;
  }
  if ((c = fgetc(fp)) == '6'){
    fclose(fp);
    read_p6(argv[2]);
  }else if(c == '3'){
    fclose(fp);
    read_p3(argv[2]);
  }else{
    printf("File error!");
    return 3;
  }
	if(writeType == 6){
		write_p6(argv[3]);
	}else if(writeType == 3){
		write_p3(argv[3]);
	}else{
		fprintf(stderr, "Wrong conversion type\n");
		return -1;
	}

  return 1;
}

int read_p6(char* input){
  FILE* fp = fopen(input, "rb");
	if(fp == 0){
		fprintf(stderr, "Input file invalid\n");
		exit(9);
	}
  int c;
  char s;
  c = fgetc(fp);
  printf("%c\n", c);
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
  fscanf(fp, "%d %d %d ", &image.width, &image.height, &image.range);
  printf("%d - %d - %d - %c\n", image.width, image.height, image.range, image.format);
  image.buffer = malloc(sizeof(image.height * image.width));
  int i=0;
  int j=0;
  while((c = fgetc(fp)) != EOF){
		printf("%d\n", c);
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
	image.count = j;
  for(i = 0; i<j; i++){
    printf("%d, %d, %d\n", image.buffer[i].r, image.buffer[i].g, image.buffer[i].b);
  }
	fclose(fp);
  return 1;
}
int read_p3(char* input){
  FILE* fp = fopen(input, "r");
	if(fp == 0){
		fprintf(stderr, "Input file invalid\n");
		exit(9);
	}
  int c;
  c = fgetc(fp);
  c = fgetc(fp);
  image.format = c;
  c = fgetc(fp);
  c = fgetc(fp);

  while (c == '#'){
    while(c != '\n'){
      c = fgetc(fp);
    }
  }

  while(c == ' '){
    c = fgetc(fp);
  }
  //c = fgetc(fp);
  fscanf(fp, "%d %d %d ", &image.width, &image.height, &image.range);

  image.buffer = malloc(sizeof(image.height * image.width));
  int j = 0;
  int i = 0;
  while((fscanf(fp, "%d ", &c)) != EOF){
    //printf("%d\n", c);
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
	image.count = j;
  for(i = 0; i<j; i++){
    printf("%d, %d, %d\n", image.buffer[i].r, image.buffer[i].g, image.buffer[i].b);
  }
	fclose(fp);
  return 1;
}

int write_p6(char* input){
	FILE* fp = fopen(input, "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "#This document was converted from P%c to P6 by my converter\n", image.format);
	fprintf(fp, "%d %d\n%d\n", image.width, image.height, image.range);
	fwrite(image.buffer, sizeof(RGBpixel), image.height * image.width, fp);
	/*for(int i = 0; i<image.count; i++){
		fwrite(fp, "%d%d%d", image.buffer[i].r, image.buffer[i].g, image.buffer[i].b);
	}*/
	fclose(fp);
	return 0;
}

int write_p3(char* input){
	FILE* fp = fopen(input, "w");
	fprintf(fp, "P3\n");
	fprintf(fp, "#This document was converted from P%c to P3 by my converter\n", image.format);
	fprintf(fp, "%d %d\n%d\n", image.width, image.height, image.range);
	for(int i = 0; i<image.count; i++){
		fprintf(fp, "%d\n%d\n%d\n", image.buffer[i].r, image.buffer[i].g, image.buffer[i].b);
	}
	fclose(fp);
	return 0;
}
