#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

COORD c={0,0};
void gotoxy(int x,int y){
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

FILE *fp,*fp1;
typedef struct details dt;
struct details{
    char name[20];
    int contact;
    char type[50];
    int charge;
    char status[10];
};
dt u;
typedef struct count dt1;
struct count{
    int heavy;
    int two;
    int four;
    int total;
    int amount;
};
dt1 u1;

void menu();
void edit(){
    system("cls");
    fflush(stdin);
    int pos,found=0;
    char ch,name[20];
    gotoxy(15,1);
    printf("***Edit Status***");

    gotoxy(1,3);
    printf("Enter Name:");
    scanf("%[^\n]",&name);
    fflush(stdin);
    fp=fopen("record.txt","r+");
    while(fread(&u,sizeof(u),1,fp)!=0){
        if(strcmp(u.name,name)==0 && strcmpi(u.status,"parked")==0){
            system("cls");
            gotoxy(1,2);
            printf("Showing Results For %s",name);
            found=1;
            gotoxy(2,4);
            printf("Name         : %s",u.name);
            gotoxy(2,5);
            printf("Contact      : %d",u.contact);
            gotoxy(2,6);
            printf("Vehicle Type : %s",u.type);
            gotoxy(2,7);
            printf("Charge       : %d",u.charge);
            gotoxy(2,8);
            printf("Status       : %s",u.status);
            break;
        }
    }
    if(found==0){
        system("cls");
        gotoxy(4,13);
        printf("\nRecord Not Found.");
    }
    else{
        gotoxy(1,10);
        printf("You want To change the Status (Y/N) :");
        ch=getch();
        if(ch=='y' || ch=='Y'){
            pos=ftell(fp);
            fseek(fp,pos-sizeof(u),SEEK_SET);
            strcpy(u.status,"Left");
            fwrite(&u,sizeof(u),1,fp);
            fclose(fp);
            gotoxy(1,13);
            printf("Status Updated Successfully.");
        }
    }
    gotoxy(1,15);
    printf("Press any key.");
    getch();
    menu();
}
void earninig(){
    system("cls");
    gotoxy(13,1);
    printf("***Today's Earning ***");
    gotoxy(0,2);
    printf("------------------------------------------------");
    gotoxy(0,4);
    printf("------------------------------------------------");
    gotoxy(0,8);
    printf("------------------------------------------------");
    gotoxy(0,3);
    printf("| Vehicle   |");

    gotoxy(35,3);
    printf("|");
    gotoxy(47,3);
    printf("|");

    gotoxy(35,5);
    printf("|");
    gotoxy(47,5);
    printf("|");
    gotoxy(35,6);
    printf("|");
    gotoxy(47,6);
    printf("|");
    gotoxy(35,7);
    printf("|");
    gotoxy(47,7);
    printf("|");
    gotoxy(35,9);
    printf("|");
    gotoxy(47,9);
    printf("|");

    gotoxy(16,3);
    printf("Number of Vehicle");
    gotoxy(38,3);
    printf("Charge");
    gotoxy(0,5);
    printf("| 2-Wheeler |");
    gotoxy(0,6);
    printf("| 4-Wheeler |");
    gotoxy(0,7);
    printf("| Heavy     |");
    gotoxy(0,9);
    printf("| Total     |");
    gotoxy(0,10);
    printf("------------------------------------------------");
    
    fp1=fopen("count.txt","r");
    while(fread(&u1,sizeof(u1),1,fp1)!=0){}
    int pos=ftell(fp1);
    fseek(fp1,pos-sizeof(u1),SEEK_SET);
    gotoxy(24,5);
    printf("%d",u1.two);
    gotoxy(40,5);
    printf("%d",u1.two*30);

    gotoxy(24,6);
    printf("%d",u1.four);
    gotoxy(40,6);
    printf("%d",u1.four*60);

    gotoxy(24,7);
    printf("%d",u1.heavy);
    gotoxy(40,7);
    printf("%d",u1.heavy*100);

    gotoxy(24,9);
    printf("%d",u1.total);
    gotoxy(40,9);
    printf("%d",u1.amount);

    fclose(fp1);

    gotoxy(2,12);
    printf("Press any key to continue.");
    getch();
    menu();
}
void clear(){
    char c;
    system("cls");
    printf("Are You Sure To clear All The Records. (Y/N) :");
    c=getch();
    if(c=='Y' || c=='y'){
        system("cls");
        fp=fopen("record.txt","w");
        fclose(fp);
        u1.amount=0;
        u1.two=0;
        u1.four=0;
        u1.heavy=0;
        u1.total=0;
        fp1=fopen("count.txt","w");
        fclose(fp1);
        printf("\nRecords Cleared Successfully.\n");
    }
    else{
        system("cls");
        printf("\nAction Terminated.\n");
    }
    printf("Press any key to continue");
    getch();
    menu();
}
void view(){
    system("cls");
    fp=fopen("record.txt","r");
    fseek (fp, 0, SEEK_END);
    int size = ftell(fp);
    if (0 == size) {
        printf("No Records Found...Press any key.");
        fclose(fp);
        getch();
    }
    else{
        fp=fopen("record.txt","r");
        gotoxy(17,0);
        printf("*** Showing Vehicle Records ***");
        gotoxy(1,2);
        printf("*****************************************************************");
        gotoxy(2,3);
        printf("Name");
        gotoxy(18,3);
        printf("Contact");
        gotoxy(32,3);
        printf("Vehicle Type");
        gotoxy(48,3);
        printf("Charge");
        gotoxy(58,3);
        printf("Status");
        int i=5;
        while(fread(&u,sizeof(u),1,fp)!=0){
            gotoxy(2,i);
            printf("%s",strupr(u.name));
            gotoxy(18,i);
            printf("%d",u.contact);
            gotoxy(32,i);
            printf("%s",u.type);
            gotoxy(48,i);
            printf("%d",u.charge);
            gotoxy(58,i);
            printf("%s",u.status);
            i++;
        }
        fclose(fp);

        fp1=fopen("count.txt","r");
        while(fread(&u1,sizeof(u1),1,fp1)!=0){}
        int pos=ftell(fp1);
        fseek(fp1,pos-sizeof(u1),SEEK_SET);

        gotoxy(1,i+1);
        printf("*****************************************************************");
        gotoxy(2,i+3);
        printf("2 Wheeler     - ");
        gotoxy(20,i+3);
        printf("%d",u1.two);

        gotoxy(2,i+4);
        printf("4 Wheeler     - ");
        gotoxy(20,i+4);
        printf("%d",u1.four);

        gotoxy(2,i+5);
        printf("Heavy Vehicle - ");
        gotoxy(20,i+5);
        printf("%d",u1.heavy);

        gotoxy(2,i+6);
        printf("Total         -");
        gotoxy(20,i+6);
        printf("%d",u1.total);

        gotoxy(2,i+8);
        printf("Press any key to continue.");
        fclose(fp1);
        getch();
    }
    menu();
}
void fourwheeler(){
    system("cls");
    fflush(stdin);
    fp=fopen("record.txt","a");
    printf("Enter Name:");
    scanf("%[^\n]",&u.name);
    printf("Enter Contact Number:");
    scanf("%d",&u.contact);
    strcpy(u.status,"PARKED");
    u.charge=60;
    strcpy(u.type,"4 Wheeler");
    u1.four++;
    u1.amount=u1.amount+60;
    u1.total++;
    fp=fopen("record.txt","a");
    fwrite(&u,sizeof(u),1,fp);
    fclose(fp);
    fp1=fopen("count.txt","a");
    fwrite(&u1,sizeof(u1),1,fp1);
    fclose(fp1);
    printf("Information Saved. Press any key to continue.");
    getch();
}
void twowheeler(){
    system("cls");
    fflush(stdin);
    printf("Enter Name:");
    scanf("%[^\n]",&u.name);
    printf("Enter Contact Number:");
    scanf("%d",&u.contact);
    strcpy(u.status,"PARKED");
    u.charge=30;
    strcpy(u.type,"2 Wheeler");
    u1.two++;
    u1.amount=u1.amount+30;
    u1.total++;
    fp=fopen("record.txt","a");
    fwrite(&u,sizeof(u),1,fp);
    fclose(fp);
    fp1=fopen("count.txt","a");
    fwrite(&u1,sizeof(u1),1,fp1);
    fclose(fp1);
    printf("Information Saved. Press any key to continue.");
    getch();
}
void heavyvehicles(){
    system("cls");
    fflush(stdin);
    printf("Enter Name:");
    scanf("%[^\n]",&u.name);
    printf("Enter Contact Number:");
    scanf("%d",&u.contact);
    strcpy(u.status,"PARKED");
    u.charge=100;
    strcpy(u.type,"Heavy");
    u1.heavy++;
    u1.amount=u1.amount+100;
    u1.total++;
    fp=fopen("record.txt","a");
    fwrite(&u,sizeof(u),1,fp);
    fclose(fp);
    fp1=fopen("count.txt","a");
    fwrite(&u1,sizeof(u1),1,fp1);
    fclose(fp1);
    printf("Information Saved. Press any key to continue.");
    getch();
}
void entry(){
    char ch;
    system("cls");
    printf("1.Two Wheeler\n2.Four Wheeler\n3.Heavy Vehicle\n4.Back to Main Menu.\n");
    printf("Enter Your Choice:");
    ch=getch();
    switch(ch){
        case '1':
        twowheeler();
        break;
        case '2':
        fourwheeler();
        break;
        case '3':
        heavyvehicles();
        break;
        case '4':
        menu();
        break;
        default:
        system("cls");
        printf("\nInvalid Choice...Press any key.");
        getch();
        exit(0);
    }
    menu();
}
void menu(){
    char ch;
    system("cls");
    gotoxy(1,1);
    printf("*** Welcome to Parking Management System ***\n\n");
    gotoxy(0,2);
    printf("------------------------------------------------");
    gotoxy(0,9);
    printf("------------------------------------------------");

    gotoxy(10,15);
    printf("| By-Ujjwal Jain |");
    gotoxy(12,3);
    printf("1.New Vehicle Entry.");
    gotoxy(12,4);
    printf("2.View Records.");
    gotoxy(12,5);
    printf("3.Clear Records.");
    gotoxy(12,6);
    printf("4.Today's Earning.");
    gotoxy(12,7);
    printf("5.Edit Status.");
    gotoxy(12,8);
    printf("6.Exit.");
    gotoxy(8,10);
    printf("Enter Your Choice:");
    ch=getch();
    switch(ch){
    case '1':
        entry();
        break;
    case '2':
        view();
        break;
    case '3':
        clear();
        break;
    case '4':
        earninig();
        break;
    case '5':
        edit();
        break;
    case '6':
        system("cls");
        exit(0);
    default:
        system("cls");
        printf("\nInvalid Choice...Press any key.");
        getch();
        exit(0);
    }
}

void main(){
    menu();
}