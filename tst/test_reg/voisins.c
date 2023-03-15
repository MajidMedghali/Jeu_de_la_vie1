#include<stdio.h>

#include<stdlib.h>
//#include"rule.h"
#include"voisins.h"


struct world_test
{
  int t[9];
};


void world_init(struct world *w){
  for(int i=0; i<3*3; i++)
    w->t[i]=(rand()%2)*b;
 }

struct rule
{
  int couleur;
  int couleur_voisin;
  int couleur_new;
  int regle[8];
};


void remplir_image1(const struct world_test* w, int img[3][3])
{
  for (int i=0; i<3; ++i)
    {
      for (int j=0; j<3; ++j)
	{
	  img[i][j]=w->t[i*3+j];
	}
    }  
}


/*--------------------------------------------------------------*/
void afficher_image(struct world_test w)
{
  printf("\n#");
    for (int i =0; i<3; ++i)
      {
       	printf("\n");
	for (int j=0; j<3; ++j)
          {
            printf("%d ", w.t[i*WIDTH+j]);
          }
      }
}
/*--------------------------------------------------------------*/
		  
int rule_match(const struct world_test* w,const struct rule* r
               ,unsigned int i, unsigned int j)
{
  int img[3][3];
  remplir_image1(w,img);
  int v[8];
  v[0]=img[(i-1)%3][(j-1)%3];
  v[1]=img[(i-1)%3][j];
  v[2]=img[(i-1)%3][(j+1)%3];
  v[3]=img[i][(j+1)%3];
  v[4]=img[(i+1)%3][(j+1)%3];
  v[5]=img[(i+1)%3][j];
  v[6]=img[(i+1)%3][(j-1)%3];
  v[7]=img[i][(j-1)%3];
  int couleur=w->t[i*3+j];
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
/*-------------------------------------------------------------*/
