#include "uti1.h"


/*first transition*/
void analize1(char * l){

  char *l1 = del_first_spaces(l); /*l1 point on the array on the the place after the first spaces*/

  if(*l1 == ';' || *l1 == '\0' || *l1 == '\n')  /*ignore comments and empty lines*/
	return;


  if(! strncmp(l1,".entry",6))
	return;


  if(! strncmp(l1,".extern",7)){  /*if its extern*/
       ext(l1+7);
       return;
	
  }

  if(! strncmp(l1,".data",5)){
	numData(l1+5);
        return;
	
  }

  if(! strncmp(l1,".string",7)){
	strData(l1+7);
        return;
	
  }
  

  if(isOp(l1)){
        op(l1+3);
        return;
	
  } 
  if(isStop(l1)){ /*if it's stop operation*/
	op(l1+4);
        return;
  }

  if(isLabel(l1)){
	label(l1);
        return;
  }


  error("command not found");

  
  
 /* printf("\n%s\n",l1); check if ignore comments and empty lines and .enrty V */

}/*end of analize1*/



/*second transition*/
void analize2(char * l){
  
  char *l1 = del_first_spaces(l); /*l1 point on the array on the the place after the first spaces*/

  if(*l1 == ';' || *l1 == '\0' || *l1 == '\n')  /*ignore comments and empty lines*/
	return;

  
  if(! strncmp(l1,".entry",6)){
        ent(l1+6);
	return;

  }

  if(! strncmp(l1,".extern",7)){  /*if its extern dont do nothing this time*/
       return;
	
  }

  if(! strncmp(l1,".data",5)){
        return;
	
  }

  if(! strncmp(l1,".string",7)){
        return;
	
  }

  if(isLabel2(l1)){
	label2(l1);
        return;
  }

  if(isOp(l1)){
        op2(l1+3);
        return;
	
  }

  if(isStop(l1)){
        op2(l1+4);
        return;
	
  }

  

  
    

}/*end of analize2*/




