#include<stdio.h>
#include<stdlib.h>
#include "world.h"
#include"rule2.h"
#include<getopt.h>
#include<time.h>
#include<unistd.h>
#define BLANC 16777215
#define NOIR 0
#define BLEU 16711680
#define ROUGE 255
#define JAUNE 65535
#define GRIS 6579300
#define GRISE 1579300

struct world world;
struct world world1;


void world_init(struct world *w)
{
  
  for (int i=0; i<HEIGHT*WIDTH; ++i)
    {
      w->t[i]=(rand()%2)*JAUNE;
    }  
  w->t[(WIDTH/2+HEIGHT/3*WIDTH)%(HEIGHT*WIDTH)]=JAUNE;w->t[(WIDTH/2+HEIGHT/3*WIDTH+1)%(HEIGHT*WIDTH)]=JAUNE;
  w->t[(WIDTH/2+HEIGHT/3*WIDTH+2)%(HEIGHT*WIDTH)]=JAUNE;w->t[(WIDTH/2+(HEIGHT/3-1)*WIDTH+1)%(HEIGHT*WIDTH)]=JAUNE;
  w->t[(WIDTH/2+(HEIGHT/3+1)*WIDTH)%(HEIGHT*WIDTH)]=GRIS;w->t[(WIDTH/2+(HEIGHT/3+1)*WIDTH+1)%(HEIGHT*WIDTH)]=GRIS;
  w->t[(WIDTH/2+(HEIGHT/3+1)*WIDTH+2)%(HEIGHT*WIDTH)]=GRIS;
  int a=(WIDTH*(HEIGHT-1)+(WIDTH/2+3));
  while(a<WIDTH*HEIGHT)
    {
    w->t[a]=GRIS;
    ++a;
    }
  for (int j=0; j<WIDTH/2 ;++j)
    w->t[(WIDTH*(HEIGHT-1)+j)%(HEIGHT*WIDTH)]=GRIS;
  
 
 
}




void queue_append(struct world *w, struct rule* rule, int x, int y, int a)
{ 
  if (a==1)
    {
      int x_new=(rule_change_dx(rule, x))%HEIGHT;
      int y_new=(rule_change_dy(rule, y))%WIDTH;

      w->t[x*WIDTH+y]=x_new*WIDTH+y_new;

    }
  if (a==0)
    {
      w->t[x*WIDTH+y]=x*WIDTH+y;
    }    
}



void world_apply(struct world *w, struct world* m, int x)
{
  w->t[m->t[x]]=w->t[x];
  if (m->t[x]!=x)
    w->t[x]=0;
}









void afficher_image(struct world w)
{
  printf("\n#");
    for (int i =0; i<HEIGHT; ++i)
      {
       	printf("\n");
	for (int j=0; j<WIDTH; ++j)
          {
            printf("%d ", w.t[i*WIDTH+j]);
          }
      }
}


int main(int argc, char* argv[])
{
  
   char stropt[]="ms";
   int c; int iterations=10;int seed=time(NULL);
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
   printf("%d %d", WIDTH,HEIGHT);
   afficher_image(world);
  for (int z=0; z<iterations; ++z)
    {
      //queue_init(&file);
 
      for (int i=0; i<HEIGHT*WIDTH; ++i)
	{
	  int l=i/WIDTH;
	  int c=i%WIDTH;
	  int a;
	  int comp=0;
	  for (int j=0; j<rules_count(); ++j)
	    {
	      if(comp==0)
		{
		  struct rule* p=rule_get(j);
		  a=rule_match(&world, p,l,c);
		  queue_append(&world1,p,l,c, a);
		  if(a==1)
		    ++comp;
		}

	    }
	}
	
      for (int k=0; k<HEIGHT*WIDTH;++k)
	world_apply(&world, &world1,k);
      afficher_image(world);
    }
    
  return 0;
}
  
