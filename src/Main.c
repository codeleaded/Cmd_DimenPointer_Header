#if defined(__linux__)
    #include "/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(_WINE)
    #include "/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(_WIN32)
    #include "F:/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(__APPLE__)
    #error "Apple not supported!"
#else
    #error "Platform not supported!"
#endif

void print(void* p){
    printf("%d ",*(int*)p);
}

int main(int argc,char **argv){
    Pointer p = Pointer_New(3U,(unsigned int[]){ 2U,2U,2U },sizeof(int),NULL,print);

    Pointer_Set(&p,(unsigned int[]){ 0U,0U,0U },(int[]){ 0 });
    Pointer_Set(&p,(unsigned int[]){ 0U,0U,1U },(int[]){ 1 });

    Pointer_Set(&p,(unsigned int[]){ 0U,1U,0U },(int[]){ 2 });
    Pointer_Set(&p,(unsigned int[]){ 0U,1U,1U },(int[]){ 3 });

    Pointer_Set(&p,(unsigned int[]){ 1U,0U,0U },(int[]){ 4 });
    Pointer_Set(&p,(unsigned int[]){ 1U,0U,1U },(int[]){ 5 });

    Pointer_Set(&p,(unsigned int[]){ 1U,1U,0U },(int[]){ 6 });
    Pointer_Set(&p,(unsigned int[]){ 1U,1U,1U },(int[]){ 7 });
    
    Pointer_Print(&p);

    Pointer_Free(&p);
    return 0;
}