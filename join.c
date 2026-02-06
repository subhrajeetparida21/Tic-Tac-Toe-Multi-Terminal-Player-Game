#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct packet { int type, pos; char msg[100]; };
char board[9]={'1','2','3','4','5','6','7','8','9'};

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

int main(){
    int hostpid;
    printf("Enter Host PID: ");
    scanf("%d",&hostpid);

    char p1[50],p2[50];
    sprintf(p1,"/tmp/ttt_%d_p1",hostpid);
    sprintf(p2,"/tmp/ttt_%d_p2",hostpid);

    int fdr=open(p1,O_RDONLY);
    int fdw=open(p2,O_WRONLY);

    struct packet data;

    printf("Enter password: ");
    scanf("%s",data.msg);
    data.type=0;
    write(fdw,&data,sizeof(data));

    read(fdr,&data,sizeof(data));
    if(strcmp(data.msg,"AUTH_OK")!=0){
        printf("Wrong password.\n");
        exit(0);
    }

    while(1){
        read(fdr,&data,sizeof(data));
        board[data.pos-1]='X';
        display();
        if(win()){printf("X wins!\n");break;}

        while(1){
            printf("Your move (O): ");
            scanf("%d",&data.pos);
            if(data.pos<1 || data.pos>9){ printf("Invalid position!\n"); continue; }
            if(board[data.pos-1]=='X'||board[data.pos-1]=='O'){ printf("Spot taken!\n"); continue; }
            break;
        }

        data.type=1;
        board[data.pos-1]='O';
        write(fdw,&data,sizeof(data));
    }
}

