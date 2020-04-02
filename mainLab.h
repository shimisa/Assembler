
/*output functions*/
void create_ob_file();
void create_ent_file();
void create_ext_file();


/*two transition functions*/
void analize1(char *);

void analize2(char *);

/*fix the address in the symbal table*/
void fix_sym_add();

/*tables and lists*/
extern symbal *sym;
extern symbal *entHead;
extern symbal *extHead;

extern Dword *data_table[150];
extern oWord inst_table[150];


/*index*/
extern int errorC;

extern int D;
extern int I;

extern int IC;
extern int DC;


