#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

struct packet { int type, pos; char msg[100]; };
char board[9];

void resetBoard(){ for(int i=0;i<9;i++) board[i]='1'+i; }

void display(){
    printf("\n %c | %c | %c\n",board[0],board[1],board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",board[3],board[4],board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n\n",board[6],board[7],board[8]);
}

int win(){
    int w[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(int i=0;i<8;i++)
        if(board[w[i][0]]==board[w[i][1]] && board[w[i][1]]==board[w[i][2]])
            return 1;
    return 0;
}

int draw(){
    for(int i=0;i<9;i++)
        if(board[i]!='X' && board[i]!='O') return 0;
    return 1;
}

void updateScore(char *winner){
    FILE *f=fopen("scoreboard.txt","a");
    time_t t=time(NULL);
    fprintf(f,"%s won at %s",winner,ctime(&t));
    fclose(f);
}

int main(){
    int pid=getpid();
    char p1[50],p2[50],specfifo[50];
    sprintf(p1,"/tmp/ttt_%d_p1",pid);
    sprintf(p2,"/tmp/ttt_%d_p2",pid);
    sprintf(specfifo,"/tmp/ttt_%d_spec",pid);

    mkfifo(p1,0666); mkfifo(p2,0666); mkfifo(specfifo,0666);

    char password[20];
    printf("Set game password: ");
    scanf("%s",password);
    printf("Host PID: %d\nWaiting for player...\n",pid);

    int fdw=open(p1,O_WRONLY);
    int fdr=open(p2,O_RDONLY);
    int fdspec=open(specfifo,O_WRONLY|O_NONBLOCK);

    struct packet data;

    read(fdr,&data,sizeof(data));
    if(data.type!=0 || strcmp(data.msg,password)!=0){
        strcpy(data.msg,"AUTH_FAIL");
        write(fdw,&data,sizeof(data));
        exit(0);
    }
    strcpy(data.msg,"AUTH_OK");
    write(fdw,&data,sizeof(data));
    printf("Player joined!\n");

    char replay='y';
    while(replay=='y'){
        resetBoard();
        while(1){

            while(1){
                display();
                printf("Your move (X): ");
                scanf("%d",&data.pos);
                if(data.pos<1 || data.pos>9){ printf("Invalid position!\n"); continue; }
                if(board[data.pos-1]=='X'||board[data.pos-1]=='O'){ printf("Spot taken!\n"); continue; }
                break;
            }

            data.type=1;
            board[data.pos-1]='X';
            write(fdw,&data,sizeof(data));
            write(fdspec,board,9);

            if(win()){display();printf("You win!\n");updateScore("X");break;}
            if(draw()){display();printf("Draw!\n");break;}

            read(fdr,&data,sizeof(data));
            board[data.pos-1]='O';
            write(fdspec,board,9);

            if(win()){display();printf("O wins!\n");updateScore("O");break;}
        }
        printf("Replay? (y/n): ");
        scanf(" %c",&replay);
    }

    unlink(p1); unlink(p2); unlink(specfifo);
}

