#include <stdio.h>
#include <unistd.h>

typedef char ALIGN[8];
union header{
    struct{
        size_t size;
        unsigned is_free;
        union header* next;
    }s;
    ALIGN stub;
};

typedef union header header_t;

int main(){
    header_t* a;
    size_t total_size = sizeof(header_t) + sizeof(int);
    void* block = sbrk(total_size);
    if(block == (void*)-1){
        printf("sbrk failed\n");
        return 1;
    }
    a = block;
    a->s.size = sizeof(int);
    a->s.is_free = 0;
    a->s.next = NULL;
    printf("block %p, %p\n", (void*)block, (void*)(a+1));



    printf("%d, %d\n", sizeof(*a), sizeof(union header));
    printf("void* %d\n", sizeof(void*));
    printf("s %d %p\n", sizeof(a->s), &a->s);
    printf("s.size %d %p\n", sizeof(a->s.size), &a->s.size);
    printf("s.is_free %d %p\n", sizeof(a->s.is_free),&a->s.is_free);
    printf("s.next %d %p\n", sizeof(a->s.next), &a->s.next);
    printf("stub %d %p\n", sizeof(a->stub), &a->stub);
    return 0;
}
