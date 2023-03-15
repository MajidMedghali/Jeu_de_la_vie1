#include<stdio.h>
#include<stdlib.h>
#include "world.h"
#include"rule1.h"
#include<time.h>
#include<getopt.h>
#include<unistd.h>
#define BLANC 16777215
#define NOIRE
#define BLEU 16711680
#define ROUGE 255

struct file file;

struct world world={};
struct world world1={};


//struct world world={{n,n,n,n,b,n,n,b,b,b,n,b,b,b,n,n,n,b,n,b,n,b,b,n,b}};


void world_init(struct world *w)
{
  for (int i=0; i<HEIGHT*WIDTH; ++i)
    {
      w->t[i]=(rand()%2)*BLANC;
    }
}




struct file{
  int indebut;
  int infin;
  int val[HEIGHT*WIDTH];
};


struct file file;

void remplir_image(struct world w, int img[HEIGHT][WIDTH])
{
  for (int i=0; i<HEIGHT; ++i)
    {
      for (int j=0; j<WIDTH; ++j)
	{
          img[i][j]=w.t[i*WIDTH+j];
        }
    }
}




void defiler(struct file *f)
{
  f->indebut=( ( (f->indebut)+1) % (HEIGHT*WIDTH) );
}



void enfiler(struct file *f, int a)
{
  f->infin=( ( (f->infin)+1) % (HEIGHT*WIDTH) );
  f->val[f->infin]=a;
}



void queue_init(struct file *f)
{
  f->indebut=0;
  f->infin=HEIGHT*WIDTH-1;
  for (int i=0; i<HEIGHT*WIDTH; ++i)
    f->val[i]=0;
}




void queue_append(struct world *w, struct rule* rule, int x, int y)
{
  int a=rule_match(&world, rule,x,y);
  if (a==1)
    {
      // defiler(f);
      int n=rand()%3;
      int couleur_new=rule_change_to(rule,n);
      // enfiler(f,couleur_new);
      w->t[x*WIDTH+y]=couleur_new;
    }
  if (a==0)
    {
      //defiler(f);  
      //enfiler(f, world.t[x*WIDTH+y]);
      w->t[x*WIDTH+y]=world.t[x*WIDTH+y];
    }
}





void world_apply(struct world *w, struct world m, int x)
{
          w->t[x]=m.t[x];
}







void afficher_image(int image[HEIGHT][WIDTH])
{
  printf("\n#");
    for (int i =0; i<HEIGHT; ++i)
      {
       	printf("\n");
	for (int j=0; j<WIDTH; ++j)
          {
            int img=*(*(image+i)+j);
            printf("%d ", img);
          }
      }
}

/*void afficher_file(struct file f )
{
  if(f.infin>f.indebut)
    {
      for (int i=f.indebut; i<=f.infin; ++i)
        printf("%d ", f.val[i]);
    }
  else
    {
      for (int j=f.indebut; j<HEIGHT*WIDTH; ++j)
	printf("%d ", f.val[j]);
      for (int i=0; i<=f.infin; ++i)
        printf("%d ",f.val[i]);
    }
  printf("\n");
}


*/		    









int main(int argc, char* argv[])
{
  
   char stropt[]="ms";
   int c; int iterations;int seed;
   while((c=getopt(argc,argv,stropt))!=EOF){
     switch(c){
     case 'm':
       iterations=atoi(argv[optind]);
     break;
     case 's':
       seed=atoi(argv[optind]);
       break;}}
       
       srand(seed);
   world_init(&world);
  int image[HEIGHT][WIDTH];
  remplir_image(world, image);
  printf("%d %d", WIDTH,HEIGHT);
  afficher_image(image);
  for (int z=0; z<iterations; ++z)
    {
      //queue_init(&file);
 
      for (int i=0; i<HEIGHT*WIDTH; ++i)
	{
	  int l=i/WIDTH;
	  int c=i%WIDTH;
	  for (int j=0; j<rules_count(); ++j)
	    {
	      struct rule* p=rule_get(j);
	      queue_append(&world1,p,l,c);
	    }
	}
	
      for (int k=0; k<HEIGHT*WIDTH;++k)
	world_apply(&world, world1,k);
      int image_new[HEIGHT][WIDTH];
      remplir_image(world, image_new);
      afficher_image(image_new);
    }
    
  return 0;
}
  
