#include <stdio.h>

#define length 3

char board[3][3] =
{ 
    {'\0','\0','\0'},
    {'\0','\0','\0'},
    {'\0','\0','\0'},
};

int player = 1;

char *boardValue(int position) {
    switch(position) {
        case 1:
            return &board[0][0];
        case 2:
            return &board[0][1];
        case 3:
            return &board[0][2];
        case 4:
            return &board[1][0];
        case 5:
            return &board[1][1];
        case 6:
            return &board[1][2];
        case 7:
            return &board[2][0];
        case 8:
            return &board[2][1];
        case 9:
            return &board[2][2];
    }
}

int main(void) {
    game();
	return 0;
}

void game() {    
    printf("\n       Tic Tac Toe\n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n");
    
    boardDraw();
    playGame();
}

void boardDraw() {
    int number = 1;
     for(int i = 0; i < length;i++) {
        char row[3];
        
        for(int j = 0; j < length;j++) {
            if(board[i][j] == '\0') {
              row[j] = number+48;
              number++;
              continue;
            }
            
            row[j] = board[i][j];
            number++;
        }
        
        printf("     |     |     \n");
        printf("  %c  |  %c  |  %c  \n", row[0] , row[1], row[2]);
        printf("_____|_____|_____\n");
    }
}

void playGame() {
    boardAdd(typePosition(), player);
    
    if(winnerOrDraw()){
        return;
    }
    
    player = player == 1 ? 2 : 1;
    system("clear");
    game();
}

int typePosition() {
    int position;
    printf("\nPlayer %d, enter a number: ", player); scanf("%d", &position);
    
    while((position < 1 || position > 9) || *boardValue(position) != '\0') {
         printf("Invalid move, please enter a number: "); scanf("%d", &position);
    }
    
    return position;
}

void boardAdd(int position, int player) {
    char valor = player == 1 ? 'X' : 'O';
    char *pointer = boardValue(position);
    *pointer = valor;
}

int winnerOrDraw() {
    int action = boardCheck();
    
    if(action == 0) {
        draw();
        return 1;
        
    } else if(action == 1){
        winner();
        return 1;
    }
    
    return 0;
}

int boardCheck() {
    if(horizontal() || vertical() || diagonalPrincipal() || diagonalSecundaria()) {
        return 1;
    } else if(drawLogic()) {
        return 0;
    }
    
    return -1;
}

int horizontal() {
    for(int i = 0; i < length;i++) {
        int equals = 0;
        
        for(int j = 0; j < length;j++) {
            if(board[i][0] != board[i][j] || board[i][0] == '\0' || board[i][j] == '\0') { 
                break;
            }
            
            if(equals++ == 2) {
                return 1;
            }
        }
        
    }
    
    return 0;
}

int vertical() {
    for(int j = 0; j < length;j++) {
        int equals = 0;
        
        for(int i = 0; i < length;i++) {
            if(board[0][j] != board[i][j] || board[i][j] == '\0') { 
                break;
            }
            
            if(equals++ == 2) {
                return 1;
            }
        }
    }
    
    return 0;
}

int diagonalPrincipal() {
    if(*boardValue(1) == '\0' || *boardValue(5)== '\0' || *boardValue(9) == '\0') {
        return 0;
    }
    
    if((*boardValue(1) == *boardValue(5)) && (*boardValue(1) == *boardValue(9)) && (*boardValue(5) == *boardValue(9))){
        return 1;
    }
    
    return 0;
}

int diagonalSecundaria() {
    if((*boardValue(3) == '\0' || *boardValue(5) == '\0' || *boardValue(7)== '\0')){
         return 0;
    }
    
    else if((*boardValue(3) == *boardValue(5)) && (*boardValue(3) == *boardValue(7)) && (*boardValue(5) == *boardValue(7))){
        return 1;
    }
    
    return 0;
}


int drawLogic() {
    for(int i = 0; i < length;i++) {
        for(int j = 0; j < length;j++) {
            if(board[i][j] == '\0') { 
                return 0;
            }
        }
    }
    
    return 1;
}

void winner() {
    system("clear");
    printf("\n       Tic Tac Toe\n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n");
    
    boardDraw();
    printf("==> Player %d win\n", player);
}

void draw() {
    system("clear");
    printf("\n\n       Tic Tac Toe\n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n");
    
    boardDraw();
    printf("\n==>DRAW!!!!\n");
}