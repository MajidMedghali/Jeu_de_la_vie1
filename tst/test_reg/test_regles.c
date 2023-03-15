#include<stdio.h>
#include<stdlib.h>
#define NOIR 0
#define JAUNE 65535
#define GRIS 6579300

struct world_test
{
  int t[9];
};


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
            printf("%d ", w.t[i*3+j]);
          }
      }
}
/*--------------------------------------------------------------*/
int rule_match(const struct world_test* w,const struct rule* r,unsigned int i,
	       unsigned int j)
{
 
  int img[3][3];
  remplir_image1(w,img);
 
  int couleur=w->t[i*3+j];
  if (couleur==r->couleur)
    {
      if (r->dy==-1)
	{
	  int v[4];
	  v[0]=img[i][(j+1)%3];
	  v[1]=img[(i+1)%3][(j+1)%3];
	  v[2]=img[(i+1)%3][j];
	  v[3]=img[(i+1)%3][(j-1)%3];
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
	  v[0]=img[(i+1)%3][(j+1)%3];
	  v[1]=img[(i+1)%3][j];
	  v[2]=img[(i+1)%3][(j-1)%3];
	  v[3]=img[i][(j-1)%3];
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
	  int couleur=w->t[i*3+j];
	  if (couleur==r->couleur)
	    {
	      if (w->t[((i+1)%3)*3+j%3]==NOIR)
		return 1;
	    }
	}
    }
  return 0;
}



int main(int argc , char* argv[])
{
  printf("-------------------test_des_régles------------------\n");
  printf("Pour l'achievement 2 on prend les régles du sable\n");
  struct world_test w={{0,0,JAUNE,JAUNE,JAUNE,0,JAUNE,JAUNE,0}};
  printf("3 3");
  afficher_image(w);
  printf("\n\n on choisit la case (0,2), qui est jaune,  et on applique la régle qui correspond aux cases jaunes avec une case noire en dessous\n");

  int z=rule_match(&w ,&rule[0], 0,2);
  printf(" rule_match retounre %d\n", z);
  
  printf(" c-a-d la régle est vérifiée car la case en dessous de cette case est noire donc cette case doit avancer");


    
  printf("\n---------------------------------------------------- \n");
 
  printf("\n on s'interesse ici aux cases noires:\n  on choisit la case(1,2) et on applique pour n'importe quelle régle \n ");
  z=rule_match(&w,&rule[0],0,0);
  printf(" rule_match retounre %d\n", z);

  printf("  c-a-d cette case n'avance pas  \n");

  printf("\n---------------------------------------------------- \n");


  printf("\n on s'interesse ici aux cases jaunes avec 3 voisins jaunes: 2 en dessous et un à gauche\n  on choisit la case(1,1) et la régle qui correspond à cette situation\n");
  z=rule_match(&w,&rule[2],1,1);
  printf("  rule_match retounre %d\n", z);
  printf("  c-a-d la régle correspondant à cette situation est verifiée est donc cette case va se déplacer en bas et à droite\n");
    
  return 0;
}
  
