#include ".\Pointer.h"

typedef struct Human {
    u16 x;
    u16 y;
    u32 z;
    u64 w;
} Human;

#define USED_TYPE Human

void PrintHuman(Human *a){
    printf("Human:\nx: %llx\ny: %llx\nz: %llx\nw: %llx\n",a->x,a->y,a->z,a->w);
}

void PrintAll(char *s,size_t size){
    for(int i = 0;i<size;i++){
        if(s[i]!='\0') printf("%c",s[i]);
        else printf("0");
    }
}

void Test(){

}

void PrintUSED(void *Data){
    PrintHuman((Human*)Data);
}

int main(int argc,char **argv){
    /*
    Human a = { (u16)0x4040,(u16)0x4040,(u32)0x40404040,(u64)0x0040404040404040 };
    size_t size = sizeof(a);
    char *s = (char*)(&a);
    Human *b = (Human*)(s);
    char *s2 = (char*)(b);
    size_t size2 = sizeof(s2);
    printf("Output:\n");
    for(int i = 0;i<size;i++){
        if(s2[i]!='\0') printf("%c_",s2[i]);
        else printf("0");
    }
    printf("\n\n");
    */
    Pointer p = GetPointer(3,(size_t[]){3,3,3},(size_t[]){sizeof(USED_TYPE),sizeof(void*),sizeof(void*)},PrintUSED);

    PrintPointer(&p);

    printf("---------------------------------------------------------------------------------------------\n");

    USED_TYPE it = *((USED_TYPE*)GetItem(&p,(u32[]){ 1,2,1 }));
    printf("Item: %i\n",it);

    USED_TYPE set = { (u16)0x2440,(u16)0x2440,(u32)0x24242440,(u64)0x0024242424242440 };
    SetItem(&p,(u32[]){ 1,2,1 },(char*)(&set));

    USED_TYPE back = *((USED_TYPE*)GetItem(&p,(u32[]){ 1,2,1 }));
    printf("Item: ");
    PrintAll((char*)(&back),sizeof(back));
    printf("\n\n");

    USED_TYPE set2 = { (u16)0x2540,(u16)0x2540,(u32)0x25252540,(u64)0x0025252525252540 };
    SetItem(&p,(u32[]){ 1,2,1 },(char*)(&set2));

    USED_TYPE back2 = *((USED_TYPE*)GetItem(&p,(u32[]){ 1,2,1 }));
    printf("Item: ");
    PrintAll((char*)(&back2),sizeof(back2));
    printf("\n\n");
    PrintHuman(&back2);

    KillPointer(&p);

    Test();

    return 0;
}