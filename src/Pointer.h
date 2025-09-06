#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;
typedef long double f80;

typedef struct Pointer {
    u32 Dim;
    size_t *Length;
    size_t *Size;
    void *Ptr;
    void (*func)(void *Data);
} Pointer;

s8 Bounce(size_t Size,int index){
    if(index>=0&&index<Size) return 1;
    return 0;
}

void FillBranch(void **Branch,int Index,u32 Dim,u32 AcDim,size_t *Length,size_t *Size){
    //printf("Init Branch %i: %i\n",(int)Index,(int)AcDim);
    (*Branch) = (void*)calloc(Length[AcDim],Size[AcDim]);
    if(!(*Branch)){
        printf("Couldn't allocate memory!\n");
        return;
    }
    if(AcDim>0){
        for(int i = 0;i<Length[AcDim];i++){
            //printf("Continue Branch %i:\n",i);
            FillBranch(&(((void**)(*Branch))[i]),i,Dim,AcDim-1,Length,Size);
        }
    }
    //printf("Return %i:\n",Index);
}

void DestroyBranch(void **Branch,int Index,u32 Dim,u32 AcDim,size_t *Length){
    if(AcDim>0){
        for(int i = 0;i<Length[AcDim];i++){
            //printf("Destroy %i: %i\n",i,AcDim);
            DestroyBranch(&(((void**)(*Branch))[i]),i,Dim,AcDim-1,Length);
        }
    }
    //printf("Free %i: %i\n",Index,AcDim);
    if((void*)(*Branch)) free((void*)(*Branch));
    (*Branch) = NULL;
    //printf("End Free %i: %i\n",Index,AcDim);
}

void KillPointer(Pointer *P){
    printf("Kill Pointer:\n");
    DestroyBranch(&P->Ptr,0,P->Dim,P->Dim-1,P->Length);
    printf("End Pointer:\n");
}

Pointer GetPointer(u32 Dim,size_t Length[],size_t Size[],void (*func)(void *Data)){
    Pointer p;
    p.Dim = Dim;
    p.Length = Length;
    p.Size = Size;
    p.func = func;
    printf("Init:\n");
    FillBranch(&p.Ptr,0,Dim,Dim-1,Length,Size);
    printf("Done:\n");
    return p;
}

void* GetBranch(void **Branch,u32 AcDim,u32 Index[],u32 Size){
    if(AcDim>0){
        return GetBranch(&(((void**)(*Branch))[Index[AcDim]]),AcDim-1,Index,Size);
    }
    return &(((char*)(*Branch))[Index[AcDim] * Size]);
}

void* GetItem(Pointer *p,u32 Index[]){
    printf("Get Element: ");
    for(int i = 0;i<p->Dim;i++){
        printf("%i ",(int)Index[i]);
    }
    printf(" \n");

    int i = 0;
    for(;i<p->Dim;i++){
        if(!(Index[i]>=0&&Index[i]<p->Length[i])){
            break;
        }
    }
    if(i==p->Dim) return GetBranch(&p->Ptr,p->Dim-1,Index,p->Size[0]);
    else printf("Get: Index out of Bounce Exception");
    return NULL;
}

void SetBranch(void **Branch,u32 AcDim,u32 Index[],char *Item,u32 Size){
    if(AcDim>0){
        SetBranch(&(((void**)(*Branch))[Index[AcDim]]),AcDim-1,Index,Item,Size);
    }else{
        u32 index = Index[AcDim] * Size;
        for(int i = 0;i<Size;i++){
            ((char*)(*Branch))[index+i] = Item[i];
        }
    }
}

void SetItem(Pointer *p,u32 Index[],char *Item){
    printf("Set Element: ");
    for(int i = 0;i<p->Dim;i++){
        printf("%i ",(int)Index[i]);
    }
    printf(" \n");

    int i = 0;
    for(;i<p->Dim;i++){
        if(!(Index[i]>=0&&Index[i]<p->Length[i])){
            break;
        }
    }
    if(i==p->Dim) SetBranch(&p->Ptr,p->Dim-1,Index,Item,p->Size[0]);
    else printf("Set: Index out of Bounce Exception");
}

void PrintBranch(void **Branch,int Index,u32 Dim,u32 AcDim,size_t *Length,void (*func)(void *Data)){
    if(AcDim>0){
        for(int i = 0;i<Length[AcDim];i++){
            printf("Go to %i: %i\n",i,AcDim);
            PrintBranch(&(((void**)(*Branch))[Index]),i,Dim,AcDim-1,Length,func);
        }
    }
    printf("Go to %i: %i\n",Index,AcDim);
    for(int i = 0;i<Length[AcDim];i++){
        func((*Branch));
    }
}

void PrintPointer(Pointer *P){
    PrintBranch(&P->Ptr,0,P->Dim,P->Dim-1,P->Length,P->func);
}
