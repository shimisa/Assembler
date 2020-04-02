

#define MAX_STRING 75
#define NUM_OF_OP 16

/*tables and lists*/
extern symbal *sym;
extern oWord inst_table[150];
extern Dword *data_table[150];

extern symbal *entHead;
extern symbal *extHead;

extern char line[MAX_LINE];

/*index*/
extern int IC;
extern int DC;

extern int I;
extern int D;

/*functions*/
char address_met(char *);


/*two transition functions*/
void analize1(char *);

void analize2(char *);

