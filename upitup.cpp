#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include<tuple>
#include<cmath>
#include<queue>
#include<assert.h>
#include<string.h>
using namespace std;

struct board{
    int arr[3][3];
};

void print_board(const board& board){
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            if(board.arr[r][c] == 2){cout<<"D ";}
            else if(board.arr[r][c] == 1){cout<<"U ";}
            else if(board.arr[r][c] == 0){cout<<"_ ";}
            else{cout<<"S ";}
        }
        cout<<endl;
    }
    return;
}

pair<int,int> find_space(const board& board){
    int r=0,c=0;
    for(r=0;r<3;r++){
        for(c=0;c<3;c++){
            if(board.arr[r][c]==0){
                return make_pair(r,c);
            }
        }
    }
    assert(0);
}

bool isSolvedBoard(const board& board ){  
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            if(board.arr[r][c]>1){return false;}    // 0 for _ (empty space), 1 for U (up face), 2 for D (down face), 3,4,5,6 for S (side faces)
            if((r*c==1)){
                if(board.arr[1][1]!=0){return false;}
            }
        }
    }
    return true;
}

int ord(const board& board){
    int o=0;
    int i=0;
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            o+=board.arr[r][c]*pow(7,i);
            i++;
        }
    }
    return o;
}

board up(board b, int r, int c){
    board bnew=b;
    int val=b.arr[r-1][c];
    if(val==4){val=6;}
    else if(val==2){val=5;}
    else if(val==5){val=1;}
    else if(val==6){val=2;}
    bnew.arr[r][c]=val;
    bnew.arr[r-1][c]=0;
    return bnew;
}

board down(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r+1][c];
    if(val==1){val=5;}
    else if(val==2){val=6;}
    else if(val==5){val=2;}
    else if(val==6){val=1;}
    bnew.arr[r][c]=val;
    bnew.arr[r+1][c]=0;
    return bnew;
}

board left(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r][c-1];
    if(val==1){val=4;}
    else if(val==2){val=3;}
    else if(val==3){val=1;}
    else if(val==4){val=2;}
    bnew.arr[r][c]=val;
    bnew.arr[r][c-1]=0;
    return bnew;
}

board right(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r][c+1];
    if(val==1){val=3;}
    else if(val==2){val=4;}
    else if(val==3){val=2;}
    else if(val==4){val=1;}
    bnew.arr[r][c]=val;
    bnew.arr[r][c+1]=0;
    return bnew;
}

uint8_t visited[40353600]={0};
uint64_t parent[40353600];

vector<char> solve(const board& b){
    int count=0;
    if(isSolvedBoard(b)){
        vector<char> v;
        v.push_back('Z');
        return v;
    }
    queue<board> q;             
    q.push(b);
    visited[ord(b)] = 'Z';          
    while(!q.empty()){
        board u=q.front();
        q.pop();
        if(isSolvedBoard(u)){
            vector<char> moves;
            int o=ord(u);
            while(visited[o]!= 'Z'){
                moves.push_back(visited[o]);
                o=parent[o];
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }   

        auto p=find_space(u);
        int row= p.first;
        int col= p.second;
        board a,b,c,d;
        if(row!=0){
            a=up(u,row,col);             
            int aord = ord(a);
            if (!visited[aord]) {
                visited[aord] = 'U';
                parent[aord] = ord(u);
                q.push(a);count++;
            }
        }
        if(row!=2){
            b = down(u,row,col);  
            int bord = ord(b);
            if (!visited[bord]) {
                visited[bord] = 'D';
                parent[bord] = ord(u);
                q.push(b);count++;
            }
        }
        if(col!=0){
            c = left(u,row,col);
            int cord = ord(c);
            if (!visited[cord]) {
                visited[cord] = 'L';
                parent[cord] = ord(u);
                q.push(c);count++;
            }
        }
        if(col!=2){
            d = right(u,row,col);
            int dord = ord(d);
            if (!visited[dord]) {
                visited[dord] = 'R';
                parent[dord] = ord(u);
                q.push(d);count++;
            }
        }
    }
    vector<char> v;
    v.push_back(0);
    return v;
}

// void initialize_board(board& b){                              
//     for(int r=0;r<3;r++){                              
//         for(int c=0;c<3;c++){
//             if(r*c==1){
//                 b.arr[r][c]=0;
//             }
//             else{
//                 int val=2;
//                 assert(val!=0);
//                 b.arr[r][c]=val;
//             }
//         }
//     }
//     return;
// }

int main(){
    board b;
    cout<<"Input format of board is:"<<endl<<"- - -\n- - -\n- - -"<<endl<<"Enter U, D, or _ as the positions mentioned above"<<endl;
    int spacePosition[2];
    for (int i = 0; i < 3; i++) {
        string str;
        getline(cin, str);
        char input[3];
        for (int j = 0; j < 3; j++) {
            input[j] = str[2 * j];
            if (input[j] == '_')
                b.arr[i][j] = 0;
            else if (input[j] == 'U')
                b.arr[i][j] = 1;
            else if (input[j] == 'D')
                b.arr[i][j] = 2;
            if (input[j] == '_') {
                spacePosition[0] = i;
                spacePosition[1] = j;
            }
        }
    }
    cout<<"Let Me Think..."<<endl;

    auto moves=solve(b);
    if(moves[0]==0){
        cout<<"You Entered an Unsolvable Board Position"<<endl;
        exit(0);
    }else if(moves[0] == 'Z'){
        cout<<"You Entered already Solved Board Position"<<endl;
        exit(0);
    }
    cout<<"Let's Start Solving"<<endl<<"The Seq. of moves are:";
    for(char c: moves){
        print_board(b);
        cout<<endl;
        if (c == 'U'){
            cout<<"Up"<<endl;
            b = up(b,spacePosition[0],spacePosition[1]);
            spacePosition[0]--;
        }else if(c == 'D'){
            cout<<"Down"<<endl;
            b = down(b,spacePosition[0],spacePosition[1]);
            spacePosition[0]++;
        }else if(c == 'L'){
            cout<<"Left"<<endl;
            b = left(b,spacePosition[0],spacePosition[1]);
            spacePosition[1]--;
        }else if(c == 'R'){
            cout<<"Right"<<endl;
            b = right(b,spacePosition[0],spacePosition[1]);
            spacePosition[1]++;
        }
    }
    print_board(b);
    cout<<endl<<"We Solved the Board"<<endl;
    return  0;
}