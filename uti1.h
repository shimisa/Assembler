#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 80
#define MAX_LABEL 31

/*strucures*/
typedef enum {no,yes} boolean;



typedef struct symbals{/*struct for the symbal table as a linked list*/
                  char sym_name[31];
                  unsigned address;
		  boolean isGuide;
                  boolean isExt;
                  struct symbals *next;

                                }symbal;

typedef union DmachineWord{ /*data machine word*/

struct { 
       
	int w : 15;
        unsigned :0;
	unsigned address;
        union DmachineWord *next;



};

struct { 
       
	unsigned w1 : 3;
	unsigned w2 : 3;
	unsigned w3 : 3;
	unsigned w4 : 3;
	unsigned w5 : 3;
	
      



};



}Dword;

typedef union machineWord{ /*machine word*/

 struct{
        unsigned E : 1;
        unsigned R : 1;
        unsigned A : 1;
	int w : 12;
        unsigned :0;
	unsigned address;
        union machineWord *next;



 };


 struct{

        unsigned w1 : 3;
	unsigned w2 : 3;
	unsigned w3 : 3;
	unsigned w4 : 3;
	unsigned w5 : 3;



 };

}word;

typedef union opMachineWord{ /*operatrtion machine word*/

 struct{
	
        unsigned int role : 3;

        unsigned dest_op0 :1;
        unsigned dest_op1 :1;
        unsigned dest_op2 :1;
        unsigned dest_op3 :1;

	unsigned sour_op0 :1;
        unsigned sour_op1 :1;
        unsigned sour_op2 :1;
        unsigned sour_op3 :1;

	unsigned op_code :4;
        
        unsigned :0;
        
	unsigned address;
	union machineWord *next;




 };

 struct{

        unsigned w1 : 3;
	unsigned w2 : 3;
	unsigned w3 : 3;
	unsigned w4 : 3;
	unsigned w5 : 3;



 }; 


}oWord;


/*analize function*/
void label(char *);
int isLabel(char *);
 int isLabel2(char *);

void numData(char *);
void strData(char *);
void op(char *);

int isOp(char *);
int isStop(char *);
void ext(char *);

/*analize2 function*/
void ent(char *);
void label2(char *);
void op2(char *li);


void error(char *);

/*util functions*/
char *find_comma(char *);
void printErrors();
void free_symList();
void free_entList();
void free_extList();
void print_labels(symbal *);
char *del_first_spaces(char *);
void freeError();
void free_table_data();
void free_table_op();
void print_table_data();
void clean_line(char *);
void clean_label_name(char *);
void fileName(char *);





