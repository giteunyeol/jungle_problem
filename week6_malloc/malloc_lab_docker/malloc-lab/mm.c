/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/

/* Basic constants and macros */

#define WSIZE 4 /* Word and header/footer size (bytes) */            // 한개의 워드
#define DSIZE 8 /* Double word size (bytes) */                       // 두개의 워드,헤더와 푸터가 각4바이트
#define CHUNKSIZE (1 << 12) /* Extend heap by this amount (bytes) */ // 힙을 한번 확장할때 늘릴 크기

#define MAX(x, y) ((x) > (y) ? (x) : (y)) // 두 값중 큰값 리턴

/* Pack a size and allocated bit into a word */
// 헤더값 만들기. 사이즈와, 할당여부가 들어옴
// | 하나는 비트 연산자이고(각 비트자리끼리OR), size의 하위 비트가 0이기 때문에,
// alloc값이 1이면 마지막 비트가 1, free면 0이 들어와 할당여부를 판별한다.
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
// P를 형변환후 역참조, ex)GET(HDRP(bp))하면 현재 블록 헤더에 저장된 4바이트 값
// unsigned int:부호가 없는 정수형(보통4바이트), 원래 p의 자료형을 모르니까 형변환
// bp:블록 포인터, bp는 헤더를 가리키는게 아닌 payloda시작 주소, 헤더는bp보다 4바이트 앞
//[ Header | Payload | Footer ]
//          ^bp
// malloc을 하면 포인터가 payload 시작 주소를 가리킴. 그래서 bp를 기준으로 잡음.
// p는 헤더나 푸터가 저장된 주소, bp는 블록의 payload시작주소로 생각함.
#define GET(p) (*(unsigned int *)(p))
// p가 가리키는 메모리 위치에 val을 써라
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
//&는 and연산, ~0x7은 마지막     뒤 비트가 000. 근데 그걸 기존 포인터가 가리키는
// 주소에 저장된 헤드값과 and연산을 찍어서 마지막 3비트를 0으로 만듬
#define GET_SIZE(p) (GET(p) & ~0x7)
// 헤더값의 최하위 1비트만 남기려고 0x1과 and연산 한다.
// 결과가 1이면 allocated, 0이면 free이다.
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
// 현재 블럭의 헤더주소구함. 페이로드 주소 - WSIZE
#define HDRP(bp) ((char *)(bp) - WSIZE)
// 현재 블럭의 푸터 주소를 구함. Bp에서 시작해서 DSIZE를 빼줌.
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */ // 다음 블록의 payload시작 주소를 구함
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
// GET_SIZE(((char *)(bp) - DSIZE))이게 이전 블록의 footer. bp에서 이전블럭 크기를 뺌
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8 // 조정

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

static char *mem_heap;     // 힙의 첫번째 주소
static char *mem_bkr;      // 힙의 끝 주소 + 1
static char *mem_max_addr; // 최대로 확장할 수 있는 주소

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /* Create the initial empty heap */
    //힙 시작에 필요한 초기공간 16바이트 확보하고, 실패하면 -1 리턴

    // heap_listp = mem_sbrk(4*WSIZE);
    // if (heap_listp == (void *)-1) { return -1; }, 이거 두줄이랑 같음
    // sbrk는 NULL을 안쓰고 (void *)-1을 리턴하는게 관례임.
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
    return -1;
    
    PUT(heap_listp, 0);                            /* Alignment padding */ //정렬 맞추기용 빈칸
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */ //프롤로그 블록(힙 맨 앞에 있는 가짜 할당 블록)의 헤더를 넣어줌
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ //프롤로그 블록 푸터 삽입
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     /* Epilogue header */ //에필로그 헤더 삽입(힙의 끝 표시)
    
    heap_listp += (2 * WSIZE); // heap_listp를 원래 힙 시작 주소에서 프롤로그 블록 payload위치로 옮김.(payload블록 포인터 역할로)

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    //힙을 chunksize만큼 free블록을 만들고, 실패하면 mm_init을 실패로 처리함, 실패하면 NULL리턴 
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
        return NULL;
    else
    {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
        return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
        copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

//extend_heap: 새 블록으로 힙 확장하기
static void *extend_heap(size_t words)
{
    char *bp; //새로 만들어질 블록의 payload시작 주소 (block pointer)
    size_t size; //실제로 늘릴 바이트 크기 
    
    /* Allocate an even number of words to maintain alignment */
    // 짝수로 맞춰야하니까, 홀수면 1을 더해서 wsize를 곱해주고, 짝수면 그대로 wsize를 곱해줌
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE; 
    /*
    ==
    bp = mem_sbrk(size); 
    if((long)bp == -1) { return NULL; }
    */
   //힙을 size만큼 늘려서 주소를 bp에 저장하고, 결과가 -1이면 NULL리턴
    if ((long)(bp = mem_sbrk(size)) == -1) //bp는 포인터라서, 정수형으로 바꿔서 비교하기 위함.
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    //새로 확장된 공간을 정상적인 블럭 구조로 만듬.

    //헤더와 푸터에 블럭크기, 할당상태를 넣어줌
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
    //새로운 free로 확장됐으니 뒤에 epilogue header를 다시 세움. 
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */
    //새로운 구조 [ Free block header ][ Free payload ... ][ Free block footer ][ Epilogue header ]

    /* Coalesce if the previous block was free */
    // 인접한 free블록들을 하나로 합치는 함수.
    // 힙을 확장했는데 마지막 블럭이 free였으면 free블럭이 두개로 쪼개져서 비효율적, 그래서 둘을 합치는 함수 호출
    return coalesce(bp); 
}