#include <stdio.h>
#include <stdint.h>

uint8_t sbox[2][4][4] = {{{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}},{{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}}};
int P10[10]={3,5,2,7,4,10,1,9,8,6},P8[8]={6,3,7,4,8,5,10,9},IP[8]={2,6,3,1,4,8,5,7},IPi[8]={4,1,3,5,7,2,8,6},EP[8]={4,1,2,3,2,3,4,1},P4[4]={2,4,3,1};

uint8_t rotl5(uint8_t x,int n){return ((x<<n)|(x>>(5-n)))&0x1F;}

void gen(uint16_t k,uint8_t* k1,uint8_t* k2){
    uint16_t p=0;for(int i=0;i<10;i++)p|=((k>>(10-P10[i]))&1)<<(9-i);
    uint8_t l=(p>>5)&0x1F,r=p&0x1F;
    l=rotl5(l,1);r=rotl5(r,1);p=(l<<5)|r;
    *k1=0;for(int i=0;i<8;i++)*k1|=((p>>(10-P8[i]))&1)<<(7-i);
    l=rotl5(l,2);r=rotl5(r,2);p=(l<<5)|r;
    *k2=0;for(int i=0;i<8;i++)*k2|=((p>>(10-P8[i]))&1)<<(7-i);
}

uint8_t f(uint8_t r,uint8_t k){
    uint8_t e=0;for(int i=0;i<8;i++)e|=((r>>(4-EP[i]))&1)<<(7-i);
    e^=k;uint8_t l=e>>4,rr=e&0xF;
    int row=((l&8)>>2)|(l&1),col=(l>>1)&3;
    uint8_t s0=sbox[0][row][col];
    row=((rr&8)>>2)|(rr&1);col=(rr>>1)&3;
    uint8_t s1=sbox[1][row][col];
    uint8_t s=(s0<<2)|s1,o=0;
    for(int i=0;i<4;i++)o|=((s>>(4-P4[i]))&1)<<(3-i);
    return o;
}

uint8_t sdes(uint8_t in,uint8_t k1,uint8_t k2){
    uint8_t ip=0;for(int i=0;i<8;i++)ip|=((in>>(8-IP[i]))&1)<<(7-i);
    uint8_t l=ip>>4,r=ip&0xF;
    l^=f(r,k1);uint8_t tmp=l;l=r;r=tmp;
    l^=f(r,k2);uint8_t pre=(l<<4)|r,out=0;
    for(int i=0;i<8;i++)out|=((pre>>(8-IPi[i]))&1)<<(7-i);
    return out;
}
