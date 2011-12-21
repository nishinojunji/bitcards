/* card game simulater */
/* junji nishino nishinojunji@gmail.com 2011 */

/* deliver cards */
/* handle cards */

#include<stdio.h>
#include<stdint.h>

typedef struct {
  int64_t c; /* bit board sizeof(long) == 8 in 64bit architecture */
  int na; /* number of all cards */
} Cards;


void cards_display(Cards c);
int cards_countnum(Cards c);
Cards cards_addcard(Cards c, int i);
Cards cards_init();

main(){
  Cards c;

  c = cards_init();

  c = cards_addcard(c, 0);
  c = cards_addcard(c, 3);
  c = cards_addcard(c, 10);
  /* c = cards_addcard(c, 20); */
  c = cards_addcard(c, 30);
  c = cards_addcard(c, 31);
  c = cards_addcard(c, 32);
  /* c = cards_addcard(c, 33); */
  /* c = cards_addcard(c, 60); */
  /* c = cards_addcard(c, 40); */
  /* c = cards_addcard(c, 50); */
  c = cards_addcard(c, 7);
  cards_display(c);
  printf("\n");
  printf("countnum %d\n", cards_countnum(c));
}



/* -- functions -- */
int cards_countnum(Cards c){
  int num;

  num=0;
  while(c.c !=0){
    if(c.c & 1 == 1)  num++;	/* why not ? */
    c.c = c.c >> 1;
  }
  return num;
}

Cards cards_init(){
  Cards c;
  c.na= 0;
  c.c = 0;
  return c;
}

Cards cards_addcard(Cards c, int i){
  c.c = c.c | 1UL<<i;
  c.na = c.na+1;
  return c;
}

void cards_display(Cards c){
  int64_t a;
  int i;
  i=0;
  a = c.c;
  while(a != 0){
    if(a & 1) printf("%d ", i);
    a = a>>1;
    i++;
  }
}
