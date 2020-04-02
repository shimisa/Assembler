#include "uti1.h"
#include "func1Lab.h"


extern int opCode; /*operation code*/


void ent(char *li){/*to handle the entry guides-create a list*/

  symbal *tmp=sym;
  symbal *tmp2;
  boolean isExist=no;
  int i; 

   li = del_first_spaces(li);

   if(*li == '\0')
	error("Label is Missing");     

   if(strlen(li)>MAX_LABEL){
          
           error("Label is too long (more then 30 chars)");
         
   }
   for(i=1; i<MAX_LINE || li[i]=='\0'; i++){
	if(li[i]==' ' || li[i]=='\n' || li[i]=='\t')
		break;

   } 

   while(tmp){

      if(! strncmp(li,tmp->sym_name,i)){
          isExist=yes;
          
          if(tmp->isExt)
		error("This label is external");
          else{
		tmp2=(symbal *)malloc(sizeof(symbal));	/*create the list of the entry labels*/	
                if(! tmp2){
	             printf("no memmory");
	             break;
                }
                tmp2->next=entHead;
                entHead=tmp2;
		
                clean_label_name(entHead->sym_name);
		entHead->address=tmp->address;
		strcpy(entHead->sym_name,tmp->sym_name);

         }

     }
     tmp=tmp->next;


   }
   if( isExist==no)
	error("This label isn't exist");   
 

}/*end of ent*/


 int isLabel2(char *li){

    int i;


    li = del_first_spaces(li);	

    for(i=0; i<MAX_LINE; i++){

        if(li[i] == ':')
		return 1;
	
    }
    return 0;


 }

/*if its a label*/
void label2(char *li){

    int i;
    for(i=0; i<MAX_LINE; i++){

        if(li[i] == ':'){
	   analize2(li+i+1); /*go again to analize2*/
	   return;     
        }

    }


}


