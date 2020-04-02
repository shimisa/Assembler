#include "uti1.h"

extern symbal *sym;
extern symbal *entHead;
extern symbal *extHead;

extern Dword *data_table[150];
extern oWord inst_table[150];
extern int D;
extern char *file_name;

  

char *del_first_spaces(char *c){

  while(*c == ' ' || *c == '\t')
	c++;
 
  return c;
}


void print_labels(symbal *sym)
{

  symbal *s=sym;
  while(s != NULL){

     printf("\n%s\n",s->sym_name);
     s=s->next;
     
  }
  

}




void print_table_data(){
   
   int i;
   Dword *tmp;
   for(i=0; i<D; i++){
     
       tmp=data_table[i];
      
       while(tmp){
          printf("\n%c--%d\n",tmp->w,tmp->address);
          printf("\n%d--%d\n",tmp->w,tmp->address);
	  printf("\n%o--%d\n",tmp->w,tmp->address);
	  tmp=tmp->next;
       }

   }
}


void free_table_data(){
   int i;
   Dword *tmp;
   Dword *tmp2;
   for(i=0; i<150; i++){
       tmp=data_table[i];
       tmp2=tmp;
      
       while(tmp2){

          tmp=tmp2;
	  tmp2=tmp2->next;
	  free(tmp);
	 
       }
       data_table[i]=NULL;

   }

}

void free_table_op(){
   int i;
   word *tmp;
   word *tmp2;
   for(i=0; i<150; i++){
      tmp=inst_table[i].next;
      tmp2=tmp;

      while(tmp2){

          tmp=tmp2;
	  tmp2=tmp2->next;
	  free(tmp);
	 
       }
	
	inst_table[i].w1=0;
	inst_table[i].w2=0;
	inst_table[i].w3=0;
	inst_table[i].w4=0;
	inst_table[i].w5=0;
        inst_table[i].next=NULL;
   }

}

void free_symList()
{
   symbal *tmp=sym;
   symbal *tmp2=tmp;
   
   while(tmp2){

      tmp=tmp2;
      tmp2=tmp2->next;
      free(tmp);
      
  }
  sym=NULL;

}


void free_entList()
{
   symbal *tmp=entHead;
   symbal *tmp2=tmp;
   
   while(tmp2){

      tmp=tmp2;
      tmp2=tmp2->next;
      free(tmp);
      
  }
  entHead=NULL;

}


void free_extList()
{
   symbal *tmp=extHead;
   symbal *tmp2=tmp;
   
   while(tmp2){

      tmp=tmp2;
      tmp2=tmp2->next;
      free(tmp);
      
  }
  extHead=NULL;

}


void clean_line(char *l){
	int i;

	for(i=0; i<MAX_LINE; i++){
  
   		l[i]='\0';

	}

}

void clean_label_name(char *l){
	int i;

	for(i=0; i<MAX_LABEL; i++){
  
   		l[i]='\0';

	}

}

char *find_comma(char *l){
	
   int i;
   for(i=0; l[i]!='\0'; i++){
  
   	if(l[i]==',')
		break;
        
   }

return l+i;
}




void fileName(char *suffix){

	int i;

	for(i=0; file_name[i] != '.'; i++);

	strcpy((file_name+i),suffix);

	
}

  







