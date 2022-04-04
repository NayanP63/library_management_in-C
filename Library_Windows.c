#include<stdio.h> // Only for WINDOWS Systems.
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<dirent.h>
#include<sys/stat.h>
#include<dos.h>
#include<windows.h>

// ------------------------------------- GLOBAL THINGS...
FILE *fb;
char str[2],dat[11],isn_global[6],sts[43];
int sem, derror = 1,st_num, msg = 0, bn = 0, add = 0,folder=0;

// ------------------------------------- FUNCTIONS
int book_update(int ,char[]); // Book Data Update Function
int b_unique(char[]); // Book's Uniqueness Searching
int datentry(int ); // As name specified its DataEntry
int get_token(); // Unique Token for each User
int inmgt(); // Inventory Management
int renamef(); // Renaming Function
int search(int ); // NO NEED to Say
int stud_update(int ,char[]); // Student Data Update
int s_unique(int ,char[]); // Student Uniqueness
int upgrade(); // Data Upgrading to next Sem
void add_stdata(); // Add new Student Details
void book_datentry(); 
void bdata_update(int );
void choice();
void data_name();
void delay(unsigned int);
void del_book();
void del_std();
void get_date();
void issueb();
void issn_update(char[],char[]);
void last_date();
void returnb();
void set_issnd();
void stdtls();
void str_works();
void rmv();
void rmv_ids(char []);
void rnm_st();

// -------------------------------------- STRUCTRE OF BOOK DATA
struct book {
	char name[64], issn[6];
	int issued;
	int in_stock;
}b;
// -------------------------------------- STRUCTURE FOR DIRECTORY ACCESSING
struct dirent *de;
// -------------------------------------- STURCTURE FOR GETTING THE ISSN ISSUE MAX DATES
struct dates {
	int i1,i2,i3;
}dt;
// -------------------------------------- STRUCTRE OF USERID AND PASSWORD
struct log {
	char usid[10], passwd[10];
}l;
// -------------------------------------- STRUCTURE OF LAST SUBMISSION DATES ENTERING
struct sisn {
	int ld1,ld2,ld3;
}ld;
// -------------------------------------- STRUCTRE OF STUDENT DATA
struct std {
	char name[20],date1[11],date2[11],date3[11], id[15], issn1[6], issn2[6], issn3[6];
	int issue_st1,issue_st2,issue_st3,token1,token2,token3;
}s;
// -------------------------------------- STRUCTRE OF UNIQUE TOKEN
struct token {
	char date[11];
	int t_number;
}t;
// -------------------------------------- STRUCTURE OF THE STUDENT ID UNIQUE FUNCTION
struct unique {
	char dept[3],sid[15],d1[11],d2[11],d3[11];
	int smt;
}u;
// -------------------------------------- MAIN FUNCTION WITH CUSTOM INCRYPTION FOR DATA
void sign_up() {
	int i;
	FILE *fp = fopen("C:/LibFiles/Login/login_data.nsp","wb");
	printf("\n\n>> ENTER THE NEW USERID : ");fflush(stdin);
	gets(l.usid);
	for(i = 0; l.usid[i] != '\0';i++) {//--------------------INCRYPTION STARTED
		if(isalpha(l.usid[i])) l.usid[i] += 7;
		else if(isdigit(l.usid[i])) l.usid[i] += 10;
	}
	printf("\n\n>> NOW, ENTER THE NEW PASSWORD : ");fflush(stdin);
	gets(l.passwd);
	for(i = 0; l.passwd[i] != '\0';i++) {
		if(isalpha(l.passwd[i])) l.passwd[i] += 7;
		else if(isdigit(l.passwd[i])) l.passwd[i] += 10;
	}
	fwrite(&l,sizeof(l),1,fp);
	msg = 1;
	fclose(fp);
	printf("\n\n\t\t\t\t ------------>> USER DATA SAVED SUCCESSFULLY <<--------------"
	        "\n\n  ---->>  DEAR USER , WE SUGGEST YOU TO WRITE DOWN THESE GIVEN CREDENTIALS IN SAFE PLACE OR MEMORIZE THESE :)  <<----"
	        "\n\n>> PRESS ANY KEY TO CONTINUE : ");
	getch();	
}