void op2(char *li){  /*the second transition on the operations--classified and allocate memmory--machine words*/
 
   symbal *tmp=sym;
   symbal *ext;
   int i;
   li = del_first_spaces(li);

   if(opCode == 14 || opCode == 15){ /*operations with no operands*/
	I++;
	return;
   }

   if(opCode <=13 && opCode >= 5){ /*operations with one operand*/

        if(inst_table[I].dest_op0){ /*for method 0*/
		/*printf(" %d\n",atoi(li+1));*/
		inst_table[I].next->w=atoi(li+1); /*convert the immediate number*/
                inst_table[I].next->A=1;
        }

        if(inst_table[I].dest_op1){
		tmp=sym;
		for(i=0; li[i]!='\0'; i++)
			if(li[i] == ' '||li[i] == '\n')
				break;
                while(tmp){

                   if(! strncmp(li,tmp->sym_name,i)){
			/*printf(" %s\n",tmp->sym_name);*/	 
                         inst_table[I].next->w=tmp->address;
		         if(tmp->isExt){
				inst_table[I].next->E=1;
				ext=(symbal *)malloc(sizeof(symbal));
				if(! ext){
					printf("cannot allocate for ext");
					return;
				}
				ext->next=extHead;
				extHead=ext;

				clean_label_name(extHead->sym_name);
				strncpy(extHead->sym_name,tmp->sym_name,i);
				extHead->address=inst_table[I].next->address;
			 }
			 else
				inst_table[I].next->R=1;
                         break;

                   }
                   tmp=tmp->next;

                }
	   
        }
        
        if(inst_table[I].dest_op3){
		inst_table[I].next->w=atoi(li+1);
		/*printf(" %d\n",atoi(li+1));*/
                inst_table[I].next->A=1;
	}
	if(inst_table[I].dest_op2){
		inst_table[I].next->w=atoi(li+2);
		/*printf(" %d\n",atoi(li+2));*/
                inst_table[I].next->A=1;
	}
    
        I++;
	return; 
   }/*end of operations with one operand*/

   else{ /*operations with two operands*/
      
       if((inst_table[I].dest_op2 && inst_table[I].sour_op3) || (inst_table[I].dest_op3 && inst_table[I].sour_op2) || (inst_table[I].dest_op2 && inst_table[I].sour_op2) || (inst_table[I].dest_op3 && inst_table[I].sour_op3)){

		
		for(i=0; li[i]!='\0'; i++){
			if(li[i]=='r'){
				inst_table[I].next->w=atoi(li+i+1);
				inst_table[I].next->w=inst_table[I].next->w << 3;
				/*printf("\n%d ",atoi(li+i+1));*/
				inst_table[I].next->A=1;
				li+=i+1;
				break;
			}
		}
		for(i=0; li[i]!='\0'; i++){
			if(li[i]=='r'){
				inst_table[I].next->w+=atoi(li+i+1);
                               /* printf(" %d\n",atoi(li+i+1));*/
				inst_table[I].next->A=1;
				li+=i;
				break;
			}
		}		
		

       }
	else{    /*operations with two operands and two machine words*/
		 if(inst_table[I].sour_op3){
			inst_table[I].next->w=atoi(li+1);
			/*printf(" %d\n",atoi(li+1));*/
			inst_table[I].next->w=inst_table[I].next->w << 3;
               		inst_table[I].next->A=1;
		}
		if(inst_table[I].sour_op2){
			inst_table[I].next->w=atoi(li+2);
			/*printf(" %d\n",atoi(li+2));*/
			inst_table[I].next->w=inst_table[I].next->w << 3;
                	inst_table[I].next->A=1;
		}

       		if(inst_table[I].sour_op0){

			for(i=0; li[i]!='\0'; i++){
				if(li[i]=='#'){
					inst_table[I].next->w+=atoi(li+i+1);
					/*printf(" %d\n",atoi(li+i+1));*/
					inst_table[I].next->A=1;
					li+=i+1;
					break;
				}
			}
		
       		}
      
       		if(inst_table[I].sour_op1){
			tmp=sym;
			for(i=0; li[i]!='\0'; i++)
				if(li[i] == ','||li[i] == ' ')
					break;
			while(tmp){

                   		if(! strncmp(li,tmp->sym_name,i)){
				/*printf(" %s\n",tmp->sym_name);*/
                         	inst_table[I].next->w=tmp->address;
		         	if(tmp->isExt){
					inst_table[I].next->E=1;
					ext=(symbal *)malloc(sizeof(symbal));
					if(! ext){
						printf("cannot allocate for ext");
						return;
					}
					ext->next=extHead;
					extHead=ext;

					clean_label_name(extHead->sym_name);
					strncpy(extHead->sym_name,tmp->sym_name,i);
					extHead->address=inst_table[I].next->address;
			 
				}	
			 	else
					inst_table[I].next->R=1;
                        	 break;

                   	}
                   	tmp=tmp->next;

                	}
		

      		}
		li=find_comma(li);
		li+=1;
		li = del_first_spaces(li);

		if(inst_table[I].dest_op3){
			

			inst_table[I].next->next->w=atoi(li+1);
			/*printf(" %d\n",atoi(li+1));*/
                	inst_table[I].next->next->A=1;
		}
		if(inst_table[I].dest_op2){


			inst_table[I].next->next->w=atoi(li+2);
			/*printf(" %d\n",atoi(li+2));*/
                	inst_table[I].next->next->A=1;
		}

		if(inst_table[I].dest_op0){
			for(i=0; li[i]!='\0'; i++){
				if(li[i]=='#'){
					inst_table[I].next->next->w+=atoi(li+i+1);
					/*printf(" %d\n",atoi(li+i+1));*/
					inst_table[I].next->next->A=1;
					break;
				}
			}

       		}
      		if(inst_table[I].dest_op1){
			tmp=sym;
       
			for(i=0; li[i]!='\0'; i++)
				if(li[i] == ' '||li[i] == '\n')
					break;	
			while(tmp){

                   	if(! strncmp(li,tmp->sym_name,i)){
				/*printf(" %s\n",tmp->sym_name);*/
                         	inst_table[I].next->next->w=tmp->address;
		         	if(tmp->isExt){
					inst_table[I].next->next->E=1;
					ext=(symbal *)malloc(sizeof(symbal));
					if(! ext){
						printf("cannot allocate for ext");
						return;
					}
					ext->next=extHead;
					extHead=ext;

					clean_label_name(extHead->sym_name);
					strncpy(extHead->sym_name,tmp->sym_name,i);
					extHead->address=inst_table[I].next->next->address;
			 
				}
			 	else
					inst_table[I].next->next->R=1;
                         	break;

                   	}
                   	tmp=tmp->next;

                	}

      		}
		

	}/*end of else*/
	

      
       
       
     
   }/*end of operations with two operands*/

   I++;

}/*end of op2*/










