#include "uti1.h"
#include "func1Lab.h"
#include "stat_tables.h"



int opCode; /*operation code, only relible if the operation is legal*/

/*function to know if its a label in the begining*/
 int isLabel(char *li){
  
    int i;
    char *p;

    li = del_first_spaces(li);	

    for(i=0; i<MAX_LINE; i++){

        if(li[i] == ':')
		return 1;
	else if(li[i] == ' '){
		p=li;
		p=del_first_spaces(p);
		if(li[i] != '\0'){
			error("Missing  :  for lable");
			*(p-1)=':';
			return 1;
		}
	}
    }
    return 0;
 }





/*if its a label then do things*/
 void label(char *li){
   char *p;
   symbal *tmp;
   int i;
	
    for(i=0; i<MAX_LINE; i++){

        if(li[i] == ':'){
	   if(i > MAX_LABEL){
		error("Lable is too long (more then 30 chars)");
           }
           else{
                tmp=(symbal *)malloc(sizeof(symbal));
                if(! tmp){
	             printf("no memmory");
	             break;
                }
                tmp->next=sym;
                sym=tmp;
		clean_label_name(sym->sym_name);
	        strncpy(sym->sym_name,li,i);
	        
           }
           p=(li+i+1);
           p=del_first_spaces(p);
           
           if(*p == '.'){  /*if its guide statement*/
           
               sym->address=DC;   
               sym->isGuide=yes;
               sym->isExt=no;
		/*printf("\n%s\n",p);*/
		if(! strncmp(p,".entry",6))
			error("Imossible entry guide after lable");
		else if(! strncmp(p,".extern",7))
			error("Imossible extern guide after lable");
		else
                 analize1(p);  /*go again to analize to find out if its data or string*/
		
           }
           else{  /*if its instruction statement*/
              sym->address=IC;
              sym->isGuide=no;
              sym->isExt=no;              
              analize1(p);/*go again to analize to find out which instruction statement*/
           }
                          
       }
          
   }

 }


 int isOp(char * li){

    int i;

    for(i=0; i<NUM_OF_OP-1; i++){ /*without stop op*/
   
       if(! (strncmp(li,op_method[i][2],3))){  /*if the operation exist return true--1*/
           opCode=i;
	   return 1;            
       }
       
    }
    return 0;

}/*end of isOp method*/

 int isStop(char *li){

    if(! (strncmp(li,"stop",4))){
	/*printf("\nstop\n");*/
       opCode=15;  
       return 1;
    }

  
    return 0;

 }/*end of isStop method*/


 void op(char *li){/*first transition of the operations*/
    int k;
    int s;
    int j;
    char oper[MAX_LINE-4];
    char *p=oper;
    char sou_met;    /*method of addrresing operand source*/
    char dest_met=' ';  /*method of addrresing operand destanation*/
    int i=0;
    boolean isSou=no;
    boolean isDest=no;
    word *tmp;
 
    boolean missComma=0;
 
   

    for(k=0; li[k] == ' ' || li[k] == '\t' ; k++);
    strcpy(oper,li+k);
    /*printf("%s",oper);*/


   for(k=0; p[k] != '\0'&& p[k] != '\n' ; k++){

	if(p[k] == ' '){
 		while(p[k] == ' ' || p[k] == '\t')
			k++;
		
		if(p[k] == ','){
			k++;
			while(p[k] == ' ' || p[k] == '\t')
			k++;
			
			if(p[k] == '\0')
				break;

		}
		else if(p[k] != '\0' && p[k] != '\n'){
			error("Missing comma");
			/*printf("\n%c\n",p[k]);*/
			missComma=yes;
			
		}
				
		
	}
	else if(p[k] == ','){	
		k++;
		while(p[k] == ' ')
		k++;
	}

   
   }
	


    if(missComma){
	
	for(s=0; li[s] == ' ' || li[s] == '\t' ; s++);
	for(s=s; li[s] != ' ' && li[s] != '\t' ; s++);
	/*printf("\n%c\n",*(li+s));*/
	*(li+s)=',';
      	
    }

    

    sou_met=address_met(li); /*discover the address method of sou*/


    for(j=0; li[j] != '\0'; j++){
		if(li[j] == ','){  
                        dest_met=address_met(li+j+1); /*if thre is a comma, discover the address method of dest*/
			break;
                }
		
    }


    

    if(li[j] == '\0'){ /*if there isnt comma then the only operand is dest*/
     
       dest_met=sou_met;
       sou_met=' ';
    }
 
    while((op_method[opCode][1])[i] != '\0'){ 

       if((op_method[opCode][1])[i] == sou_met) /*check if the specific op suppurt the add method for sou*/
		isSou=yes;
       i++;

   }   
   i=0;
   while((op_method[opCode][0])[i] != '\0'){

       if((op_method[opCode][0])[i] == dest_met)/*check if the specific op suppurt the add method for dest*/
		isDest=yes;
       i++;
   } 
    /*if not rise an error*/
   if(! isSou) 
	error("Wrong method for source operand"); 
   
   if(! isDest) 
	error("Wrong method for destination operand");

   /*if there is 2 operands and both of them 3 or 4 add method, they share the same memmory word--allocate one more word */
   if((sou_met == '3'&& dest_met == '2') || (dest_met == '3'&& sou_met == '2') || (sou_met == '3'&& dest_met == '3') || (dest_met == '2'&& sou_met == '2')){ 

      tmp=(word *)malloc(sizeof(word)); 
      if(! tmp){
	printf("cannot alocate memmory");
	return;	
      }
      tmp->next=inst_table[I].next;       
      inst_table[I].next=tmp;

      inst_table[I].role=4; /*its absolute*/
      inst_table[I].address=IC; /*give address*/
      IC++;
      inst_table[I].next->address=IC;
      IC++;
      inst_table[I].op_code=opCode;
      
      if(sou_met == '3'&& dest_met == '2'){/*printf("\n%d\n",2);*/
		inst_table[I].sour_op3=1;
                inst_table[I].dest_op2=1;
      }
      else if(sou_met == '2'&& dest_met == '3'){
		inst_table[I].sour_op2=1;
                inst_table[I].dest_op3=1;
      }
      else if(sou_met == '2'&& dest_met == '2'){
		inst_table[I].sour_op2=1;
                inst_table[I].dest_op2=1;
      }
      else{
		inst_table[I].sour_op3=1;
                inst_table[I].dest_op3=1;
      }
      
   }

  /* if there is just one operand then--allocate one more word*/
   else if(sou_met == ' ' && dest_met != ' '){

      tmp=(word *)malloc(sizeof(word)); 
      if(! tmp){
	printf("cannot alocate memmory");
	return;	
      }
      tmp->next=NULL;       
      inst_table[I].next=tmp;

      inst_table[I].role=4; /*its absolute*/
      inst_table[I].address=IC; /*give address*/
      IC++;
      inst_table[I].next->address=IC;
      IC++;
      inst_table[I].op_code=opCode;
     
      if(dest_met == '0')
	inst_table[I].dest_op0=1;
      else if(dest_met == '1')
	inst_table[I].dest_op1=1;
      else if(dest_met == '2')
	inst_table[I].dest_op2=1;
      else
	inst_table[I].dest_op3=1;

   }
   /*if there isnt operands then no need of more memmory words--don't allocate one more word*/
   else if((sou_met == ' ' && dest_met == ' ')){
      inst_table[I].role=4; /*its absolute*/
      inst_table[I].address=IC; /*give address*/
      IC++;
      inst_table[I].op_code=opCode;
      inst_table[I].next=NULL;
   }

   else { /*allcate two more memmory words*/

     tmp=(word *)malloc(sizeof(word)); 
     if(! tmp){
	printf("cannot alocate memmory");
	return;	
     }
     tmp->next=NULL;       
     inst_table[I].next=tmp;
    
     tmp=(word *)malloc(sizeof(word)); 
     if(! tmp){
	printf("cannot alocate memmory");
	return;	
     }
     tmp->next=inst_table[I].next;       
     inst_table[I].next=tmp;
  
     inst_table[I].role=4; /*its absolute*/
     inst_table[I].address=IC; /*give address*/
     IC++;
     inst_table[I].next->address=IC;
     IC++;
     inst_table[I].next->next->address=IC;
     IC++;
     inst_table[I].op_code=opCode;

     if(dest_met == '0')  /*for dest*/
	inst_table[I].dest_op0=1;
     else if(dest_met == '1')
	inst_table[I].dest_op1=1;
     else if(dest_met == '2')
	inst_table[I].dest_op2=1;
     else
	inst_table[I].dest_op3=1;

      
     if(sou_met == '0')  /*for sour*/
	inst_table[I].sour_op0=1;
     else if(sou_met == '1')
	inst_table[I].sour_op1=1;
     else if(sou_met == '2')
	inst_table[I].sour_op2=1;
     else
	inst_table[I].sour_op3=1;

   }
   I++;
  

   
 }/*end of op method*/



 char address_met(char *li){  /*address method*/
  
    int i=2;

    li = del_first_spaces(li);

    if(*li == '#'){
        if(li[1]<47 || li[1]>58){ /*if after the # its no a number so rise an error*/
		if(li[1] != '-' && li[1] != '+')
		   error("Invalid parameter for immediate address");
	}
        else{
           while(li[i] != ' ' && li[i] != ',' && li[i] != '\0'&& li[i] != '\n'&& li[i] != '\t'){
	      if(li[i]<47 || li[i]>58){   /*if after the # its no a number so rise an error*/
		      error("Invalid parameter for immediate address");
                      break;
              }
              i++;
           }  
        }
	return '0'; /*immediate address*/
    }
    else if(*li == '*'){ /*indirect register address*/
	if(!(*(li+1) == 'r'))
		error("Invalid parameter for indirect address");
	else if(!(*(li+2)>47 && *(li+2)<56)) /*if the register ins't between 0-7*/
		error("Invalid register for indirect address");
	return '2';
    }

    else if(*li == 'r'){ /*direct register address*/
	if(!(*(li+1)>47 && *(li+1)<56)) /*if the register ins't between 0-7*/
		error("Invalid register for direct address");
	return '3';
	
    }

    else if(*li > 20 && *li < 127) /*direct address, the operand is a label*/
		return '1';
                
            		
    else
	return ' ';


    

 }/*end of address_met*/





 void ext(char *li){/*handle the external guides*/
   symbal *tmp;
   int i;

   li = del_first_spaces(li);

   if(*li == '\0')
	error("Label is Missing");

   for(i=0; li[i] != '\0' && li[i] != '\n' && li[i] != ' '; i++);
     
   if(i>MAX_LABEL){
          
           error("Label is too long (more than 30 chars)");
         
   }        
   

   tmp=(symbal *)malloc(sizeof(symbal));
   if(! tmp){
	printf("cannot allocate memmory for ext");
	return;	
   }	

   tmp->next=sym;
   sym=tmp;
   clean_label_name(sym->sym_name);
   strncpy(sym->sym_name,li,i);
   sym->isExt=yes;
   sym->address=0;
   

 }/*end of ext*/