void main() {
	get_date();
    SetConsoleTitle("                                                                                                                 -: PGEC LIBRARY MANAGEMENT :-");
	system("color 0F");
	//system("mode 800");
	mkdir("C:/LibFiles");
	mkdir("C:/LibFiles/Login");
	mkdir("C:/LibFiles/stdData");
    mkdir("C:/LibFiles/bookData");
    mkdir("C:/LibFiles/gens");
    mkdir("C:/LibFiles/UniqData");
	mkdir("C:/ProgramData/wincore");
	FILE *fp;
	remove("C:/LibFiles/stdData/stemp.dat");
	remove("C:/LibFiles/stdData/stud.dat");
	b:;
	int flag = 1, i;
	char uid[10],pass[10];
	if((fp = fopen("C:/LibFiles/Login/login_data.nsp","rb"))== NULL) {
		FILE *n;
		if((n = fopen("C:/ProgramData/wincore/Login/login_data.nsp","rb")) != NULL) {
			system("color 04");
			printf( "\t\t\t\a! WARNING !\t\t\t! WARNING !\t\t\t! WARNING !"
			        "\n\n\n>> YOUR LAST SAVED DATA ARE CORRUPTED , DO YOU WANT TO START RECOVERY OF YOUR OLD DATA (y/n): ");
			if(getch() == 'y') {
				system("ROBOCOPY C:/ProgramData/wincore C:/LibFiles /S /COPYALL /COPY:D /NJS /NP /NS /NDL /NFL /NJH");
				fclose(fp);
				if((fp = fopen("C:/LibFiles/Login/login_data.nsp","rb")) != NULL) {
 					fseek(fp,0,2);
                	int size = ftell(fp);
                	if(size != 0){
                		system("cls");
                		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t UPDATING");
                	    int i;
                 	    for(i = 0; i < 5; i++) {
                     		delay(600);
                 	        printf(".");
                 	    }
				        system("cls");
				        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-: UPDATE SUCCESSFULL :-"
				                "\n\n>> PRESS ANY KEY TO GO TO NEW SIGN UP SECTION : ");
				        getch();
				        system("cls");
					}
				    else {
					    printf("\n\n\n\t\t\t DATA RECOVERY FAILED. PLEASE, RELOGIN WITH NEW USERID AND PASSWORD"
					            "\n\n>> PRESS ANY KEY TO GO TO NEW SIGN UP SECTION : ");
				        getch();
				        system("cls");
					    fp = fopen("C:/LibFiles/Login/login_data.nsp","wb");
					    flag = 0;
				    }
				}
			}
			else {
			    printf("\n\n\n\t\t\t  YOU OPTED NOT TO RETRIEVE THE SAVED DATA , NOW CREATE A NEW DATA SET"
				       "\n\n>> PRESS ANY KEY TO GO TO NEW SIGN UP SECTION : ");
				getch();
				system("cls");
				fp = fopen("C:/LibFiles/Login/login_data.nsp","wb");
			    flag = 0;
		    }
		}
		else flag = 0;
	}
	fseek(fp,0,2);
	int size = ftell(fp);
	if(size == 0) {
		flag = 0;
		fclose(fp);
	}
	else fseek(fp,0,0);
	if(flag == 0) {
		system("color 06");
		printf("\t\a-------------------- :-) WELLCOME 1ST TIME USER , ENTER THE CREDENTIALS CAREFULLY (-: ---------------------");
		sign_up();
		goto b;
	}
	else {
		if(msg == 1) {
			system("cls");
			printf("\n\n\t\t\t\t\t\a-: WELCOME 1st TIME USER :-"
                    "\n\n      This Software is designed for Library Management Purposes, Totally Done on C Programming language."
					"\nI hope you will find it usefull enough. Firstly it will run on the CMD Terminal of your Windows Machine, and"
					"\nit is designed to hold LARGE DATA SETS, easily. Please, don't tamper with the files created while using "
					"\n this Program, it will cause fatal ERRORS.  "
					"\n\n>>INSTRUCTIONS :-"
					"\n\n\t - USE USERID AND PASSWORD OF MAX 10 CHARACTERS ALPHANUMERIC"
					"\n\t - ENHANCED SECURITY FOR USERID AND PASSWORD PROTECTION"
					"\n\t - AUTOMATIC BACKUP ENABLED @@ SECURE MODE #winapi"
					"\n\t - COMPILED FOR 64bit MACHINES"
					"\n\t - USE ONLY 2 CHARACTERS FOR STREAM SELECTION - Like, Civil (ce), cs, ec, es, me"
					"\n\t - USE MAX 15 CHARACTERS FOR ID AND 5 CHARACTERS FOR BOOK ISSN NUMBER"
					"\n\n\n\t\t ----------------------  YOU ARE GOOD TO GO : )"
					"\n\n\n>> PRESS ANY KEY TO GO TO LOGIN MENU : ");
					getch();
					system("cls");
		}
		loop :;
		system("cls");
		system("color 9F");
		int mc,sc;//mc = main choice , sc = sub choice
		printf("\n\n\n\n\n\t   ======================================<<  LOGIN WINDOW  >>========================================"
	        "\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                         1 to LOG_IN                                            :"
			"\n\t   :                                                                                                :"
			"\n\t   :                               2 to IF YOU FORGOT USERID OR PASSWORD                            :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :                                                                                                :"
			"\n\t   :----------->> ENTER : ");
		scanf("%d",&mc);
		if(mc != 2 && mc != 1) {
			printf("\n\n\t\t\t  ------------>> INVALID ENTERY , PRESS ANY KEY TO ENTER AGAIN\n : ");
			getch();
			goto loop;
		}
		else if(mc == 2) {
			system("cls");
			printf("\n\t\t\t\t\t    ->> RESET USERID & PASSWORD <<-"
			       "\n\n\t\t\t\t\t     --> 1 to RESET BY USERID"
				   "\n\t\t\t\t\t     --> 2 to RESET BY PASSWORD"
				   "\n\t\t\t\t ---> ENTER : ");
			scanf("%d",&sc);
			if(sc == 1) {
				printf("\n\n>> ENTER THE LAST GIVEN USERID : ");
				fflush(stdin);gets(uid);
				for(i = 0; uid[i] != '\0';i++) {
         			if(isalpha(uid[i])) uid[i] += 7;
		        	else if(isdigit(uid[i])) uid[i] += 10;
			    }
				rewind(fp);
				fread(&l,sizeof(l),1,fp);
				if(!strcmp(l.usid,uid)) {
					fclose(fp);
					sign_up();
					goto loop;
				}
				else {
					printf("\n\n\t\t\t\t -------->> WRONG USERID ENTERED :( EXITING ");
					fclose(fp);
					exit(0);
			    }
			}
			else if(sc == 2) {
				printf("\n\n>> ENTER THE LAST GIVEN PASSWORD : ");
				fflush(stdin); gets(pass);
				for(i = 0; pass[i] != '\0';i++) {
			        if(isalpha(pass[i])) pass[i] += 7;
    		    	else if(isdigit(pass[i])) pass[i] += 10;
	        	}
				rewind(fp);
				fread(&l,sizeof(l),1,fp);
				if(!strcmp(l.passwd,pass)) {
					fclose(fp);
					sign_up();
				}
				else {
					printf("\n\n\t\t\t\t -------->> WORNG PASSWORD ENTERED :(  EXITING");
					fclose(fp);
					exit(0);
				}
			}
		}
		system("cls");
	    printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\a>> ENTER USERID : ");fflush(stdin);
	    gets(uid);
	/*	i = 0;
    	while(i < 10) {
		    uid[i] = getch();
		    if(uid[i] == 13) {
		    	uid[i] = '\0';
		    	break;
			}
			else if(uid[i] == 8) {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t>> ENTER USERID : ");
		        --i;
		        int k;
		        for(k = 0; k < i;k++) printf("*");
			}
		    else {
		    	i++;
		        printf("*");
			}
	    }*/
	    for(i = 0; uid[i] != '\0';i++) {
			if(isalpha(uid[i])) uid[i] += 7;
			else if(isdigit(uid[i])) uid[i] += 10;
		}
	    fread(&l,sizeof(l),1,fp);//----------------------------DECRYPTION PHASE
	    if(!strcmp(l.usid,uid)) {
		    system("cls");
	        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\a>> ENTER THE PASSWORD : ");fflush(stdin);
	        i = 0;
     		while(i < 10) {
		        pass[i] = getch();
	   	        if(pass[i] == 13) {
	               	pass[i] = '\0';
	            	break;
		        }
	        	else if(pass[i] == 8) {
	    	    	system("cls");
	                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t>> ENTER THE PASSWORD : ");
	    	    	--i;
	                int k;
	                for(k = 0; k < i;k++) printf("*");
    		    }
	            else {
	            	i++;
	                printf("*");
        		}
            }
	        for(i = 0; pass[i] != '\0';i++) {
			    if(isalpha(pass[i])) pass[i] += 7;
    			else if(isdigit(pass[i])) pass[i] += 10;
	    	}
			if(!strcmp(l.passwd,pass)) {
				system("cls");
				system("color F0");
		        printf("\t\a  ------------------------>.--->>.-->>>  WELLCOME ADMIN  <<<--.<<---.<-------------------------\n"
				        "\t                                 !                              !   \n"
						"\t                              {.} {.}                        {.} {.}\n"
						"\t                                {.}                            {.}\n"
						"\t                                 ^                              ^\n");
		        fclose(fp);
	    	    choice();
	    	}
	        else {
	    	    system("cls");
	        	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t! WARNING !\n\n\t\t\t\t  SORRY USER NOT VERIFIED , SESSION TERMINATED  :(");
	        	fclose(fp);
	        	exit(0);
	    	}
		}
		else {
	        system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t! WARNING !\n\n\t\t\t\t     -: SORRY USER ID NOT VERIFIED :-"
			        "\n\n\n>> DO YOU WANT TO TRY AGAIN (y/n): ");
			if(getch() == 'y') {
				system("cls");
	            fclose(fp);
	            goto loop;
			}
			else {
				system("cls");
	            fclose(fp);
	            system("taskkill/IM ConsolePauser.exe");
			}
		}
	}
	//choice();
}
// -------------------------------------- FUNCTION OF MAIN MENU 
void choice() {
	int mmsg = 0,i,c; fflush(stdin);fflush(stdout);
	FILE *f;
	if((f = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) mmsg = 1;
	else {
		fseek(f,0,2);
		if(ftell(f) == 0) mmsg = 1; 
	}
	fclose(f);
	printf("\n\t\a=====================================>> -: MAIN MENU :- <<======================================="
			"\n\n\t\t\t\t-> 1 to STUDENT RELATED WORKS\n\n\t\t\t\t"
			"-> 2 to BOOKS RELATED WORKS\n\n\t\t\t\t");
	if(mmsg == 0) {
		printf(	"-> 3 to SEE WHOSE LAST DATE OF BOOK SUBMISSION IS TODAY\n\n\t\t\t\t"
		    	"-> 4 to SET MAXIMUM DAYS FOR TAKING BOOKS\n\n\t\t\t\t"
		    	"-> 5 to CLONE PREVIOUS DATA (IF DATA IS MISSING OR CORRUPTED)\n\n\t\t\t\t"
	    		"-> 6 to UPGRADE STUDENTS TO NEXT SEMESTER\n\n\t\t\t\t");
	}
	printf( "-> 0 to EXIT\n\n"
	        "\t\t\t  ============================*_*============================"
	        "\n\t>> ENTER : ");
	scanf("%d",&c);
	if(mmsg == 1) {
		if(c == 1) str_works();
		else if(c == 2) inmgt();
		else if(c == 0) exit(0);
		else {
			printf("\n\n\t\t\t ---------------->> INVALID ENTRY , PRESS ANY KEY TO ENTER AGAIN :)");
			getch();
			system("cls");
			choice();
		}
	}
	if(c == 1) str_works();
	else if(c == 2) inmgt();
	else if(c == 3) last_date();
	else if(c == 4) set_issnd();
	else if(c == 5) {
		system("cls");
		system("ROBOCOPY C:/ProgramData/wincore C:/LibFiles /S /COPYALL /COPY:D /NJS /NP /NS /NDL /NFL /NJH");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t UPDATING");
	    int i;
	    for(i = 0; i < 5; i++) {
    		delay(500);
	        printf(".");
	    }
	    system("cls");
	    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ---: UPDATED :---"
		        "\n\n>> PRESS ANY KEY TO GO BACK : ");
		getch();
		system("cls");
	}
	else if(c == 6) {
		if(upgrade() == 1) {
			for(i = 3; i > 0; i--) {
				system("cls");printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t UPDATING...........WAIT FOR %d SECONDS  :)",i);delay(1000);
			}
			system("ROBOCOPY C:/LibFiles/stdData C:/ProgramData/wincore/stdData /MIR /S /COPYALL /COPY:D /NJS /NP /NJH /NS /NFL /NDL");
			system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t\t UPGRADE COMPLETE");
			printf("\n\n\n>> PRESS ANY KEY TO CONTINUE : ");getch();
			system("cls");
		}
		else {
			system("cls");
			printf("\n\n\n\t\t\t\t UPGRADE ERROR OCCURED :-------------------------------------");
			printf("\n\n\n>> PRESS ANY KEY TO CONTINUE : ");
			getch();
			system("cls");
		}
	}
	else if(c == 0) {
		system("ROBOCOPY C:/LibFiles C:/ProgramData/wincore /S /COPYALL /COPY:D /NJS /NP /NJH /NS /NFL /NDL");
		system("taskkill/IM ConsolePauser.exe");
	}
	else {
		printf("\n\n\t\t\t ---------------->> INVALID ENTRY , PRESS ANY KEY TO ENTER AGAIN :) ");
		getch();
		system("cls");choice();
	}
	choice();
}

//---------------------------------------------------- GENERALS -----------------------------------------------------------------

