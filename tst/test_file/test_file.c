#include<stdio.h>
#include<stdlib.h>
#include"world.h"
#include"rule.h"
#include"file.h"
#define n 0
#define b 16777215



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

struct file f;
int main(){
  printf("-------------------test_de_la_file------------------");
  printf(" \n on enfile 2 et 3 et 5 on obtient.\n");
    enfiler(&f,2);
  enfiler(&f,3);
  enfiler(&f,5);
   afficher_file(f);
  printf("si on defile\n");
  defiler(&f);
  afficher_file(f);
  printf("si on enfile 8\n ");
  enfiler(&f,8);
 
  afficher_file(f);
 
}
