/* solver.c */
#include<stdio.h>

typedef struct{
  int n;			/* number of cards in hand */
  int card[13];			/* 1-53, 0 nane */
} Hands;

typedef struct{
  int playernum;		/* player =[0 : playernum-1] */
  Hands hand[5];		/* h[0] : hand of player 0 */
  int passes[5];		/* passes[0] : 1 if palyer 0 passed */
  int win[5];			/* 0 in play, 1-5 winner point */
  int lastplayer;		/* 0 in lead, 1-5 in turn */
  int player;			/* 0-5 in turn */
  Hands ba;
} Gamestate;

typedef struct{
  int playernum;
  int win[5];
} Gamevalue;

typedef struct{
  Hands h[20];
  int n;
} Plays;


/* ----- prototypes ----- */
Gamevalue solver(Gamestate s);
Gamestate next_state(Gamestate s, Hands p);
Gamestate gamestate_init();
void gamestate_display(Gamestate s);

void hands_display(Hands hs);
Plays plays_makecanonicals(Gamestate s);
Plays plays_add(Plays ps, Hands h);
Hands hands_pass();
int hands_is_pass(Hands hs);
Hands hands_lowest(Hands myhand);
Hands hands_dellowest(Hands myhand);
Hands hands_dellower(Hands myhand, Hands ba);
Hands hands_delete(Hands hs, Hands hlow);
int hands_num(Hands myhand);
Hands hands_pack(Hands myhand);
Hands plays_getplay(Plays plays, int n);
Hands hands_init();

Gamevalue gamevalue_zero(int playernum);
int is_leaf(Gamestate s);
Gamevalue eval_state(Gamestate s);
Gamevalue gamevalue_merge(Gamevalue v, Gamevalue vmax);
Plays plays_init();

/* ----- solver main ----- */

main(){
  Gamestate s;
  s = gamestate_init();
  gamestate_display(s);
  solver(s);
}

Gamestate gamestate_init(){
  Gamestate gs;
  int i;

  printf("gamestate_init : stub now \n");
  gs.playernum = 3;
  for (i=0; i<gs.playernum; i++){
    gs.hand[i] = hands_init();
    gs.passes[i] = 0;
    gs.win[i] = 0;
  }
  gs.lastplayer = gs.playernum;
  gs.player = gs.playernum;
  gs.ba = hands_init();
  return gs;
}

Gamevalue solver(Gamestate s){
  Gamevalue v, vmax;
  Plays plays;
  Hands p;			/* a play */
  Gamestate ns;
  int i;

  if(is_leaf(s)) return eval_state(s);

  vmax = gamevalue_zero(s.playernum);
  
  plays = plays_makecanonicals(s);
  for(i=0; i<plays.n; i++){	/* for each plays */
    
    p = plays_getplay(plays, i);
    ns = next_state(s, p);
    v = solver(ns);
    vmax = gamevalue_merge(v, vmax);
    
    i++;
  }
  
  return vmax;
}


/* ----- functions ----- */

/* ----- game rules ----- */
Gamestate next_state(Gamestate s, Hands p){
  /* stab! */
  return s;
}

void gamestate_display(Gamestate s){
  int i;
  printf("n %d ", s.playernum);

  printf(":");
  for(i=0; i<s.playernum; i++){
    hands_display(s.hand[i]);
  }

  printf(":");
  for(i=0; i<s.playernum; i++){
    printf("%d ",s.passes[i]);
  }

  printf(":");
  for(i=0; i<s.playernum; i++){
    printf("%d ",s.win[i]);
  }

  printf(":");
  printf("n %d ", s.lastplayer);
  printf("n %d ", s.player);

  hands_display(s.ba);
  printf("\n");
}

void hands_display(Hands hs){
  int i;
  printf("%d ", hs.n);
  for(i=0; i<hs.n; i++){
    printf("%d ", hs.card[i]);
  }
}

/* ----- player models ----- */
Plays plays_makecanonicals(Gamestate s){
  /* stab! */
  
  Plays ps;
  Hands myhand;

  myhand = s.hand[ s.player ];
  myhand = hands_dellower(myhand, s.ba);


  ps = plays_init();

  while( hands_num(myhand) > 0){
    ps = plays_add( ps, hands_lowest(myhand));
    myhand = hands_dellowest(myhand);
  }

  ps = plays_add( ps, hands_pass() );

  return ps;
}

Hands hands_pass(){
  /* stab */
  /* return pass as a move of game */
  Hands pass;

  pass.n = 0;
  pass.card[0] = 0;
  return pass;
}

int hands_is_pass(Hands hs){
  if(hs.n == 0 && hs.card[0] == 0)
    return 1;
  else
    return 0;
}

Hands hands_init(){
  Hands hs;

  hs.n = 0;
  return hs;
}


/* ----- support functions ----- */
Plays plays_init(){
  Plays p;
  p.n = 0;
  return p;
}

Plays plays_add(Plays ps, Hands h){
  ps.h[ps.n] = h;
  ps.n++;
  return ps;
}

Hands hands_lowest(Hands h){
  int i, mini;

  for(i = mini = 0; i < h.n; i++){
    if(h.card[i] < h.card[mini]){
      mini = i;
    }
  }

  h.n = 1;
  h.card[0] = h.card[mini];
  
  return h;
}

Hands hands_dellowest(Hands myhand){
  Hands hlow;
  
  hlow = hands_lowest(myhand);
  myhand = hands_delete(myhand, hlow);
  
  return myhand;
}

Hands hands_delete(Hands hs, Hands hlow){
  int i;

  for(i=0; i<hs.n; i++){
    if(hs.card[i] == hlow.card[0]){
      hs.card[i] = 0;
      hs.n = hs.n -1;
    }
  }
  
  hs = hands_pack(hs);

  return hs;
}

Hands hands_dellower(Hands myhand, Hands ba){
  int i;
  
  for(i=0; i<myhand.n; i++){
    if(myhand.card[i] == 0 ) continue;
    if(myhand.card[i] <= ba.card[0]){
      myhand.n = myhand.n - 1;
      myhand.card[i] = 0;
    }
  }
  
  myhand = hands_pack(myhand);
  return myhand;
}

int hands_num(Hands myhand){
  return myhand.n;
}

Hands hands_pack(Hands myhand){
  int i, j;
  
  j=0;
  for(i=0; i<myhand.n; i++){
    if(myhand.card[i] == 0) continue;
    myhand.card[i] = myhand.card[j];
    j++;
  }
  
  return myhand;
}

Hands plays_getplay(Plays plays, int n){
  if(n < 0) n = 0;
  if(n > plays.n) n = plays.n;
  
  return plays.h[n];
}

Gamevalue gamevalue_zero(int playernum){
  Gamevalue gv;
  int i;
  
  gv.playernum = playernum;		/* default */
  for(i=0; i<playernum; i++){
    gv.win[i] = 0;
  }
  
  return gv;
}

int is_leaf(Gamestate s){
  int i;

  for(i=0; i<s.playernum; i++){
    if(s.win[s.playernum] == 0) return 0;
  }

  return 1;
}

Gamevalue eval_state(Gamestate s){
  Gamevalue gv;
  int i;
  gv.playernum = s.playernum;
  for(i=0; i<gv.playernum; i++){
    gv.win[i] = s.win[i];
  }
  return gv;
}

/* min-max track backs */
Gamevalue gamevalue_merge(Gamevalue v, Gamevalue vmax){
  if (v.win[0] > vmax.win[0]){
    vmax = v;
  }
  return vmax;
}