// -------------------------------------- DELAY FUNCTION
void delay(unsigned int msecs){
	clock_t goal = msecs + clock();
	while(goal > clock());
}
// -------------------------------------- FUNCTION TO UPDATE ISSN IN ALL DATA SETS
void issn_update(char issno[],char issnn[]) {
	int i = 0;
	DIR *d = opendir("C:/LibFiles/stdData/");
	remove("C:/LibFiles/stdData/stemp.dat");
	remove("C:LibFiles/stdData/stud.dat");
	rewinddir(d);
	for(i = 0; (de = readdir(d)) != NULL;i++) {
		if(i > 1 ) {
			char stro[42] = "C:/LibFiles/stdData/";
	    	strcat(stro,de->d_name);
			FILE *t1, *t2;
			t1 = fopen(stro,"rb");
			t2 = fopen("C:/LibFiles/stdData/x.dat","wb");
			while(1) {
				fread(&s,sizeof(s),1,t1);
				if(feof(t1)) break;
				else if(!strcmp(s.issn1,issno)) strcpy(s.issn1,issnn);
				else if(!strcmp(s.issn2,issno)) strcpy(s.issn2,issnn);
				else if(!strcmp(s.issn3,issno)) strcpy(s.issn1,issnn);
				fwrite(&s,sizeof(s),1,t2);
			}
			fclose(t1); fclose(t2);
			char strn[] = "C:/LibFiles/stdData/x.dat";
			remove(stro);
			rename(strn,stro);
		}
	}
	return;
}
// -------------------------------------- FUNCTION TO SET ISSN ISSUE MAX DAYS
void set_issnd() {
	system("cls");
	printf("\t\t=============================================================================\n"
	        "\t\t\t\t\t\t  SETING DAYS\n"
			"\t\t\t\t\t=====================================\n");
	FILE *f;
	int flag = 0;
	if((f = fopen("C:/LibFiles/gens/issn_days.mj","r")) == NULL) {
		f = fopen("C:/LibFiles/gens/issn_days.mj","w");
		flag = 1;
	}
	if(flag == 1) {
	    loop :;
		printf("\n\n>> HOW MANY DAYS TO RETURN 1st BOOK : ");
		scanf("%d",&ld.ld1);
		printf("\n\n>> HOW MANY DAYS TO RETURN 2nd BOOK : ");
		scanf("%d",&ld.ld2);
		printf("\n\n>> HOW MANY DAYS TO RETURN 3rd BOOK : ");
		scanf("%d",&ld.ld3);
		fwrite(&ld,sizeof(ld),1,f);
		fclose(f);
	}
	else {
		fread(&ld,sizeof(ld),1,f);
		printf("\n>> YOUR CURRENT LAST DATE SETUP IS :-"
		        "\n\t\t\t\t BOOK_1 : %d Days"
				"\n\t\t\t\t BOOK_2 : %d Days"
				"\n\t\t\t\t BOOK_3 : %d Days",ld.ld1,ld.ld2,ld.ld3);
		printf("\n\n>> DO YOU WANT TO CHANGE OLD DAYS COUNTS (y/n): ");
	    if(getch() == 'y') {
		    f = fopen("C:/LibFiles/gens/issn_days.mj","w");
		    goto loop;
	    }
	}
	printf("\n\n>> PRESS ANY KEY TO CONTINUE : ");
	getch();
	system("cls");
}
// -------------------------------------- FUNCTION TO UPGRADE ALL DATA SETS TO NEXT SEMESTER
int upgrade() {
	int i = 0;
	DIR *d = opendir("C:/LibFiles/stdData/");
	remove("C:/LibFiles/stdData/stemp.dat");
	remove("C:LibFiles/stdData/stud.dat");
	while((de = readdir(d)) != NULL) i++;
	for(;i > 1;i--) {
		if(i == 2) return 1;
		rewinddir(d);
    	seekdir(d,i-1);
    	de = readdir(d);
    	char rn[13],stro[42] = "C:/LibFiles/stdData/";
    	strcpy(rn,de->d_name);
	    if(rn[8] != '8') {
		    rn[8] += 1;
	    	strcat(stro,de->d_name);
	    	char strd[42] = "C:/LibFiles/stdData/";
	        strcat(strd,rn);
	        rename(stro,strd);
    	}
		else {
	    	strcat(stro,rn);
	    	rmv_ids(stro);
            rnm_st();
	    	remove(stro);
    	}
	    fflush(stdin);fflush(stdout);
	}
}
// -------------------------------------------------------------- REMOVING ALL IDs FROM stro FILE
void rmv_ids(char nm[]) {
	FILE *f = fopen(nm,"rb");
	while(1) {
		fflush(stdin);fflush(stdout);
		fread(&s,sizeof(s),1,f);
		if(feof(f)) break;
		else if(s.issue_st1 == 1 || s.issue_st2 == 1 || s.issue_st3 == 1) {
			printf("\n\n\t\t\t -: ALERT ! id %s HAS NOT RETURNED BOOK/BOOKS :-"
			        "\n\n>> WISH TO TAKE BOOKS (y/n): ",s.id);
			if(getch() == 'y') {
				if(s.issue_st1 == 1) {
					if(book_update(1,s.issn1)) printf("\n\n\t\t\t\t\t -: BOOK 1 TAKEN SUCCESSFULLY :-");
					else printf("\n\n\t\t\t\t\t -: ERROR, BOOK 1 NOT TAKEN :-");
				}
				if(s.issue_st2 == 1) {
					if(book_update(1,s.issn2)) printf("\n\n\t\t\t\t\t -: BOOK 2 TAKEN SUCCESSFULLY :-");
					else printf("\n\n\t\t\t\t\t -: ERROR, BOOK 2 NOT TAKEN :-");
				}
				if(s.issue_st3 == 1) {
					if(book_update(1,s.issn3)) printf("\n\n\t\t\t\t\t -: BOOK 3 TAKEN SUCCESSFULLY :-");
					else printf("\n\n\t\t\t\t\t -: ERROR, BOOK 3 NOT TAKEN :-");
				}
				FILE *n,*m;
		        if((n = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) 
				    printf("\n\n\t\t\t\t --------->> ERROR, SUPPORTING DATA NOT FOUND");
        		else {
        			m = fopen("C:/LibFiles/UniqData/st_temp.dat","wb");
		           	rewind(n);
        	    	while(1) {
	       	        	fread(&u,sizeof(u),1,n);
		            	if(feof(n)) break;
		            	else if(!strcmp(s.id,u.sid));
		      	    	else fwrite(&u,sizeof(u),1,m);
	   	        	}
		        	fclose(n);
					fclose(m);
				}
			}
	    	else printf("\n\n\t\t\t\t\t -: YOU OPTED NOT TO TAKE THE BOOKS :-");
		}
	}
	fclose(f);
}
// -------------------------------------------------------------- TO SEE WHO IS TAKING BOOK MORE THAN THEIR
void last_date() {
	system("cls");
	FILE *t,*f;
	int flag = 0;
	if((f = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) {
		printf("\n\n\n\t\t------------>> DATA CORRUPTION FOUND, PLEASE GOTO MAIN MENU AND TRY TO BACKUP OLD DATA"
		       "\n\n PRESS ANY KEY TO CONTINUE : ");
		getch();
		return;
	}
	if((t = fopen("C:/LibFiles/gens/issn_days.mj","r")) == NULL) {
		printf("\n\n\n\t\t-------->> DATA CORRUPTION FOUND, PLEASE ENTER THESE DETAILS FIRST :)");
		set_issnd();
		t = fopen("C:/LibFiles/gens/issn_days.mj","r");
	}
	rewind(t);
	fread(&ld,sizeof(ld),1,t);
	printf( "\n\t======================================================================================================="
	        "\n\t\t\t\t\t\t-: TODAY EXPIRING :-"
			"\n\t\t\t======================================================================"
			"\n\n\t\t                              BOOK TAKEN"
			"\n\t\t     -: ID :-    -: DEPT :-  -: ON SEM :-    -: BOOK1 :- -: BOOK2 :- -: BOOK3 :-"
			"\n\t\t   -------------------------------------------------------------------------------");
	while(1) {
    	int x = 0,y = 0;
    	fflush(stdin);fflush(stdout);
		fread(&u,sizeof(u),1,f);
		if(feof(f)) {
			if (flag == 0) printf("\n\n\t\t\t\t\t   << SITBACK EVERYTHING IS FINE >>");
	        printf( "\n\n\t\t   --    -----      ------       --< END OF FILE >--       -------     -----    --");
			break;
		}
    	else {
			if(u.d1[0] != '-') {
				if(get_days(u.d1) >= ld.ld1) {
					flag = 1;
					printf("\n\n\t\t    %s      %s\t\t   %d\t\t YES\t     ",u.sid,u.dept,u.smt);
					x = 1;
				}
    		}
			if(u.d2[0] != '-') {
				if(get_days(u.d2) >= ld.ld2) {
					flag = 1;
					if(x == 1) {
						printf("YES\t ");
						y = 1;
					}
					else {
						printf("\n\n\t\t    %s      %s\t\t   %d\t\t\t     YES\t ",u.sid,u.dept,u.smt);
						y = 1;
					}
				}
			}
	    	if(u.d3[0] != '-') {
	    		if(get_days(u.d3) >= ld.ld3) {
	    			flag = 1;
					if(y == 0 && x == 1) printf("   \t  YES");
	    			else if(y == 1) printf("YES");
	    			else printf( "\n\n\t\t    %s      %s\t\t   %d     \t\t\t\t YES",u.sid,u.dept,u.smt);
				}
			}
   	    }
	}
	fclose(f);
	fclose(t);
	printf("\n\n>> PRESS ANY KEY TO GO BACK : ");
	getch();
	system("cls");
}
// -------------------------------------- FUNCTION TO GET THE UNIQUE TOKEN
int get_token() {
	FILE *f;
	if((f = fopen("C:/LibFiles/gens/token.dat","rb")) == NULL) {
		f = fopen("C:/LibFiles/gens/token.dat","wb");
		strcpy(t.date,dat);
		t.t_number = 1;
		fwrite(&t,sizeof(t),1,f);
		fclose(f);
	}
	else {
		fread(&t,sizeof(t),1,f);
		if(!strcmp(t.date,dat)) ++t.t_number;
		else {
			strcpy(t.date,dat);
			t.t_number = 1;
		}
		fclose(f);
		fopen("C:/LibFiles/gens/token.dat","wb");
		fwrite(&t,sizeof(t),1,f);
		fclose(f);
	}
	return t.t_number;
}
// -------------------------------------- REMOVING stemp.dat
void rmv() {
	remove("C:/LibFiles/stdData/stemp.dat");
}
// -------------------------------------- FUNCTION TO RENAME THE FILE TO APPROPRIATE ONE
int renamef(int i) {
	data_name();
	if(i == 1) {
	    remove(sts);
	    rename("C:/LibFiles/stdData/stud.dat",sts);
	}
	else if(i == 2) {
	    remove(sts);
		rename("C:/LibFiles/stdData/stemp.dat",sts);
		return 1;
	}
}
// -------------------------------------- FUNCTION TO RENAME st_temp
void rnm_st() {
	remove("C:/LibFiles/UniqData/st_data.dat");
	rename("C:/LibFiles/UniqData/st_temp.dat","C:/LibFiles/UniqData/st_data.dat");
}
// -------------------------------------- FUNCTION FOR RENAME book_temp
void rnm_bk() {
    remove("C:/LibFiles/bookData/book_inv.dat");
    rename("C:/LibFiles/bookData/btmp.dat","C:/LibFiles/bookData/book_inv.dat");
}
// -------------------------------------- FUNCTION TO GET THE TODAYS DATE
void get_date() {
	time_t timec;
    time(&timec);
    struct tm *mtime = localtime(&timec);
    FILE *f = fopen("C:/LibFiles/gens/date.txt","w");
    if(mtime->tm_mday < 10) {
    	if((mtime->tm_mon + 1) < 10) fprintf(f,"0%i/0%i/%i",mtime->tm_mday,mtime->tm_mon+1,mtime->tm_year+1900);
    	else fprintf(f,"0%i/%i/%i",mtime->tm_mday,mtime->tm_mon+1,mtime->tm_year+1900);
	}
	else {
		if((mtime->tm_mon + 1) < 10) fprintf(f,"%i/0%i/%i",mtime->tm_mday,mtime->tm_mon+1,mtime->tm_year+1900);
		else fprintf(f,"%i/%i/%i",mtime->tm_mday,mtime->tm_mon+1,mtime->tm_year+1900);
	}
    fclose(f);
    f = fopen("C:/LibFiles/gens/date.txt","r");
	fgets(dat,11,f);
    fclose(f);
}
// -------------------------------------- FUNCTION TO GET DAYS OF HAVING THE BOOK
int get_days(char sdate[]) {
	get_date();
	char a[11],b[11];
	strcpy(b,dat);
	strcpy(a,sdate);
	int x = b[1] - a[1] + 10*(b[0] - a[0]) + 30*(10*(b[3] - a[3]) + b[4] - a[4]);
	x += 365*(1000*(b[6] - a[6]) + 100*(b[7] - a[7]) + 10*(b[8] - a[8]) + b[9] - a[9]);
    return x;
}
// -------------------------------------- SEARCHING ID IS UNIQUE OR NOT
int s_unique(int x,char id[]) {
	FILE *f;
	int fl = 0;
	if((f = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) {
		f = fopen("C:/LibFiles/UniqData/st_data.dat","wb");
		fclose(f);
		f = fopen("C:/LibFiles/UniqData/st_data.dat","rb");
	}
	rewind(f);
	while(1) {
		fread(&u,sizeof(u),1,f);
		if(feof(f)) break;
		else if(!strcmp(u.sid,id)) {
			fclose(f);
			return 1;
		}
	}
	fclose(f);
	return 0;
}
// -------------------------------------- SEARCHING ISSN IS UNIQUE OR NOT
int b_unique(char in[]) {
	fclose(fb);
	FILE *f = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
	fseek(f,0,0);
	while(1) {
		fread(&b,sizeof(b),1,f);
		if(feof(f)) break;
		else if(!strcmp(b.issn,in)) {
			fclose(f);
			fb = fopen("C:/LibFiles/bookData/book_inv.dat","ab");
			return 1;
		}
	}
	fclose(f);
	fb = fopen("C:/LibFiles/bookData/book_inv.dat","ab");
	return 0;
}
// -------------------------------------- FUNCTION TO KNOW THE CURRENT WORKING DATA
void data_name() {
    FILE *f;
    f = fopen("C:/LibFiles/gens/err.txt","w");
    fprintf(f,"C:/LibFiles/stdData/data_%s_%d.dat",str,sem);
    fclose(f);
    f = fopen("C:/LibFiles/gens/err.txt","r");
    fflush(stdout);
    fgets(sts,40,f);
	fclose(f);
	up3:;
    int x = remove("C:/LibFiles/gens/err.txt");
    if(x != 0) goto up3;
}

//-------------------------------------------------   STUDENT RELATED FUNCTIONS -------------------------------------------------

// ----------------------------------------------------- STUDENT RELATED MOST USED FUNCTIONS
// --------------------------------------- SEARCHING
int search(int x) {
	FILE *fp;
	char str1[] = "ce";char str2[] = "cs";char str3[] = "ec";char str4[] = "ee";char str5[] = "me";
	loop:;
	printf("\n\n>> ENTER THE STREAM : ");fflush(stdin);
	gets(str);
	if(!strcmp(str,str1)) {
		loop1:;
		printf("\n>> ENTER THE SEMESTER : ");fflush(stdin);
	    scanf("%d",&sem);
	    switch(sem) {
		case 1 : if((fp = fopen("C:/LibFiles/stdData/data_ce_1.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_1.dat","wb");break;
		case 2 : if((fp = fopen("C:/LibFiles/stdData/data_ce_2.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_2.dat","wb");break;
		case 3 : if((fp = fopen("C:/LibFiles/stdData/data_ce_3.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_3.dat","wb");break;
		case 4 : if((fp = fopen("C:/LibFiles/stdData/data_ce_4.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_4.dat","wb");break;
		case 5 : if((fp = fopen("C:/LibFiles/stdData/data_ce_5.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_5.dat","wb");break;
		case 6 : if((fp = fopen("C:/LibFiles/stdData/data_ce_6.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_6.dat","wb");break;
		case 7 : if((fp = fopen("C:/LibFiles/stdData/data_ce_7.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_7.dat","wb");break;
		case 8 : if((fp = fopen("C:/LibFiles/stdData/data_ce_8.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ce_8.dat","wb");break;
		default:printf("\n\n\t    -----------------< INVALID ENTRY , PLEASE TRY AGAIN >------------------\n");
		        goto loop1;
				break;
    	}
    }
	else if(!strcmp(str,str2)) {
		loop2:;
		printf("\n>> ENTER THE SEMESTER : ");fflush(stdin);
	    scanf("%d",&sem);
	    switch(sem) {
		case 1 : if((fp = fopen("C:/LibFiles/stdData/data_cs_1.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_1.dat","wb");break;
		case 2 : if((fp = fopen("C:/LibFiles/stdData/data_cs_2.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_2.dat","wb");break;
		case 3 : if((fp = fopen("C:/LibFiles/stdData/data_cs_3.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_3.dat","wb");break;
		case 4 : if((fp = fopen("C:/LibFiles/stdData/data_cs_4.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_4.dat","wb");break;
		case 5 : if((fp = fopen("C:/LibFiles/stdData/data_cs_5.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_5.dat","wb");break;
		case 6 : if((fp = fopen("C:/LibFiles/stdData/data_cs_6.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_6.dat","wb");break;
		case 7 : if((fp = fopen("C:/LibFiles/stdData/data_cs_7.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_7.dat","wb");break;
		case 8 : if((fp = fopen("C:/LibFiles/stdData/data_cs_8.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_cs_8.dat","wb");break;
		default:printf("\n\t    -----------------< INVALID ENTRY , PLEASE TRY AGAIN >------------------\n");
		        goto loop2;
		        break;
	     }
    }
	else if(!strcmp(str,str3)) {
		loop3:;
		printf("\n>> ENTER THE SEMESTER : ");
	    scanf("%d",&sem);
	    switch(sem) {
		case 1 : if((fp = fopen("C:/LibFiles/stdData/data_ec_1.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_1.dat","wb");break;
		case 2 : if((fp = fopen("C:/LibFiles/stdData/data_ec_2.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_2.dat","wb");break;
		case 3 : if((fp = fopen("C:/LibFiles/stdData/data_ec_3.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_3.dat","wb");break;
		case 4 : if((fp = fopen("C:/LibFiles/stdData/data_ec_4.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_4.dat","wb");break;
		case 5 : if((fp = fopen("C:/LibFiles/stdData/data_ec_5.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_5.dat","wb");break;
		case 6 : if((fp = fopen("C:/LibFiles/stdData/data_ec_6.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_6.dat","wb");break;
		case 7 : if((fp = fopen("C:/LibFiles/stdData/data_ec_7.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_7.dat","wb");break;
		case 8 : if((fp = fopen("C:/LibFiles/stdData/data_ec_8.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ec_8.dat","wb");break;
		default:printf("\n\t    -----------------< INVALID ENTRY , PLEASE TRY AGAIN >------------------\n");
		        goto loop3;
		        break;
    	}
    }
    else if(!strcmp(str,str4)) {
    	loop4:;
		printf("\n>> ENTER THE SEMESTER : ");fflush(stdin);
	    scanf("%d",&sem);
	    switch(sem) {
		case 1 : if((fp = fopen("C:/LibFiles/stdData/data_ee_1.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_1.dat","wb");break;
		case 2 : if((fp = fopen("C:/LibFiles/stdData/data_ee_2.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_2.dat","wb");break;
		case 3 : if((fp = fopen("C:/LibFiles/stdData/data_ee_3.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_3.dat","wb");break;
		case 4 : if((fp = fopen("C:/LibFiles/stdData/data_ee_4.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_4.dat","wb");break;
		case 5 : if((fp = fopen("C:/LibFiles/stdData/data_ee_5.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_5.dat","wb");break;
		case 6 : if((fp = fopen("C:/LibFiles/stdData/data_ee_6.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_6.dat","wb");break;
		case 7 : if((fp = fopen("C:/LibFiles/stdData/data_ee_7.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_7.dat","wb");break;
		case 8 : if((fp = fopen("C:/LibFiles/stdData/data_ee_8.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_ee_8.dat","wb");break;
        default:printf("\n\t    -----------------< INVALID ENTRY , PLEASE TRY AGAIN >------------------\n");
		        goto loop4;
		        break;
	    }
    }
    else if(!strcmp(str,str5)) {
    	loop5:;
    	printf("\n>> ENTER THE SEMESTER : ");fflush(stdin);
	    scanf("%d",&sem);
	    switch(sem) {
		case 1 : if((fp = fopen("C:/LibFiles/stdData/data_me_1.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_1.dat","wb");break;
		case 2 : if((fp = fopen("C:/LibFiles/stdData/data_me_2.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_2.dat","wb");break;
		case 3 : if((fp = fopen("C:/LibFiles/stdData/data_me_3.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_3.dat","wb");break;
		case 4 : if((fp = fopen("C:/LibFiles/stdData/data_me_4.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_4.dat","wb");break;
		case 5 : if((fp = fopen("C:/LibFiles/stdData/data_me_5.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_5.dat","wb");break;
		case 6 : if((fp = fopen("C:/LibFiles/stdData/data_me_6.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_6.dat","wb");break;
		case 7 : if((fp = fopen("C:/LibFiles/stdData/data_me_7.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_7.dat","wb");break;
		case 8 : if((fp = fopen("C:/LibFiles/stdData/data_me_8.dat","rb"))== NULL) fp = fopen("C:/LibFiles/stdData/data_me_8.dat","wb");break;
		default:printf("\n\t    -----------------< INVALID ENTRY , PLEASE TRY AGAIN >------------------\n");
		        goto loop5;
		        break;
    	}
    }
    else {
    	printf("\n\t    -------------------< INVALID ENTRY , PLEASE TRY AGAIN >----------------------");
    	goto loop;
	}
	fseek(fp,0,2);
	int size = ftell(fp);
	st_num = size/sizeof(s);
	if(size == 0) {//----------------FILE CREATED BUT NO DATA OR NEWLY CREATED FILE 
		printf("\n\t\t\t\t     - : NO STUDENT DATA IS IN THE FILE : - ");
		printf("\n\n>> DO YOU WANT TO ADD STUDENT DATA NOW (y/n): ");
		if(getch() == 'y') {
			fclose(fp);
			add = 1;
    		st_num = datentry(0);
		}
		else {
			printf("\n\n\n\n\t\t\t ------------>> YOU OPTED NOT TO ADD STUDENT DATA ");
			sleep(1);
			fclose(fp);
			return 0;
		}
	}
	if(x != 1) {
		if(size == 0) fp = fopen(sts,"rb");
		fflush(fp);	fseek(fp,0,0);
	    FILE *f = fopen("C:/LibFiles/stdData/stemp.dat","wb");
	    while(1) {
            fread(&s,sizeof(s),1,fp);
            if(feof(fp)) break;
            else fwrite(&s,sizeof(s),1,f);
        }
        fclose(f);
        fclose(fp);
        return 1;
	}
	fclose(fp);
	return 1;
}
// --------------------------------------- STUDENT DATA ENTRY 
int datentry(int x) {
	system("cls");
	int n,i;
	char space[] = "--/--/----"; char isn[] = " --- "; char idn[15];
	FILE *fp, *d;
	if(x == 0) {
	    fp = fopen("C:/LibFiles/stdData/stemp.dat","wb");
	    fseek(fp,0,0);
	    printf("\n\t\t\a---------------------------------------------------------------------------"
	        "\n\t\t\t\t        SAVING DATA OF DEPT -%s- SEMESTER %d"
			"\n\t\t\t----------------------        *       ----------------------\n",str,sem);
	}
	else {
		data_name();
		fp = fopen(sts,"ab");
		system("cls");
		printf("\n\t\t\a---------------------------------------------------------------------------"
	            "\n\t\t\t\t        ADDING DATA TO DEPT -%s- SEMESTER %d"
			    "\n\t\t\t----------------------        *        ----------------------\n",str,sem);
	}
	nn:;
	printf("\n>> HOW MANY STUDENT DATA TO ENTER : ");
	fflush(stdin);scanf("%d",&n);
	if(n == 0) {
		printf("\n\n\t\t\t\t\t ----------->> NOT A VALID INPUT :("
		        "\n\n>> WISH TO GIVE AGAIN (y/n):");
		    if(getch() == 'y') goto nn;
		    else {
		    	fclose(fp);
		    	rmv();
		    	str_works();
			}
	}
	int re = n;
	while(n) {
		loop:;
		printf("\n\n>> ENTER THE ID NUMBER : ");
	    fflush(stdin);gets(idn);
	    if(idn[0] == '\0') {
	    	printf("\n\n\t ------------------------------->> ERROR, NO DATA INPUT GIVEN , GIVE AGAIN");
	    	goto loop;
		}
		else if(idn[0] == '0') {
	    	printf("\n\n\t ------------------------------->> ERROR, 0 is NOT VALID INPUT , GIVE AGAIN");
	    	goto loop;
		}
	    for(i = 0; idn[i] != '\0'; i++) {
	    	if(!isdigit(idn[i])) {
	    	    printf("\n\n\t -------------------------------->> ERROR, ENTER NUMBER ONLY : )");
	    	    goto loop;
		    }
		}
	    int y = s_unique(x,idn);
	    if(y == 1) {
	    	printf("\n\n\t\t\t\t     *** ID ALREADY EXIST , GIVE ANOTHER ***");
			goto loop;
		}
		loopn:;
	    printf("\n\n>> ENTER THE STUDENT NAME : ");
	    fflush(stdin);gets(s.name);
	    if(s.name[0] == '\0') {
	    	printf("\n\n\t ------------------------------->> ERROR, NO DATA INPUT GIVEN , GIVE AGAIN");
	    	goto loopn;
		}
	    
		if((d = fopen("C:/LibFiles/UniqData/st_data.dat","ab")) == NULL) d = fopen("C:/LibFiles/UniqData/st_data.dat","wb");
		fflush(stdin);strcpy(u.sid,idn);strcpy(u.dept,str);u.smt = sem;
		fflush(stdin);strcpy(u.d2,"-");strcpy(u.d3,"-");strcpy(u.d1,"-");
		fwrite(&u,sizeof(u),1,d);
		fclose(d);
		
		fflush(stdin);s.issue_st1 = 0; s.issue_st2 = 0; s.issue_st3 = 0;
		fflush(stdin);strcpy(s.issn1,isn); strcpy(s.issn2,isn); strcpy(s.issn3,isn);
	    fflush(stdin);s.token1 = 0;s.token2 = 0;s.token3 = 0;
		fflush(stdin);strcpy(s.date1,space);strcpy(s.date2,space);strcpy(s.date3,space);
		fflush(stdin);strcpy(s.id,idn);
	    
		fwrite(&s,sizeof(s),1,fp);
		n--;
	}
	fclose(fp);
	if(x == 0) {
		if(renamef(2)) printf("\n\n\t\t\t\t\t-: ALL DATA ENTERED SUCCESSFULLY :- ");
		else  printf("\n\n\t\t\t\t     -: DATA ENTERY UNSUCCESSFUL :- ");
	}
	printf("\n\n>> PRESS ANY KEY TO CONTINUE : ");
	getch();
	return re;
}
// --------------------------------------- STUDENT DATA UPDATE WHILE ISSUING OR RETURNING
int stud_update(int x,char d[]) {
	char dat[11] = "25/12/2018";
	FILE *fs = fopen("C:/LibFiles/stdData/stud.dat","wb");
	FILE *fp = fopen("C:/LibFiles/stdData/stemp.dat","rb");
	FILE *t1 = fopen("C:/LibFiles/UniqData/st_data.dat","rb");
	FILE *t2 = fopen("C:/LibFiles/UniqData/st_temp.dat","wb");
	strcpy(u.dept,str);
	u.smt = sem;
	char space[] = "--/--/----";
	char isn[] = " --- ";
	int f = 0, i = 0;
	fflush(fp);fseek(fp,0,0);
	fflush(fs);fseek(fs,0,0);//     mistake in issue
	for(i = 0; i < st_num; i++){
		fflush(stdin);fflush(stdout);
		fread(&s,sizeof(s),1,fp);
		if(!strcmp(s.id,d)) {
	        f = 1;
			// ------------------------------------------- ISSUE ZONE
			if(x == 1) {
				if(bn == 1) {
			    	if(!strcmp(s.issn1,isn)) {
			    		s.issue_st1 = 1;fflush(stdin);
			    	    strcpy(s.issn1,isn_global);
		    		    s.token1 = get_token();fflush(stdin);
	    			    strcpy(s.date1,dat);
	    			    rewind(t1);
						rewind(t2);
						while(1) {
		    	            fread(&u,sizeof(u),1,t1);
		                	if(feof(t1)) break;
            	    		else if(!strcmp(d, u.sid)) {
	    	            		strcpy(u.d1,dat);
	        	            	fwrite(&u,sizeof(u),1,t2);
	                		}
		                	else fwrite(&u,sizeof(u),1,t2);
	                	}
				    }
				}
				else if (bn == 2) {
					if (!strcmp(s.issn2,isn)) {
				    	s.issue_st2 = 1;fflush(stdin);
				    	strcpy(s.issn2,isn_global);
				        s.token2 = get_token();fflush(stdin);
				        strcpy(s.date2,dat);
				        rewind(t1);
						rewind(t2);
						while(1) {
		    	            fread(&u,sizeof(u),1,t1);
		                	if(feof(t1)) break;
            	    		else if(!strcmp(d, u.sid)) {
	    	            		strcpy(u.d2,dat);
	        	            	fwrite(&u,sizeof(u),1,t2);
	                		}
		                	else fwrite(&u,sizeof(u),1,t2);
	                	}
			    	}
				}
				else {
					if(!strcmp(s.issn3,isn)) {
			    		s.issue_st3 = 1;fflush(stdin);
			    	    strcpy(s.issn3,isn_global);
			    	    s.token3 = get_token();fflush(stdin);
			    	    strcpy(s.date3,dat);
			    	    rewind(t1);
						rewind(t2);
						while(1) {
		    	            fread(&u,sizeof(u),1,t1);
		                	if(feof(t1)) break;
            	    		else if(!strcmp(d, u.sid)) {
	    	            		strcpy(u.d3,dat);
	        	            	fwrite(&u,sizeof(u),1,t2);
	                		}
		                	else fwrite(&u,sizeof(u),1,t2);
	                	}
     				}
				}
			}
			// --------------------------------------------- RETURN SPACE
			else {
				if(!strcmp(isn_global,s.issn1)) {
					s.issue_st1 = 0;fflush(stdin);
				    strcpy(s.issn1,isn);
				    s.token1 = 0;fflush(stdin);
				    strcpy(s.date1,space);
				    while(1) {
	            		fread(&u,sizeof(u),1,t1);
        	    		if(feof(t1)) break;
	    	        	else if(!strcmp(d, u.sid)) {
         	    			strcpy(u.d1,"-");
	            	    	fwrite(&u,sizeof(u),1,t2);
	            		}
	            		else fwrite(&u,sizeof(u),1,t2);	
           	    	}
				}
				else if(!strcmp(isn_global,s.issn2)) {
					s.issue_st2 = 0;fflush(stdin);
				    strcpy(s.issn2,isn);
				    s.token2 = 0;fflush(stdin);
				    strcpy(s.date2,space);
				    while(1) {
	            		fread(&u,sizeof(u),1,t1);
        	    		if(feof(t1)) break;
	    	        	else if(!strcmp(d, u.sid)) {
         	    			strcpy(u.d2,"-");
	            	    	fwrite(&u,sizeof(u),1,t2);
	            		}
	            		else fwrite(&u,sizeof(u),1,t2);	
           	    	}
				}
				else {
					s.issue_st3 = 0;fflush(stdin);
				    strcpy(s.issn3,isn);
				    s.token3 = 0;fflush(stdin);
				    strcpy(s.date3,space);
				    while(1) {
	            		fread(&u,sizeof(u),1,t1);
        	    		if(feof(t1)) break;
	    	        	else if(!strcmp(d, u.sid)) {
         	    			strcpy(u.d3,"-");
	            	    	fwrite(&u,sizeof(u),1,t2);
	            		}
	            		else fwrite(&u,sizeof(u),1,t2);	
           	    	}
				}
			}
			fwrite(&s,sizeof(s),1,fs);
        }
        else fwrite(&s,sizeof(s),1,fs);
    }
	if(f == 1) {
		fclose(fp);fclose(fs);
		renamef(1);
		fclose(t1);fclose(t2);
		rnm_st();
	    return 1;
	}
	else {
		fclose(fp);
	    fclose(fs);
		return 0;
	}
}
// --------------------------------------------------- STUDENT RELATED MENU STARTING
void str_works() {
	int c, smsg = 0;
	FILE *f;
	if((f = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) smsg = 1;
	else {
		fseek(f,0,2);
		if(ftell(f) == 0) smsg = 1;
	}
	fclose(f);
	system("ROBOCOPY C:/LibFiles C:/ProgramData/wincore /MIR /S /COPYALL /COPY:D /NJS /NP /NJH /NS /NFL /NDL");
	system("cls");
	rmv();
	printf("\t\a=================================>> -: STUDENT RELETED WORKS :- <<===================================\n");
	if(smsg == 0) printf(   "\n\t\t\t\t\t    -> 1 to ISSUE BOOK"
    			            "\n\t\t\t\t\t    -> 2 to BOOK RETURN"
            	    		"\n\t\t\t\t\t    -> 3 to CHECK STUDENT DETAILS"
            	    		"\n\t\t\t\t\t    -> 4 to ADD STUDENT DETAILS"
							"\n\t\t\t\t\t    -> 5 to DELETE A STUDENT DETAILS");
	if(smsg == 1) printf("\n\t\t\t\t\t    -> 1 to ADD STUDENT DETAILS");
	printf( "\n\t\t\t\t\t    -> 0 to RETURN TO MAIN MENU\n\n"
	            "\t\t\t  ============================*_*============================"
	            "\n\t>> ENTER : ");
	        scanf("%d",&c);
	if(smsg == 1) {
		if(c == 1) add_stdata();
		else if(c == 0) {
			system("cls");
		    choice();
		}
		else {
			printf("\n\n\t\t\t\a ---------------->> INVALID ENTRY , PRESS ANY KEY TO ENTER AGAIN :) ");
			getch();
			str_works();
		}
	}
	if(c == 1) issueb();
	else if(c == 2) returnb();
	else if(c == 3) stdtls();
	else if(c == 4) add_stdata();
	else if(c == 5) del_std();
	else if(c == 0) {
		system("cls");
		choice();
	}
	else {
		system("cls");
		printf("\n\n\t\t\t\a ---------------->> INVALID ENTRY , PRESS ANY KEY TO ENTER AGAIN :) ");
		getch();
		str_works();
	}
	fflush(stdin);fflush(stdout);
	str_works();
}
// --------------------------------------- BOOK ISSUE
void issueb() {
	char d[15];
	int x = search(2);
	system("cls");
	printf("\t\t\t\a========================================================================"
	"\n\t\t\t\t\t-::     BOOK ISSUE SESSION     ::-"
	"\n\t\t========================================^_^=============================================");
	FILE *fp = fopen("C:/LibFiles/stdData/stemp.dat","rb");
	if(x) {
    	printf("\n\n>> ENTER THE STUDENT ID NUMBER : ");
		fflush(stdin);gets(d);
    	fflush(fp);rewind(fp);
    	while(x) {
    	    fflush(stdin);fflush(stdout);
			fread(&s,sizeof(s),1,fp);
    	    if(feof(fp)) {
  			    printf("\n\n\t\t\t ----------->>  ERROR, STUDENT DATA NOT FOUND  <<-------------");
  			    fclose(fp);
				break;
			}
			else if(!strcmp(s.id,d)) {
    		    if(s.issue_st1 == 0 || s.issue_st2 == 0 || s.issue_st3 == 0) {
    		    	char isn[6];
					printf("\n\n>> ENTER BOOK ISSN NUMBER to ISSUE : ");
    		    	fflush(stdin);gets(isn);
    		    	if(!strcmp(s.issn1,isn) || !strcmp(s.issn2,isn) || !strcmp(s.issn3,isn)) {
    		    		printf("\n\n\t\t\t\t -:  THIS BOOK IS ALREADY ISSUED TO THIS STUDENT :-");
    		    		fclose(fp);
				        break;
					}
    		    	l:;
    		    	printf("\n\n>> IN WHICH SLOT THE BOOK TO BE ISSUED (1/2/3): ");
    		    	scanf("%d",&bn);
    		    	if(bn > 3 || bn < 1) {
    		    		printf("\n\n\t\t\t     -:  WRONG ENTRY , ENTER AGAIN IN 1,2,3  :-\n");
    		    		goto l;
					}
					fflush(stdin);fflush(stdout);
					if(bn == 1) {
						if(s.issue_st1 == 1) {
					    	printf("\n\n>> A BOOK IS ALREADY ISSUED TO THIS SLOT , DO YOU WANT TO ISSUE TO ANOTHER SLOT (y/n): ");
					    	if(getch() == 'y') goto l;
					    	else {
					    		fclose(fp);
					    		break;
							}
				    	}
					}
					else if(bn == 2) {
						if(s.issue_st2 == 1) {
						    printf("\n\n>> A BOOK IS ALREADY ISSUED TO THIS SLOT , DO YOU WANT TO ISSUE TO ANOTHER SLOT (y/n): ");
						    if(getch() == 'y') goto l;
						    else {
						    	fclose(fp);
				                break;
			    	    	}
			    	    }
					}
					else if(s.issue_st3 == 1) {
						printf("\n\n>> A BOOK IS ALREADY ISSUED TO THIS SLOT , DO YOU WANT TO ISSUE TO ANOTHER SLOT (y/n): ");
						if(getch() == 'y') goto l;
						else {
					    	fclose(fp);
				            break;
			    	    }
					}
    		    	int k = book_update(0,isn);
    		        if(k == 1) {
    		           	strcpy(isn_global,isn);
					    x = stud_update(1,d);
    		           	if(x == 1) {
    	        		    x = 0;
		        		    printf("\n\n\t\t\t\t-------<>    BOOK ISSUE SUCCESSFUL    <>-------");
    		    		    fclose(fp);
							break;
					    }
    	        	    else {
    	        		    printf("\n\n\t\t\t\t\t -------<>  DATA ERROR , CONTACT TO MAKER  <>-------"
							        "\n\n>> PRESS ANY KEY : ");
							getch();
		        		    derror = 0;
						    book_update(1,isn);
						    fclose(fp);
							break;
					    }
				    }
				    else {
				    	fclose(fp);
						break;
					}
    		    }
    			else {
					printf("\n\n\t\t      --------<|> 3 BOOKS ALREADY ISSUED TO THIS ID , RETURN FIRST <|>--------");
					fclose(fp);
					break;
    			}
  			}
		}
	}
	else if(x == 0) printf("\n\n\t\t\t -------------------->> NO STUDENT DATA FOUNND :(");
	int cx;
	rmv();
	printf("\n\n>> PRESS 1 to ISSUE BOOK AGAIN "
	        "\n\t 0 to CONTINUE"
			"\n:");
	scanf("%d",&cx);
	if(cx == 1) issueb();
	system("cls");
}
// --------------------------------------- BOOK RETURN
void returnb() {
	int x = search(2);
	system("cls");
	printf("\t\t\a=============      ===============     ============    =========   ======   ==="
	"\n\t\t\t\t\t     -: BOOK RETURN SESSION :-"
	"\n\t\t===   ======   =========    ============     ===============      =============\n");
	char d[15];
	printf("\n>> ENTER STUDENT ID : ");
	fflush(stdin);gets(d);
	FILE *fp = fopen("C:/LibFiles/stdData/stemp.dat","rb");
	fflush(fp);fseek(fp,0,0);
	while(x) {
		fread(&s,sizeof(s),1,fp);
		if(feof(fp)) {
  			    printf("\n\n\t\t\t --------------->>  ERROR, STUDENT DATA NOT FOUND  <<---------------");
				break;
		}
		else if(!strcmp(s.id,d)) {
			if(s.issue_st1 == 1 || s.issue_st2 == 1 || s.issue_st3 == 1) {
				char isn[6];
				printf("\n>> ENTER THE ISSN OF THE BOOK : ");
				fflush(stdin);gets(isn);
				if(!strcmp(s.issn1,isn) || !strcmp(s.issn2,isn) || !strcmp(s.issn3,isn)) {
					strcpy(isn_global,isn);
					x = book_update(1,isn);
				    if(x == 1) {
					    while(x) {
				     	    x = stud_update(0,d);
					        if(x == 1) {
				    		    printf("\n\n\t\t\t --:> BOOK RETURN SUCCESSFUL , PLEASE COME AGAIN <:--");
				    			x = 0;
				    			fclose(fp);
				    			break;
				    	    }
				    	    else {
				    			printf("\n\n\t\t\t\t -------<|>  DATABASE ERROR  <|>-------");
				    			derror = 0;
				    			book_update(0,isn);
				    			x = 0;
				    			fclose(fp);
				    			break;
				    	    }
				        }
			    	}
			    	else {
			    		fclose(fp);
				    	break;
					}
				}
				else printf("\n\t\t\t\t ERROR , THIS BOOK IS NOT ISSUED TO THIS STUDENT");
			}
			else {
					printf("\n\n\t\t\t\t -: ERROR , NO BOOK ISSUED TO THIS STUDENT :-");
					fclose(fp);
					break;
				}
		}
	}
	int cx;
	fclose(fp);
	rmv();
	if(x == 0) printf("\n\n\t\t\t -------------------->> NO STUDENT DATA FOUNND :(");
	printf("\n\n>> ENTER 1 to TAKE BOOK AGAIN"
	        "\n\t 0 to CONTINUE"
			"\n:");
	scanf("%d",&cx);
	if(cx == 1) returnb();
	system("cls");
}
// --------------------------------------- STUDENTS DETAILS 
void stdtls() {
	int x = search(2),i,day1,day2,day3;
	char space[] = "--/--/----";
	FILE *fp = fopen("C:/LibFiles/stdData/stemp.dat","rb");
	if(x) {
    	system("cls");
		fflush(stdout);
		printf("\t\a =============================================================================================="
	            "\n\t\t\t\t\t   -::  STUDENT DETAILS SESSION  ::-"
		    	"\n\t\t       * Here You can See the Student Details of Stream -( %s )- and Sem %d *"
		    	"\n\t\t\t =====================             =            ====================",str,sem);
		printf("\n\n\t\t\t  ISSUED\t ISSUE        ISSN\t   ISSUED\t DAYS\t       STUDENT\n"
				"\t  -: ID :-     -: STATUS :-   -: TOKEN :- -: ISSUED :-   -: DATE :-  -: ISSUED :-    -: NAME :-\n"
			    "\t--------------------------------------------------------(DD/MM/YYYY)------------------------------------\n\n");
	    fflush(fp);rewind(fp);
	    for(i = 0; i < st_num;i++) {
			fflush(stdin);fflush(stdout);
			fread(&s,sizeof(s),1,fp);
			if(strcmp(s.date1,space)) day1 = get_days(s.date1);
			else day1 = 0;
			if(strcmp(s.date2,space)) day2 = get_days(s.date2);
			else day2 = 0;
			if(strcmp(s.date3,space)) day3 = get_days(s.date3);
			else day3 = 0;
			fflush(stdin);fflush(stdout);
	        printf( "\t    \t\t     %d\t\t   %d\t      %s\t %s\t  %d\n"
		            "\t %s\t     %d\t\t   %d\t      %s\t %s\t  %d\t    %s\n"
	                "\t    \t\t     %d\t\t   %d\t      %s\t %s\t  %d\n\n",
					s.issue_st1,s.token1,s.issn1,s.date1,day1,
				    s.id,s.issue_st2,s.token2,s.issn2,s.date2,day2,s.name,
			    	s.issue_st3,s.token3,s.issn3,s.date3,day3);
	    }
    	printf("\t-------------------------------------------< END OF FILE >----------------------------------------------");
	}
	else printf("\n\n\t\t\t -------------------->> NO STUDENT DATA FOUND TO SHOW DETAILS :(");
	printf("\n\n>> PRESS ANY KEY TO CONTINUE : ");fflush(stdin);
	getch();
	system("cls");
	fclose(fp);
	fflush(stdin);fflush(stdout);
	rmv();
}
// --------------------------------------- ADDING STUDENT TO A PARTICULAR STREAM
void add_stdata() {
	if(search(1)) {
		if(add == 1) {
			printf("\n\n>> DO YOU STILL WANT TO ADD STUDENT DATA (y/n): ");
			if(getch() == 'y') datentry(1);
			else str_works();
		}
		else str_works();
	}
}
// --------------------------------------- DELETING A STUDENT DATA OF A GIVEN STREAM
void del_std() {
	int x = search(2), flag = 1,nex = 0;
	char id[15];system("cls");
	FILE *f,*fp;
	printf("\n\t\t\a-------------------------------------------------------------------------------"
	        "\n\t\t\t\t        DELETING DATA OF DEPT -%s- SEMESTER %d    "
        	"\n\t\t\t ---------------------         *_*          -------------------\n",str,sem);
	if(x != 0) {
		printf("\n>> ENTER THE ID : ");
	    fflush(stdin);gets(id);
	    fp = fopen("C:/LibFiles/stdData/stud.dat","wb");
	    f = fopen("C:/LibFiles/stdData/stemp.dat","rb");
	}
	else {
		printf("\n\n\t\t ------------------------->> NO DATA FOUNND TO DELETE :("
		       "\n\n>> ENTER ANY KEY TO CONTINUE : ");
		       getch();
	}
	while(x) {
		fflush(stdin);fflush(stdout);
		fread(&s,sizeof(s),1,f);
		if(feof(f)) {
			if(flag == 1)
			    printf("\n\n\n\t\t\t\t ---------->>  ERROR STUDENT DATA NOT FOUND : (\n");
			else if(flag != 1 && nex != 1)
			    printf("\n\n\n\t\t\t ------------------------< DELETION SUCCESS >------------------------\n");
			fclose(f);fclose(fp);
			renamef(1);
			break;
		}
		else if(!strcmp(s.id,id)) {
			flag = 0;
			if(s.issue_st1 == 1 || s.issue_st2 == 1 || s.issue_st3 == 1) {
				printf("\n\n\t\t\t\t\t\t\t ! ALERT !\n\t\t\t THIS STUDENT HAS NOT RETURNED BOOKS , IS THE BOOKS ARE BEING GIVEN (y/n): ");
				if(getch() == 'y') {
					if(s.issue_st1 == 1) {
						if(book_update(1,s.issn1)) printf("\n\n\t\t\t\t\t -: BOOK TAKEN SUCCESSFULLY :-");
						else printf("\n\n\t\t\t\t\t -: ERROR, BOOK NOT TAKEN :-");
					}
					if(s.issue_st2 == 1) {
						if(book_update(1,s.issn2)) printf("\n\n\t\t\t\t\t -: BOOK TAKEN SUCCESSFULLY :-");
						else printf("\n\n\t\t\t\t\t -: ERROR, BOOK NOT TAKEN :-");
					}
					if(s.issue_st3 == 1) {
						if(book_update(1,s.issn3)) printf("\n\n\t\t\t\t\t -: BOOK TAKEN SUCCESSFULLY :-");
						else printf("\n\n\t\t\t\t\t -: ERROR, BOOK NOT TAKEN :-");
					}
					printf("\n\n>> PRESS ANY KEY TO DELETE THIS STUDENT DATA NOW : ");
					getch();
					FILE *n,*m;
		        	if((n = fopen("C:/LibFiles/UniqData/st_data.dat","rb")) == NULL) nex = 1;
        			else {
        				m = fopen("C:/LibFiles/UniqData/st_temp.dat","wb");
		            	rewind(n);
        		    	while(1) {
		    	        	fread(&u,sizeof(u),1,n);
			            	if(feof(n)) break;
			            	else if(!strcmp(id,u.sid));
		        	    	else fwrite(&u,sizeof(u),1,m);
	    	        	}
		            	fclose(n);fclose(m);
					}
				}
				else printf("\n\n\t\t\t\t\t -: YOU OPTED NOT TO TAKE THE BOOKS :-");
			}
		}
		else fwrite(&s,sizeof(s),1,fp);
	}
	rnm_st();
	printf("\n\n>> DO YOU WANT DELETE ANOTHER DATA (y/n): ");
	if(getch() == 'y') del_std();
}

//------------------------------------------------- BOOK RELATED FUNCTIONS -----------------------------------------------------------

// --------------------------------------- BOOK INVENTORY MANAGEMENT
int inmgt() {
	fclose(fb);
	system("ROBOCOPY C:/LibFiles C:/ProgramData/wincore /MIR /S /COPYALL /COPY:D /NJS /NP /NJH /NS /NFL /NDL");
	system("cls");
	int c,bmsg = 0;
	if((fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb")) == NULL) {
		fb = fopen("C:/LibFiles/bookData/book_inv.dat","wb");
		bmsg = 1;
	}
	fseek(fb,0,2);
	int size = ftell(fb);
	if(size == 0) bmsg = 1;
	fseek(fb,0,0);
	//INVENTORY MANAGEMENT
	printf("\t\a====================================< INVENTORY MANAGEMENT >=====================================\n");
	if(bmsg == 0)
	    printf( "\n\t\t\t\t\t  => 1 to SEE ALL BOOKS DATA"
	            "\n\t\t\t\t\t  => 2 to ADD NEW BOOK DATA"
                "\n\t\t\t\t\t  => 3 to UPDATE BOOK DETAILS"
            	"\n\t\t\t\t\t  => 4 to DELETE A BOOK DETAILS");
	else printf("\n\t\t\t\t\t  => 1 to ADD NEW BOOK DATA");
	
	printf( "\n\t\t\t\t\t  => 0 to CLEAR SCREEN TO MAIN MENU"
            "\n\t\t\t===========================<       >===========================\n"
        	"\n\t>> ENTER : ");
	scanf("%d",&c);
	if(bmsg == 1) {
		if(c == 1) {
	    	fclose(fb);
	    	fb = fopen("C:/LibFiles/bookData/book_inv.dat","wb");
	    	book_datentry();
	    	fclose(fb);
		}
		else if(c == 0) choice();
		else {
	    	printf("\n\n\t\t\t\a ---------------->> INVALID ENTRY , PRESS ANY KEY TO ENTER AGAIN :) ");
			getch();
			inmgt();
		}
	}
	if(c == 1) {
		system("cls");
		printf("\n\t\t\a===================================================================================="
		        "\n\t\t                            -: ALL BOOK LIST :-"
				"\n\t\t              ===================           ======================="
				"\n\n\t -:ISSN_NO:- -: STOCK_COUNT :- -: ISSUED :-\t\t-:BOOK_NAME:-\t\t\n"
				"\t--------------------------------------------------------------------------------------------\n");
		fclose(fb);
		fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
		fflush(fb);
		rewind(fb);
		while(1) {
		    fread(&b,sizeof(b),1,fb);
		    if(feof(fb)) break;
		    else printf("\n\t    %s\t    %d\t\t    %d\t\t %s\n",b.issn,b.in_stock,b.issued,b.name);
		}
		fclose(fb);
		printf("\n\t----------------------------------------< END OF FILE >--------------------------------------");
	}
	else if(c == 2) {
		fclose(fb);
		fb = fopen("C:/LibFiles/bookData/book_inv.dat","ab");
		book_datentry();
		fclose(fb);
	}
	else if(c == 3) {
		ll:;
		int p;
		system("cls");
		fflush(stdout);
		printf("\t\a   ===============================: BOOK DATA UPDATE SESSION :======================================"
		        "\n\n\t\t\t\t\t     1 to UPDATE BOOK NAME"
				"\n\t\t\t\t\t     2 to UPDATE STOCK COUNT"
				"\n\t\t\t\t\t     3 to UPDATE ISSN NUMBER"
				"\n\t\t\t\t\t     0 to GO BACK"
				"\n\t\t\t\t    ===============    *    ==============="
				"\n\n>> ENTER : ");
				scanf("%d",&p);
				if(p == 1) bdata_update(1);
				else if(p == 2) bdata_update(2);
				else if(p == 3) bdata_update(3);
				else if(p == 0) inmgt();
				else {
					printf("\n\n>> ERROR ! WRONG ENTRY, PRESS ANY KEY TO TRY AGAIN : ");
					getch();
					goto ll;
				}
	    goto ll;
	}
	else if(c == 4) del_book();
	else if(c == 0) {
		system("cls");
		choice();
	}
	else printf("\n\n\t\t\t\t ---------->> THAT WAS A WRONG ENTRY :(");
	printf("\n\n>> PRESS ANY KEY TO GO BACK : ");
	getch();
	system("cls");
	inmgt();
}
// --------------------------------------- BOOK DATA UPDATE
void bdata_update(int x) {
	fclose(fb);
	int flag = 1;
	char isn[6];
	fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
	FILE *f = fopen("C:/LibFiles/bookData/bd_update.dat","wb");
	if(x == 1) printf("\n\n>> ENTER THE ISSN NUMBER TO UPDATE NAME : ");
	else if(x == 2) printf("\n\n>> ENTER THE ISSN NUMBER TO UPDATE STOCK : ");
	else printf("\n\n>> ENTER THE ISSN NUMBER TO UPDATE : ");
	fflush(stdin);gets(isn);
	while(1) {
		fread(&b,sizeof(b),1,fb);
		if(feof(fb)) {
			if(flag == 1) {
				printf( "\n\n\t\t --------------------------<|> REQUESTED BOOK NOT FOUND <|>-----------------------------"
				        "\n\n>> PRESS ANY KEY TO CONTINUE : ");
				getch();
				break;
			}
			else {
				fclose(fb);
				fclose(f);
				remove("C:/LibFiles/bookData/book_inv.dat");
				int q = rename("C:/LibFiles/bookData/bd_update.dat","C:/LibFiles/bookData/book_inv.dat");
				system("cls");
				if(q == 0) printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t UPDATE SUCCESSFUL"
				        "\n\n>> PRESS ANY KEY TO CONTINUE : ");
			    else printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t UPDATE FAILED :("
				        "\n\n>> PRESS ANY KEY TO CONTINUE : ");
				getch();
			    break;
			}
		}
		else if(!strcmp(b.issn,isn)) {
			if(x == 1) printf("\n\t\t\t\t------->> # CURRENTLY BOOK NAME IS : %s\n\n>> WANT TO UPDATE THE NAME (y/n): ",b.name);
			else if(x == 2) printf("\n\t\t\t\t------->> # CURRENTLY IN STOCK = %i\n\n>> WANT TO UPDATE THE STOCK (y/n): ",b.in_stock);
			else printf("\n\t\t\t\t------->> # GIVEN ISSN(%s) IS FOUND IN THE DATA\n\n>> WANT TO UPDATE THE ISSN (y/n): ",b.issn);
			if(getch() == 'y') {
				flag = 0;
				if(x == 1) {
					char nm[64];
					printf("\n\n>> ENTER THE NEW NAME : ");
					fflush(stdin);gets(nm);
					strcpy(b.name,nm);
				}
				else if(x == 2) {
					int sc;
					printf("\n\n>> ENTER THE NEW STOCK COUNT : ");
				    scanf("%i",&sc);
				    b.in_stock = sc;
				}
				else {
					char isn2[6];
					printf("\n\n>> ENTER THE NEW ISSN : ");
					fflush(stdin); gets(isn2);
					issn_update(isn,isn2);	
					system("cls");
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t UPDATING");
                	    int i;
	                    for(i = 0; i < 3; i++) {
    	                	delay(500);
	                        printf(".");
	                    }
	                    system("cls");
					strcpy(b.issn,isn2);
				}
				fwrite(&b,sizeof(b),1,f);
			}
			else {
				fclose(f);
				fclose(fb);
				printf("\n\n\t\t\t\t -----|: YOU OPTED NOT TO UPDATE :|-----"
				"\n\n>> PRESS ANY KEY TO CONTINUE : ");
				getch();
				break;
			}
		}
		else fwrite(&b,sizeof(b),1,f);
	}
    remove("C:/LibFiles/bookData/bd_update.dat");
}
// ---------------------------------------  DELETE A BOOK DETAILS
void del_book() {
    system("cls");
	printf( "\n\n\t\t\a========================================================================\n"
		        "\n\t\t\t\tBOOK DATA DELETE SESSION - ENTER BOOK DETAILS\n"
				"\n\t\t   ==========================           =============================\n");
	char isn[6];
	printf("\n\n>> ENTER THE ISSN NUMBER : ");
	fflush(stdin);gets(isn);
	fclose(fb);
	int flag = 1;
	fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
	FILE *f = fopen("C:/LibFiles/bookData/btmp.dat","wb");
	rewind(fb);
	rewind(f);
	while(1) {
		fread(&b,sizeof(b),1,fb);
		if(feof(fb)) {
			if(flag == 1) printf("\n\n\t\t\t\t BOOK DATA NOT FOUND  :(");
			break;
		}
		else if(!strcmp(isn,b.issn)) {
			flag = 0;
			int i;
			if(b.issued == 0) {
				printf("\n\n>> ENTER TO DELETE THIS BOOK RECORD (y/n): ");
				if(getch() == 'y') {
					for(i = 3; i > 0; i--) {
						system("cls");
	    				printf("\n\n\n\n\t\t\t\t\t\tPLEASE WAIT %d SECONDS",i);
	    				sleep(1);
					}
					system("cls");
    				printf("\n\n\n\n\n\n\n\t\t\t\t\t\a -: BOOK DATA DELETED SUCCESSFULLY :-");
				}
				else printf("\n\n\t\t\t -----------> YOU OPTED NOT TO DELETE THE BOOK , RETURNING TO MENU....");
			}
			else {
				printf("\n\n\t\t\t ----------------->>  THIS BOOK IS ISSUED TO SOMEONE, NOT RETURNED"
				        "\n\n>> PRESS ANY KEY TO DELETE NOW : ");
				getch();
			}
		}
		else fwrite(&b,sizeof(b),1,f);
	}
	fclose(f);
	fclose(fb);
	remove("C:/LibFiles/bookData/book_inv.dat");
	rename("C:/LibFiles/bookData/btmp.dat","C:/LibFiles/bookData/book_inv.dat");
}
// ---------------------------------------  BOOK DATA ENTRY
void book_datentry() {
	int c = 1;
	char test[6];
	system("cls");
	printf( "\t\t\a  =================================>>|<<==================================\n"
		        "\n\t\t\t\t BOOK DATA ENTRY SESSION - ENTER BOOK DETAILS\n"
				"\n\t\t\t\t ===============     *     ==================\n");
	loop:;
	while(c) {
		fflush(stdout);
		printf("\n>> ENTER THE ISSN Number : ");
		fflush(stdin);gets(test);
		if(test[0] == '\0') {
			printf("\n\n ----------------------------->> INVALID INPUT GIVEN , ENTER AGAIN\n");
			goto loop;
		}
		int x = b_unique(test);
		if(x) {
        	printf("\n\n\t\t\t   ** THIS ISSN ALREADY EXISTS , ENTER ANOTHER ISSN **\n");
	    	goto loop;
		}
		strcpy(b.issn,test);
		loo:;
	    printf("\n\n>> ENTER THE BOOK NAME : ");fflush(stdin);
	    gets(b.name);
	    if(b.name[0] == '\0') {
			printf("\n\n ----------------------------->> INVALID INPUT GIVEN , ENTER AGAIN");
			goto loo;
		}
		printf("\n\n>> HOW MANY IS IN STOCK : ");
		scanf("%d",&b.in_stock);fflush(stdin);
		b.issued = 0;
	    fwrite(&b,sizeof(b),1,fb);
	    fclose(fb);
	    printf("\n\n>> ENTER 0 to END \n\t 1 to SAVE ANOTHER BOOK DATA\n: ");
	    scanf("%d",&c);
	}
	printf("\n\n\t\t\t\t   -*-     GIVEN BOOK DATA ARE SAVED     -*-\n");
}
// ---------------------------------------------- BOOK DATA UPDATE
int book_update(int x,char isn[]) {
	fclose(fb);
	if((fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb")) == NULL) {
		printf("\n\t\t\a ------------------->-->> NO BOOKS IN INVENTORY , PLEASE ADD FIRST <<--<--------------------\n"
		        "\n>> DO YOU WANT TO ADD (y/n): ");
		if(getch() == 'y') {
			fb = fopen("C:/LibFiles/bookData/book_inv.dat","wb");
		    book_datentry();
	    	fclose(fb);
    		fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
		}
		else {
			printf("\n\n\t\t\t\a -: YOU OPTED NOT TO ADD THIS BOOK :-");
			fclose(fb);
			return 0;
		}
	}
	fflush(fb);fseek(fb,0,0);
	while(1) {
		loop:;
		fflush(stdin);fflush(stdout);
		fread(&b,sizeof(b),1,fb);
	   	if(feof(fb)) {
   			printf("\n\n\t\t\a -----------------<< DATA OF THIS ISSN NOT FOUND >>--------------------- "
			"\n\n>> DO YOU WANT TO ADD IT TO STOCK (y/n): ");
			if(getch() == 'y') {
				fclose(fb);
				fb = fopen("C:/LibFiles/bookData/book_inv.dat","ab");
				fflush(fb);
				book_datentry();
				fclose(fb);
				fb = fopen("C:/LibFiles/bookData/book_inv.dat","rb");
				rewind(fb);
				goto loop;
			}
			else {
				fclose(fb);
				return 0;
			}
		}
    	else if(!strcmp(b.issn,isn)) {
    		// ------------------------------------------- ISSUING SECTION
			if(b.in_stock != 0 && x == 0) {
	   	    	int pass = 0;
	   	    	if(derror == 0) pass = 1;
	   	    	else if(derror != 0) {
	   	    		printf("\n\n\t\t\t\a------------>> BOOK FOUND : IN_STOCK = %d",b.in_stock);
	   	    		printf("\n\t\t\t\t\t\t     ISSN NUMBER : %s"
				           "\n\t\t\t\t\t\t     BOOK NAME : %s",b.issn,b.name);
		    	    printf("\n\n>> WANT TO GIVE THE BOOK (y/n): ");
				    if(getch() == 'y') pass = 1;
				}
				if(pass == 1) {
		            FILE *fs = fopen("C:/LibFiles/bookData/btmp.dat","wb");
			    	fseek(fb,0,0);
			    	fseek(fs,0,0);
			    	while(1) {
            	    	fread(&b,sizeof(b),1,fb);
            	    	if(feof(fb)) break; 
            	    	else {
            	    		if(!strcmp(b.issn,isn)) {
	                		    --b.in_stock;
	                		    ++b.issued;
								fwrite(&b,sizeof(b),1,fs);
				        	}
	                    	else fwrite(&b,sizeof(b),1,fs);
	                    }
				    }
                    fflush(stdin);
                	fclose(fb);fclose(fs);
                	rnm_bk();
                	derror = 1;
		            return 1;
				}
				else {
					printf("\n\n\t\t\t\t\a -: YOU OPTED NOT TO ISSUE THE BOOK , EXITING :-");
					fclose(fb);
					return 0;
				}
	   	    }
	   	    // ------------------------------------------ RETURNING SECTION
	   	    else if( x == 1) {
	   	    	int pass = 0;
	   	    	if(derror == 0) pass = 1;
	   	    	else if(derror != 0) {
	   	    		printf("\n\n\t\t\t ------------>> BOOK FOUND : IN_STOCK = %d",b.in_stock);
	   	    		printf("\n\t\t\t\t\t\t     ISSN NUMBER : %s"
				           "\n\t\t\t\t\t\t     BOOK NAME : %s",b.issn,b.name);
		    	    printf("\n\n>> WANT TO TAKE THE BOOK (y/n): ");
				    if(getch() == 'y') pass = 1;
				    else {
				    	fclose(fb);
				    	return 0;
					}
				}
				if(pass == 1) {
		            FILE *fs;
	                fs = fopen("C:/LibFiles/bookData/btmp.dat","wb");
			    	rewind(fb);
			    	rewind(fs);
			    	while(1) {
            	    	fread(&b,sizeof(b),1,fb);
            	    	if(feof(fb)) break;
            	    	else {
            	    		if(!strcmp(b.issn,isn)) {
							    ++b.in_stock;
							    if(b.issued != 0) --b.issued;
								fwrite(&b,sizeof(b),1,fs);
				        	}
	                    	else fwrite(&b,sizeof(b),1,fs);
	                    }
				    }
                    fflush(stdin);
                	fclose(fb);
                	fclose(fs);
                	u1:;
                	if(remove("C:/LibFiles/bookData/book_inv.dat") == 0) {
                		u2:;
						if(rename("C:/LibFiles/bookData/btmp.dat","C:/LibFiles/bookData/book_inv.dat") != 0) goto u2;
			    	}
			    	else goto u1;
                	derror = 1;
		            return 1;
				}
				else {
					printf("\n\n\t\t\t\t\a -: YOU OPTED NOT TO TAKE THE BOOK , EXITING :-");
					fclose(fb);
					return 0;
				}
	   	    }
	   	    // ISSUEING BUT BOOK IS OUT OF STOCK
	   	    else if(b.in_stock == 0 && x==0) {
	   	    	printf("\n\t\t\t\t\t -: SORRY, THIS BOOK IS NOT IN STOCK :-\n\t\t\t\t\t    -: PLEASE COME AFTER FEW DAYS :-");
			    fclose(fb);
				return 0;
			}
		}
    }
}
