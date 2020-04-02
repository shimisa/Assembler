#include "uti1.h"
#include "mainLab.h"


char line[MAX_LINE]; /*array to get line by line*/
int line_num=0;
char *file_name;
FILE *fd;



int main(int argc, char *argv[])
{


 int i;
	
 if(argc == 1){
   printf("please enter file name");
   exit(0);
 }

 /*printf("\n%s\n",argv[2]);*/

 for(i=1; i<argc; i++)  /* loop for all the files the user input */
 {

  file_name=(char *)malloc(strlen(argv[i])+4);
  
  if(! file_name){
	printf("\ncannot allocate memmory for file_name\n");
	break;
  }

/* add the suffix .as to the file name */
  strcpy(file_name,argv[i]);  
  strcat(file_name,".as"); 

 printf("\n%s ",file_name); /*print to check if the file name is correct V */ 
	
  
/* open the specific file, and if not open so rise a massage */
  fd = fopen(file_name,"r");

  if(!fd){
    printf("\ncannot open %s file\n",file_name);
    break;
  }
  
  
  while(! feof(fd)){ /*first transition*/  

   /* printf("\n%s\n",line); print to check if it reads from the file to the array line  V */ 

    analize1(line); /*first analize*/
    line_num++;

    fgets(line,MAX_LINE,fd); /*get one line from the file V */

    
  
  }
   
  line[0]='\0'; /*empty the first element of the array*/
  rewind(fd); /*return the read pointer to the beggining of the text file for the sercond transition*/
  /*zero the parameters before the next analize*/
  line_num=0;
  clean_line(line);
  I=0;
  
  fix_sym_add(); /*update the address of the guide labels in the symbal table*/
  

  while(! feof(fd)){/*second transition*/
    
    analize2(line); /*second analize*/
    line_num++;

   fgets(line,MAX_LINE,fd);
  }   
  

  fclose(fd);  /*close file*/


  if(! errorC){  /*if there is no errors create the files, else- print the errors to screen*/
    create_ob_file();
    create_ent_file();
    create_ext_file();

    printf("Compiled\n");
  }
  
  else
    printErrors();

 /*printf("\n%c\n",data_table[0]->address);*/
 /*print_table_data(); */
 /*print_labels(sym);  /*print the labels names*/
 D=0; /*zero the data table i*/
 I=0; /*zero the inst table i*/
 DC=0; /*zero the data counter*/
 IC=100; /*zero to 100 the instruction counter*/
 line_num=0;
 clean_line(line);  /*clean the line array*/
 free(file_name);  /*free the file name parameter*/
 freeError();        /*free the error table*/
 free_table_data(); /*free all the data table*/
 free_table_op(); /*free operation table list*/
 free_symList(); /*free all the allocated nodes of the symball list*/
 free_entList();/*free entry list*/
 free_extList();/*free external list*/

 

 }/*end of for loop to open the files which givven from CMD by their names*/

 


 return 0;

} /*End of Main*/


