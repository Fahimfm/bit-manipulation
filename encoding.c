#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <windows.h>



uint8_t processnibble(uint8_t number) {
uint8_t d0, d1, d2, d3, p0, p1, p2, pleft;
uint8_t result = 0;

//0010
//0001
d0 = number &0x01;
number = number >> 1;
d1 = number &0x01;
number = number >> 1;
d2 = number &0x01;
number = number >> 1;
d3 = number &0x01;


//add parity according to the venn diagram
p0 = d0^d1^d2;
p1= d0^d1^d3;
p2= d1^d2^d3;
pleft = d3^d2^d1^d0^p2^p1^p0;
//The number order is pleft, d3,d2,d1,d0,p2,p1,p0
//get the number as a whole byte
printf("**************************After adding parity*****************\n");
printf("The number with the parity bit is: %d%d%d%d%d%d%d%d\n",pleft,d3,d2,d1,d0,p2,p1,p0);
result = result | pleft;
result = result << 1;
result = result | d3;
result = result << 1;
result = result | d2;
result = result << 1;
result = result | d1;
result = result << 1;
result = result | d0;
result = result << 1;
result = result | p2;
result = result << 1;
result = result | p1;
result = result << 1;
result = result | p0;

return result;

}

//Main Function************************************************
int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Please enter both file names");
        return -1;
    }

uint8_t MSB, LSB;
uint8_t Byte;
uint8_t text;
FILE *fp;
FILE *fr;

fp = fopen(argv[1],"r");
if (fp == NULL) {
        printf("Could not open file ");
        return 1;
    }
int result = fread(&Byte,1,1,fp);
fr = fopen (argv[2],"a");

while (result>0)
{
    //Byte =          //1010 1100
    MSB = Byte >> 4;  //0000 1010 
    LSB = Byte &0x0F; //0000 1100 
    printf("The byte is: %d\n", Byte);
    //MSB part 
    printf("************************MSB****************************\n\n");
    uint8_t outcomeMSB = processnibble(MSB);
    printf("The integer of MSB  is: %d \n", outcomeMSB);
    //return a byte with added parity(MSB)
    printf("*******Processed Most significant byte****************\n");
    //write to a file 

    //LSB part
    printf("************************LSB****************************\n\n");
    uint8_t outcomeLSB = processnibble(LSB);
    printf("The integer of LSB  is: %d \n", outcomeLSB);
    printf("*******Processed Less significant byte****************\n");
    //return a byte with added parity(LSB)
    
  
    fwrite(&outcomeMSB,1,sizeof(outcomeMSB),fr);
    fwrite(&outcomeLSB,1,sizeof(outcomeLSB),fr);

   
    
    result = fread(&Byte,1,1,fp);
}

fclose (fr);
fclose (fp);

return 0;
}

