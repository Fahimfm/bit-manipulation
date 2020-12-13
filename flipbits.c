#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <windows.h>


int main(int argc, char *argv[])
{

    
    uint8_t MSByte, LSByte,fileoutput;
    FILE *fp;
    FILE *fw;
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("Could not open file ");
        return 1;
    }
    fw = fopen (argv[2],"a");
    if (fw == NULL) {
        printf("Could not open file ");
        return 1;
    }
    //DEclare srand and rand
    srand(time(NULL));
    int randNo;
    int result = 1;
    while(result > 0){
        //Reading the MSB
        result = fread(&fileoutput,1,1,fp);
        if(result == 0)
        {
            break;
        }
        MSByte = fileoutput;
        /////////////////////////////For MSB Part///////////////////////////////////////
        printf("%d is the msb\n", MSByte);
        randNo = (rand() % 7) + 1;
        switch (randNo) {
        case 1: MSByte = MSByte^0x01; printf("The first bit has been flipped\n");   break;
        case 2: MSByte = MSByte^0x02; printf("The second bit has been flipped\n");  break;
        case 3: MSByte = MSByte^0x04; printf("The third bit has been flipped\n");   break;
        case 4: MSByte = MSByte^0x08; printf("The fourth bit has been flipped\n");  break;
        case 5: MSByte = MSByte^0x10; printf("The fifth bit has been flipped\n");   break;
        case 6: MSByte = MSByte^0x20; printf("The sixth bit has been flipped\n");   break;
        case 7: MSByte = MSByte^0x40; printf("The seventh bit has been flipped\n"); break;
        default: break; }
        
        /////////////////////////////For LSB Part///////////////////////////////////////
        //Reading the LSB
        result = fread(&fileoutput,1,1,fp);
        LSByte = fileoutput;
        switch (randNo) {
        case 1: LSByte = LSByte^0x01; printf("The first bit has been flipped\n");   break;
        case 2: LSByte = LSByte^0x02; printf("The second bit has been flipped\n");  break;
        case 3: LSByte = LSByte^0x04; printf("The third bit has been flipped\n");   break;
        case 4: LSByte = LSByte^0x08; printf("The fourth bit has been flipped\n");  break;
        case 5: LSByte = LSByte^0x10; printf("The fifth bit has been flipped\n");   break;
        case 6: LSByte = LSByte^0x20; printf("The sixth bit has been flipped\n");   break;
        case 7: LSByte = LSByte^0x40; printf("The seventh bit has been flipped\n"); break;
        default: break; }
        

        
  
        fwrite(&MSByte,1,sizeof(MSByte),fw);
        fwrite(&LSByte,1,sizeof(LSByte),fw);

        

        //Print the results into a file

        printf("%d is the lsb\n", LSByte);
    }
    fclose (fw);
    fclose(fp);

   

    return 0;
}
