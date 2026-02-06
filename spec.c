#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int pid;
    printf("Enter Host PID to spectate: ");
    scanf("%d",&pid);

    char fifo[50];
    sprintf(fifo,"/tmp/ttt_%d_spec",pid);

    int fd=open(fifo,O_RDONLY);
    char board[9];

    while(read(fd,board,9)>0){
        printf("\n %c | %c | %c\n",board[0],board[1],board[2]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n",board[3],board[4],board[5]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n\n",board[6],board[7],board[8]);
    }
}

