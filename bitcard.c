/* card game simulater */
/* junji nishino nishinojunji@gmail.com 2011 */

/* deliver cards */
/* handle cards */

#include<stdio.h>
#include<stdint.h>

typedef int64_t myint64;

typedef struct {
  myint64 c; /* bit board sizeof(long) == 8 in 64bit architecture */
  int na; /* number of all cards */
} Cards;

#define HANDS_LIMIT 53
typedef struct {
  Cards h[HANDS_LIMIT];
  int n;
} Hands;

/* ----- prototypes ----- */
void cards_display(Cards c);
int cards_countnum(Cards c);
Cards cards_addcard(Cards c, int i);
Cards cards_init();
Cards cards_dellower(Cards c, Cards d);
Cards cards_getlowest(Cards c);

Hands hands_init();
void hands_display(Hands h);
Hands hands_cardsdivide(Cards c);

/* ----- main ----- */
main(){
  Cards c, d;
  Hands h;

  c = cards_init();
  d = cards_init();

  h = hands_init();

  /* c = cards_addcard(c, 0); */
  /* c = cards_addcard(c, 3); */
  c = cards_addcard(c, 10);
  /* c = cards_addcard(c, 20); */
  /* c = cards_addcard(c, 30); */
  /* c = cards_addcard(c, 31); */
  /* c = cards_addcard(c, 32); */
  /* c = cards_addcard(c, 33); */
  /* c = cards_addcard(c, 60); */
  /* c = cards_addcard(c, 60); */
  /* c = cards_addcard(c, 40); */
  c = cards_addcard(c, 50);
  c = cards_addcard(c, 7);
  /* c = cards_addcard(c, 61); */
  /* c = cards_addcard(c, 62); */

  c = cards_addcard(c, 63);
  /* c = cards_addcard(c, 64); */
  /* c = cards_addcard(c, 65); */
  cards_display(c);  printf("\n");

  h = hands_cardsdivide(c);
  hands_display(h);

  /* d = cards_addcard(d, 31); */
  /* cards_display(d);  printf("\n"); */
  
  /*  printf("countnum %d\n", cards_countnum(c)); */
  /* cards_display(cards_dellower(c, d)) ;  printf("\n"); */
  /* cards_display(cards_getlowest(c)) ;  printf("\n"); */

}



/* -- functions -- */

int cards_countnum(Cards c){
  int num;

  num=0;
  while(c.c !=0){
    if(c.c & 1 == 1)  num++;
    c.c = c.c >> 1;
  }
  return num;
}

/* delete cards in c lower than d */
Cards cards_dellower(Cards c, Cards d){
  myint64 mask;
  mask = ((~d.c)+1) ^ d.c; /* 00001000 -> 11110000 */
  c.c = c.c & mask;
  return c;
}

/* 00101000 -> 00001000 */
Cards cards_getlowest(Cards c){
  c.c = (~c.c + 1) & c.c;
  return c;
}

Cards cards_init(){
  Cards c;
  c.na= 0;
  c.c = 0;
  return c;
}

Cards cards_addcard(Cards c, int i){
  c.c = c.c | 1UL<<i;
  c.na = c.na + 1;
  return c;
}

void cards_display(Cards c){
  myint64 a;
  int i;
  i=0;
  a = 1;
  while(a != 0){
    if(a & c.c) printf("%d ", i);
    a = a<<1;
    i++;
  }
}

/* --- hands --- */
Hands hands_init(){
  Hands h;
  h.n = 0;
  return h;
}

void hands_display(Hands h){
  int i;
  for (i=0; i<h.n; i++){
    cards_display(h.h[i]); printf("\n");
  }
}

Hands hands_addcards(Hands h, Cards c){
  if(h.n >= HANDS_LIMIT) return h;
  h.h[h.n] = c;
  h.n++;
  return h;
}

Hands hands_cardsdivide(Cards c){
  Hands h;
  Cards cw;

  h = hands_init();
  while(c.c != 0){
    cw.c = (~c.c + 1) & c.c;	/* get least one  */
    h = hands_addcards(h, cw);
    c.c = c.c ^ cw.c;
  }
  return h;
}
