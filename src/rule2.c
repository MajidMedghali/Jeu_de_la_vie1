#include"rule2.h"
#include"world.h"
#include<stdio.h>
#define BLANC 16777215
#define NOIR 0
#define BLEU 16711680
#define ROUGE 255
#define JAUNE 65535
#define GRIS 6579300
struct rule
{
 
  int dx;
  int dy;
  int couleur;
  int voisins[4];
};



struct rule rule[3] ={
                      {1,0,JAUNE,{0,0,0,0}},
             
                      {1,-1,JAUNE, {JAUNE,JAUNE,JAUNE, NOIR}},
		      {1,1,JAUNE, {NOIR,JAUNE,JAUNE,JAUNE}}};
		       
                   




int rule_change_dx(const struct rule* r, unsigned int idx)
{
  return idx+r->dx;

}
int rule_change_dy(const struct rule* r, unsigned int idx)
{
  return idx+r->dy;
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



struct rule* rule_get(unsigned int i)
{
  return &(rule[i]);
}



int rule_match(const struct world* w,const struct rule* r,unsigned int i,
	       unsigned int j)
{
 
  int img[HEIGHT][WIDTH];
  remplir_image1(w,img);
 
  int couleur=w->t[i*WIDTH+j];
  if (couleur==r->couleur)
    {
      if (r->dy==-1)
	{
	  int v[4];
	  v[0]=img[i][(j+1)%WIDTH];
	  v[1]=img[(i+1)%HEIGHT][(j+1)%WIDTH];
	  v[2]=img[(i+1)%HEIGHT][j];
	  v[3]=img[(i+1)%HEIGHT][(j-1)%WIDTH];
	  int comp=0;
	  for (int i=0;i<4;++i)
	    {
	      if( v[i]==r->voisins[i])	
		comp++;  
	    }
	  if (comp==4)
	    {
	      return 1;
	    }
	      
	}
      else  if (r->dy==1)
	{
	  int v[4];
	  v[0]=img[(i+1)%HEIGHT][(j+1)%WIDTH];
	  v[1]=img[(i+1)%HEIGHT][j];
	  v[2]=img[(i+1)%HEIGHT][(j-1)%WIDTH];
	  v[3]=img[i][(j-1)%WIDTH];
	  int comp=0;
	  for (int i=0;i<4;++i)
	    {
	      if( v[i]==r->voisins[i])	
		comp++;  
	    }
	  if (comp==4)
	    {
	      return 1;
	    }
	}
      else
	{
	  int couleur=w->t[i*WIDTH+j];
	  if (couleur==r->couleur)
	    {
	      if (w->t[((i+1)%HEIGHT)*WIDTH+j%WIDTH]==NOIR)
		return 1;
	    }
	}
    }
  return 0;
}
