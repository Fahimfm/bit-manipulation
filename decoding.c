#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    uint8_t fileoutput;
    uint8_t MSByte, LSByte,pleft, d3,d2,d1,d0,p2,p1,p0, p0check,p1check,p2check;
    uint8_t finalresult;
    FILE *fp;
    FILE *fw;
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("Could not open file ");
        return 1;
    }
    fw = fopen ("decodedOutput.txt","w");

    int result = 1;
    while(result > 0){
        //for msb
        finalresult = 0;
        result = fread(&fileoutput,1,1,fp);
        if(result == 0)
        {
            break;
        }
        /////////////////////////////For MSB Part///////////////////////////////////////
        MSByte = fileoutput;
        //retrieve the (pleft, d3,d2,d1,d0,p2,p1,p0) format
        p0 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        p1 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        p2 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        d0 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        d1 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        d2 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        d3 = MSByte & 0x01;
        MSByte = MSByte >> 1;
        pleft = MSByte & 0x01;
        
        //Checking the bits
        
        p0check = p0^d0^d1^d2;
        p1check = p1^d0^d1^d3;
        p2check = p2^d1^d2^d3;
        if(p0check ==1 && p1check==1 && p2check ==1){
            d1 = d1^0x01;
        }
        else if(p0check==1 && p1check==1 && p2check == 0){
            d0 = d0^0x01;
        }
        else if(p0check == 1 && p2check ==1&& p1check == 0){
            d2 = d2^0x01;
        }
        else if(p1check ==1 && p2check ==1 && p0check == 0){
            d3 = d3^0x01;
        }
        finalresult = finalresult | d3;
        finalresult = finalresult << 1;
        finalresult = finalresult | d2;
        finalresult = finalresult << 1;
        finalresult = finalresult | d1;
        finalresult = finalresult << 1;
        finalresult = finalresult | d0;
        

        //for lsb
        result = fread(&fileoutput,1,1,fp);
        /////////////////////////////For LSB Part///////////////////////////////////////
        LSByte = fileoutput;
        p0 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        p1 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        p2 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        d0 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        d1 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        d2 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        d3 = LSByte & 0x01;
        LSByte = LSByte >> 1;
        pleft = LSByte & 0x01;
        
        p0check = p0^d0^d1^d2;
        p1check = p1^d0^d1^d3;
        p2check = p2^d1^d2^d3;
        if(p0check == 1 && p1check==1 && p2check ==1){
            d1 = d1^0x01;
        }
        if(p0check==1 && p1check==1 && p2check == 0){
            d0 = d0^0x01;
        }
        if(p0check == 1 && p2check == 1 && p1check == 0){
            d2 = d2^0x01;
        }
        if(p1check ==1 && p2check == 1 && p0check == 0){
            d3 = d3^0x01;
        }
        finalresult = finalresult << 1;
        finalresult = finalresult | d3;
        finalresult = finalresult << 1;
        finalresult = finalresult | d2;
        finalresult = finalresult << 1;
        finalresult = finalresult | d1;
        finalresult = finalresult << 1;
        finalresult = finalresult | d0;
        
        char c = finalresult;
        printf("The decoded output is: %c\n",c);
        
  
        fwrite(&c,1,1,fw);
        

        
    }

    fclose (fw);
    fclose(fp);
    return 0;
}