/*functions to fill the data table*/
 void numData(char * li){  /*for numbers*/

  int a[MAX_LINE];  /* temp array of ints for storing the input numbers */
  char b[MAX_LINE]; /* temp array of chars for storing the input numbers */
  int i=0;
  int j;
  Dword *tmp;


  li=del_first_spaces(li); /* removing spaces */

  /* analize, fill the auxiliary array of chars b and give relevant massages */
 
  if(*li == '\0')
  {
    error("Missing parameters");
  }

 
 
  while(*li != '\0')
  {  


   if(*li == '-'){

       b[i]='-';
       i++;
       li++;
       if(!(*(li)>47 && *(li)<58))
	 error("Invalid parameter");
   }
   else if(*li == '+')
	li++;
      

   li=del_first_spaces(li);

   while((*li>47 && *li<58))
   { 
 
       
          b[i]=*li;
          i++;
          li++;
        
        
   }

   li=del_first_spaces(li);
   
   if(*li == ',')
   {
     b[i]=',';
     i++; 
     li=del_first_spaces(li+1);

     if(*(li+1) == ',')
     {
       error("Multiple consecutive commas");
       
     }
                               

   }

   else{
     li=del_first_spaces(li);
     if((*li>47 && *li<58))
	error("Missing comma");
     li++;
   }


  

   }/* end of while loop */





   /*for(j=0; j<i; j++)
   {
     
      printf("\n %c \n",b[j]);
   }*/


 
  /* convert the chars array to integers and fill the int array */

  j=0;
  int z=0;
  int cnt=1;

  while(j<i)
  {
     a[z]=0;
     if(b[j] != ',')     
     {
       a[z]=atoi(b+j);
	/*printf("\n%s\n",atoi(b+j));*/
       j++;
       z++;
     }
     if(b[j] == ',')
       	cnt++;
     j++;

    
 
    
      
  
  }

  /*for(j=0; j<cnt; j++)
  {
     
     printf("\n %d \n",a[j]);
  }*/



      DC+=cnt;
      z=1;

      for(j=cnt-1; j>=0; j--){
        

           tmp=(Dword *)malloc(sizeof(Dword));
           if(! tmp){
  	         printf("cannot alocate memmory");
	         return;	
           }
           tmp->next=data_table[D];
           data_table[D]=tmp;
      
      
           data_table[D]->w=a[j];
           data_table[D]->address=DC-z;
           z++;
           
        

     }

     D++;
      
     


   
 

 }/*end of numData*/

 void strData(char * li){   /*for strings*/

   int i=0;
   int j=2;
   char *l=del_first_spaces(li);
   Dword *tmp;

  
   if(l[0] != '"')
	error("Syntax error--missing");
   
    while(l[i] !='\0' && l[i] !=' '){

       i++;
    }
    if(i>MAX_STRING)
	error("String is too long (more then 75 chars)");
    if(l[i-2] != '"')
	error("Syntax error--missing ");
    
    DC+=i-2;
    /*printf("\n%d\n",DC);*/

    if(i>3) /*if its leggal string*/
	i=i-3;

     tmp=(Dword *)malloc(sizeof(Dword));
     if(! tmp){
  	     printf("cannot alocate memmory");
	     return;	
      }
      data_table[D]=tmp;
      tmp->next=NULL;
      data_table[D]->w=0;
      data_table[D]->address=DC-1;


    for(i=i; i>=1; i--){
      
       tmp=(Dword *)malloc(sizeof(Dword));
       if(! tmp){
  	     printf("cannot alocate memmory");
	     return;	
      }
      tmp->next=data_table[D];
      data_table[D]=tmp;
      
      
      data_table[D]->w=l[i];
      data_table[D]->address=DC-j;
      j++;

     
    }
 
    
   D++;
   

 }

 void fix_sym_add(){ /*update the symbals address in the symbal list*/

   symbal *tmp=sym;
   
   while(tmp){

      if(tmp->isGuide){
          tmp->address+=IC;
      }
      tmp=tmp->next;

   }
 }



 









