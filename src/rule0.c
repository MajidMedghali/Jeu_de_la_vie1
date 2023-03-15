#include"rule1.h"
#include"world.h"
#include<stdio.h>
#define BLANC 16777215
#define NOIR 0
#define BLEU 16711680
#define ROUGE 255

struct rule
{
  int couleur;
  int couleur_voisin;
  int couleur_new;
  int regle[8];
};



struct rule  rule[2] ={{NOIR,BLANC,BLANC,{3,3,3,3,3,3,3,3}}
		       ,{BLANC,BLANC,NOIR,{0,1,4,5,6,7,8,8}}};

int couleur(int r, int v, int b){
  int N=65536*b+256*v+r;
  return N;
}


unsigned int rules_count()
{
  unsigned int x=sizeof(rule)/sizeof(rule[0]);
  return x;
}


void remplir_image1(const struct world* w, int img[HEIGHT][WIDTH])
{
  for (int i=0; i<HEIGHT; ++i)
    {
      for (int j=0; j<WIDTH; ++j)
	{
	  img[i][j]=w->t[i*WIDTH+j];
	}
    }  
}

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
  return r->couleur_new ;
}

struct rule* rule_get(unsigned int i)
{
  return &(rule[i]);
}

		  
int rule_match(const struct world* w,const struct rule* r
               ,unsigned int i, unsigned int j)
{
  int img[HEIGHT][WIDTH];
  remplir_image1(w,img);
  int v[8];
  v[0]=img[(i-1)%HEIGHT][(j-1)%WIDTH];
  v[1]=img[(i-1)%HEIGHT][j];
  v[2]=img[(i-1)%HEIGHT][(j+1)%WIDTH];
  v[3]=img[i][(j+1)%WIDTH];
  v[4]=img[(i+1)%HEIGHT][(j+1)%WIDTH];
  v[5]=img[(i+1)%HEIGHT][j];
  v[6]=img[(i+1)%HEIGHT][(j-1)%WIDTH];
  v[7]=img[i][(j-1)%WIDTH];
  int couleur=w->t[i*WIDTH+j];
  if (couleur==r->couleur)
    {
      int comp=0;
      for (int k=0; k<8; ++k)
	{
	  if (v[k]==r->couleur_voisin)
	      ++comp;
	}
     
      for (int k=0; k<7; ++k)
	{
	  if (comp==r->regle[k])
	    return 1;
	}
      return 0;
    }
  return 2;
}
