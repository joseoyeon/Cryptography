#include<stdio.h>

int main () {
int N = 160;
int i;
char love1[160] = "UnicOdeiSaCompUtInGindustRystanDArDforConsiStentEncodingRepresenTationAndhanDlinGofALLtEXTUsinGUNIcodEALLHAngUlsYllAblesCANBEExpRessedbyBitdatAbEtweenXacandxdaF";
char love2[160] = "eXcluSiVeoRXoRISaLOGiCaLopeRAtiOnTHAtRESuLTSTruEonLYwhEniNpuTsdiffERoneiSTRuETheoThErIsFALSEiTIsoFTEnUsEdfoRbitWiSeDyADIcOPERatIonSXorXorXorAnDxorAReestABLisHeD";
int tmp1[10];
for (i=0; i<160; i++){
    love1[i] = ((love1[i] >= 'A' && love1[i] <='Z')?  0 :  1); 
    love2[i] = ((love2[i] >= 'A' && love2[i] <='Z')?  0 :  1);
    love1[i]  ^= love2[i];
    // if(i%16==0)printf("\n");
    // printf("%x", love1[i]);
}

tmp1[0] = 0b1100110110010101;
tmp1[1] = 0b1101010101011000;
tmp1[2] = 0b1101010101101001;
tmp1[3] = 0b1011001011001000;
tmp1[4] = 0b1011001011100100;
tmp1[5] = 0b1100100000010101;
tmp1[6] = 0b1011001011110101;
tmp1[7] = 0b1100011110000101;
tmp1[8] = 0b1011001011001000;
tmp1[9] = 0b1011001011100100;
for (i=0 ; i<10; i++){
    printf(" %X",tmp1[i]);
}
//https://jjeong.tistory.com/696
    return 0;
}