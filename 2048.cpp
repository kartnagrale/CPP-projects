#include<bits/stdc++.h>
using namespace std;

struct Game2048{
    int board[4][4];
    int score;
    bool won;

    void init(){
        score=0;
        won=false;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                board[i][j]=0;
            }
        }
        randomPopulate();
        randomPopulate();
    }

    bool hasGameEnded(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==0){
                    return false;
                }
            }
        }
        return true;
    }

    void randomPopulate(){
        while(true){
            int i=rand()%4;
            int j=rand()%4;
            if(board[i][j]==0){
                int k=rand()%2;
                if(k==0)
                    board[i][j]=2;
                else
                    board[i][j]=4;
                break;
            }
        }
    }

    void swipeRight(int arr[]){
        int lastPlaced=4;
        bool canMerge=true;
        for(int i=3;i>=0;i--){
            if(arr[i]!=0){
                if(canMerge){
                    if(arr[i]==arr[lastPlaced]){
                        arr[lastPlaced]*=2;
                        score+=arr[lastPlaced];
                        if(arr[lastPlaced]==2048){
                            won=true;
                            return;
                        }
                        if(i!=lastPlaced) arr[i]=0;
                        canMerge=false;
                    }else{
                        arr[lastPlaced-1]=arr[i];
                        lastPlaced--;
                        if(i!=lastPlaced) arr[i]=0;
                        canMerge=true;
                    }
                }else{
                    arr[lastPlaced-1]=arr[i];
                    lastPlaced--;
                    if(i!=lastPlaced) arr[i]=0;
                    canMerge=true;
                }
            }
        }
    }

    bool up(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++){
                arr[3-row]=board[row][col];
            }
            swipeRight(arr);
            for(int row=0;row<4;row++){
                board[row][col]=arr[3-row];
            }
        }
        return moveEnd();
    }
    bool down(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++){
                arr[row]=board[row][col];
            }
            swipeRight(arr);
            for(int row=0;row<4;row++){
                board[row][col]=arr[row];
            }
        }
        return moveEnd();
    }
    bool left(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++){
                arr[3-col]=board[row][col];
            }
            swipeRight(arr);
            for(int col=0;col<4;col++){
                board[row][col]=arr[3-col];
            }
        }
        return moveEnd();
    }
    bool right(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++){
                arr[col]=board[row][col];
            }
            swipeRight(arr);
            for(int col=0;col<4;col++){
                board[row][col]=arr[col];
            }
        }
        return moveEnd();
    }

    bool moveEnd(){
        if(hasGameEnded()){
            return true;
        }
        else{
            randomPopulate();
            return false;
        }
    }

    void printBoard(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]!=0){
                    cout<<board[i][j]<<"\t";
                }else{
                    cout<<".\t";
                }
            }
            cout<<"\n";
        }
    }
};

int main(){
    srand(time(0));
    Game2048 myGame;
    myGame.init();
    while(true){
        myGame.printBoard();
        cout<<"Enter move? (U,D,L,R)";
        char ch;
        cin>>ch;
        int ended;
        if(ch=='U'){
            ended=myGame.up();
        }else if(ch=='D'){
            ended=myGame.down();
        }else if(ch=='L'){
            ended=myGame.left();
        }else if(ch=='R'){
            ended=myGame.right();
        }else{
            cout<<"INVALID\n";
        }
        if(myGame.won==true){
            cout<<"Congratulations! You Won The Game\n";
            cout<<"You Scored:"<<myGame.score<<"\n";
            return 0;
        }
        if(ended){
            myGame.printBoard();
            cout<<"GAME ENDED\n";
            cout<<"You Scored: "<<myGame.score<<"\n";;
            return 0;
        }
    }
    return 0;
}