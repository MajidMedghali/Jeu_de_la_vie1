#include<stdio.h>
#include"world.h"
#include"file.h"
#include <stdlib.h>





struct element 
{
  int val;
  struct element* suivant;
};


//-----------------------------------------//

struct file
{
  struct element* premier;
};
//----------------------------------------//

void enfiler(struct file* f, int nbre)
{
  struct element* nouveau;
  nouveau=malloc(sizeof(*nouveau));
  nouveau->val=nbre;
  nouveau->suivant=NULL;
  if(f->premier != NULL)
    {
      struct element* dernier=f->premier;
      while (dernier->suivant != NULL)
	{
	  dernier=dernier->suivant;
	}
      dernier->suivant=nouveau;
    }
  else
    f->premier=nouveau;
}
//------------------------------------------------------//

int defiler(struct file* f)
{
      int element_defile=f->premier->val;
      f->premier=f->premier->suivant;
      return element_defile;
}

//-----------------------------------------------//

void afficher_file(struct file f)
{
  struct element* actuel=f.premier;
  printf("etat de la file: ");
  while (actuel!=NULL)
    {
      printf("%d ",actuel->val);
      actuel=actuel->suivant; 
    }
  printf("\n");
}
