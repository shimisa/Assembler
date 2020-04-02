#include "uti1.h"

extern int line_num;
extern char *file_name;
int I;/*index of inst_table*/
int D;/*index of data_table*/
int IC=100;
int DC=0;


symbal *sym;
symbal *entHead;
symbal *extHead;


Dword *data_table[150]; /*data array*/
oWord inst_table[150]; /*instruction array*/


char *errors[150];
int errorC=0;



void error(char * string){/*create error table with the exact number line*/

  char *st;
  char lineNum[3];
  sprintf(lineNum,"%d",line_num);

  st=(char *)malloc(strlen(string)+20);
  if(!st){
  	printf("\nNo memmory for errors\n");
  	return;
  }
  errors[errorC]=st;
  strcpy(errors[errorC],string); /*fill the next element of the array with new erorr*/
  strcat(errors[errorC]," (line number:) ");
  strcat(errors[errorC],lineNum); /*concatenate to the line number*/ 
  errorC++;

}
/*function for printing all the errors to the screen after the two transitions*/
void printErrors(){
    int j;
  
   for(j=0; j<errorC; j++)
      printf("\n%s\n",errors[j]);
   
}

void freeError()/*free the alocated spaces in the error table*/
{
  int i;
  for(i=0; i<errorC; i++){

	free(errors[i]);
        errors[i]=NULL;        
  }
  errorC=0;



}


/*functions to create the three files---print the code divided to 3 bits every time as an octal number*/



 void create_ob_file(){
	
	int i;
	
	word *tmp;
	Dword *tmpD;
	fileName(".ob");
	FILE *fd = fopen(file_name,"w+");
	if(! fd){
		printf("Cannot create object FILE");
		return;
	}
	fprintf(fd,"   %d %d\n",IC-100,DC);/*fprint IC and DC*/

	for(i=0; i<I; i++){
		
		fprintf(fd," %d  %o",inst_table[i].address,inst_table[i].w5);
		fprintf(fd,"%o",inst_table[i].w4);
		fprintf(fd,"%o",inst_table[i].w3);
		fprintf(fd,"%o",inst_table[i].w2);
		fprintf(fd,"%o\n",inst_table[i].w1);
		

		tmp=inst_table[i].next;
		/*printf("\n%d\n",tmp);*/
		while(tmp){
			
			fprintf(fd," %d  %o",tmp->address,tmp->w5);
			fprintf(fd,"%o",tmp->w4);
			fprintf(fd,"%o",tmp->w3);
			fprintf(fd,"%o",tmp->w2);
			fprintf(fd,"%o\n",tmp->w1);

			tmp=tmp->next;
		}
		
	}/*end of for loop of inst_table*/

	for(i=0; i<D; i++){
	
		tmpD=data_table[i];

		while(tmpD){
	
			fprintf(fd," %d  %o",tmpD->address+IC,tmpD->w5);
			fprintf(fd,"%o",tmpD->w4);
			fprintf(fd,"%o",tmpD->w3);
			fprintf(fd,"%o",tmpD->w2);
			fprintf(fd,"%o\n",tmpD->w1);

			tmpD=tmpD->next;
		}
	}
		
	


	fclose(fd);
 }


 void create_ent_file(){

	symbal *symE=entHead;
	fileName(".ent");
	FILE *fd;
	if(! symE)
		return;

        fd = fopen(file_name,"w+");
	if(! fd){
		printf("Cannot create %s FILE",file_name);
		return;
	}

	while(symE){

		fprintf(fd," %s  %d\n",symE->sym_name,symE->address);

		symE=symE->next;
	}


	fclose(fd);


 } 


 void create_ext_file(){

	symbal *symE=extHead;
	fileName(".ext");
	FILE *fd;
	if(! symE)
		return;
	
	fd = fopen(file_name,"w+");
	if(! fd){
		printf("Cannot create %s FILE",file_name);
		return;
	}

	while(symE){

		fprintf(fd," %s %d\n",symE->sym_name,symE->address);

		symE=symE->next;
	}


	fclose(fd);
 }




