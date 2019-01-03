
#include <bits/stdc++.h>
using namespace std;
enum Color{White, Blue, Red, Black};

class Node{
    public:
        Node(int a[5][6], Color c[5][6], Color in): parent(NULL), input(in), bestx(-1), besty(-1), bestvalue(-10001) {
            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    _Record[i][j] = a[i][j]; _color[i][j] = c[i][j];
                }
            }
            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    value[i][j] = simulate(i, j, a, c);
#ifdef DEBUG_MODE
                    cout << value[i][j] << ' ';
#endif
                }
#ifdef DEBUG_MODE
                cout << '\n';
#endif
            }
            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    if(value[i][j]>bestvalue){
                        bestvalue = value[i][j]; bestx = i; besty = j;
                    }
                }
            }
        }
        int simulate(int x, int y, int a[5][6], Color c[5][6]){
            int Record[5][6];
            Color color[5][6];
            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    Record[i][j] = _Record[i][j]; color[i][j] = _color[i][j];
                }
            }
            int value = 0;
            if(input==Blue){
                if(color[x][y]==Blue || color[x][y]==White) {
                    Record[x][y]++; color[x][y] = input;
                    if(Record[x][y]==Max[x][y]){
                        status = Continue;
                        if(y>0) if(Record[x][y-1]==(Max[x][y-1]-1)) if(color[x][y-1]==Red) value += 50; else value += 30;
                        if(y<5) if(Record[x][y+1]==(Max[x][y+1]-1)) if(color[x][y+1]==Red) value += 50; else value += 30;
                        if(x>0) if(Record[x-1][y]==(Max[x-1][y]-1)) if(color[x-1][y]==Red) value += 50; else value += 30;
                        if(x<4) if(Record[x+1][y]==(Max[x+1][y]-1)) if(color[x-1][y]==Red) value += 50; else value += 30;
                    } else {
                        if(y>0) {
                            if(Record[x][y-1]==(Max[x][y-1]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x][y-1]==Blue) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x][y-1]==Blue) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x][y-1]==Blue) value += Record[x][y-1];
                                else value -= Record[x][y-1];
                            }
                        }
                        if(y<5) {
                            if(Record[x][y+1]==(Max[x][y+1]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x][y+1]==Blue) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x][y+1]==Blue) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x][y+1]==Blue) value += Record[x][y+1];
                                else value -= Record[x][y+1];
                            }
                        }
                        if(x>0) {
                            if(Record[x-1][y]==(Max[x-1][y]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x-1][y]==Blue) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x-1][y]==Blue) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x-1][y]==Blue) value += Record[x-1][y];
                                else value -= Record[x-1][y];
                            }
                        }
                        if(x<4) {
                            if(Record[x+1][y]==(Max[x+1][y]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x+1][y]==Blue) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x+1][y]==Blue) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x+1][y]==Blue) value += Record[x+1][y];
                                else value -= Record[x+1][y];
                            }
                        }
                    }
                } else {
                    return -999;
                }
                while(status==Continue){
                    Record[x][y] = -1; color[x][y] = Black;

                    if(y>0){
                        if(color[x][y-1] != Black) {
                            Record[x][y-1]++; color[x][y-1] = Blue;
                        }
                    }
                    if(y<5){
                        if(color[x][y+1] != Black) {
                            Record[x][y+1]++; color[x][y+1] = Blue;
                        }
                    }
                    if(x>0){
                        if(color[x-1][y] != Black) {
                            Record[x-1][y]++; color[x-1][y] = Blue;
                        }
                    }
                    if(x<4){
                        if(color[x+1][y] != Black) {
                            Record[x+1][y]++; color[x+1][y] = Blue;
                        }
                    }

                    status = Terminate;
                    for(x=0; x<5; x++){
                        for(y=0; y<6; y++){
                            if(Record[x][y]>=Max[x][y]){
                                status = Continue; break;
                            }
                        }
                        if(status) break;
                    }
                }

                for(x=0; x<5; x++){
                    for(y=0; y<6; y++){
                        if(color[x][y]==White || color[x][y]==Red){
                            status = Done; break;
                        }
                    }
                    if(status) break;
                }
                if(status==Terminate){
                    return 999;
                }
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        if(color[i][j]==Blue){
                            value++;
                            if(Record[i][j]==(Max[i][j]-1)) value++;
                        } else if(color[i][j]==Red){
                            value--;
                            if(Record[i][j]==(Max[i][j]-1)) value--;
                        }
                    }
                }
            } else {
                if(color[x][y]==Red || color[x][y]==White) {
                    Record[x][y]++; color[x][y] = input;
                    if(Record[x][y]==Max[x][y]){
                        status = Continue;
                        if(y>0) if(Record[x][y-1]==(Max[x][y-1]-1)) if(color[x][y-1]==Blue) value += 50; else value -= 30;
                        if(y<5) if(Record[x][y+1]==(Max[x][y+1]-1)) if(color[x][y+1]==Blue) value += 50; else value -= 30;
                        if(x>0) if(Record[x-1][y]==(Max[x-1][y]-1)) if(color[x-1][y]==Blue) value += 50; else value -= 30;
                        if(x<4) if(Record[x+1][y]==(Max[x+1][y]-1)) if(color[x-1][y]==Blue) value += 50; else value -= 30;
                    } else {
                        if(y>0) {
                            if(Record[x][y-1]==(Max[x][y-1]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x][y-1]==Red) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x][y-1]==Red) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x][y-1]==Red) value += Record[x][y-1];
                                else value -= Record[x][y-1];
                            }
                        }
                        if(y<5) {
                            if(Record[x][y+1]==(Max[x][y+1]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x][y+1]==Red) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x][y+1]==Red) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x][y+1]==Red) value += Record[x][y+1];
                                else value -= Record[x][y+1];
                            }
                        }
                        if(x>0) {
                            if(Record[x-1][y]==(Max[x-1][y]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x-1][y]==Red) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x-1][y]==Red) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x-1][y]==Red) value += Record[x-1][y];
                                else value -= Record[x-1][y];
                            }
                        }
                        if(x<4) {
                            if(Record[x+1][y]==(Max[x+1][y]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x+1][y]==Red) value += 20;
                                    else value -= 20;
                                } else {
                                    if(color[x+1][y]==Red) value += 10;
                                    else value -= 10;
                                }
                            } else {
                                if(color[x+1][y]==Red) value += Record[x+1][y];
                                else value -= Record[x+1][y];
                            }
                        }
                    }
                } else {
                    return -999;
                }
                while(status==Continue){
                    Record[x][y] = -1; color[x][y] = Black;

                    if(y>0){
                        if(color[x][y-1] != Black) {
                            Record[x][y-1]++; color[x][y-1] = Red;
                        }
                    }
                    if(y<5){
                        if(color[x][y+1] != Black) {
                            Record[x][y+1]++; color[x][y+1] = Red;
                        }
                    }
                    if(x>0){
                        if(color[x-1][y] != Black) {
                            Record[x-1][y]++; color[x-1][y] = Red;
                        }
                    }
                    if(x<4){
                        if(color[x+1][y] != Black) {
                            Record[x+1][y]++; color[x+1][y] = Red;
                        }
                    }

                    status = Terminate;
                    for(x=0; x<5; x++){
                        for(y=0; y<6; y++){
                            if(Record[x][y]>=Max[x][y]){
                                status = Continue; break;
                            }
                        }
                        if(status) break;
                    }
                }

                for(x=0; x<5; x++){
                    for(y=0; y<6; y++){
                        if(color[x][y]==White || color[x][y]==Blue){
                            status = Done; break;
                        }
                    }
                    if(status) break;
                }
                if(status==Terminate){
                    return 999;
                }
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        if(color[i][j]==Red){
                            value++;
                            if(Record[i][j]==(Max[i][j]-1)) value++;
                        } else if(color[i][j]==Blue){
                            value--;
                            if(Record[i][j]==(Max[i][j]-1)) value--;
                        }
                    }
                }
            }
            return value;
            
        }
        int Bestx(){bestvalue = -10001; return bestx;}
        int Besty(){bestvalue = -10001; return besty;}
    private:
        Node* parent;
        vector<Node*> child;
        int value[5][6];
        Color _color[5][6];
        Color input;
        int _Record[5][6];
        int Max[5][6] = {{2,3,3,3,3,2}, {3,4,4,4,4,3}, {3,4,4,4,4,3}, {3,4,4,4,4,3}, {2,3,3,3,3,2}};;
        enum Status{Terminate, Done, Continue};
        Status status = Done;
        int bestx, besty, bestvalue;
};

class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            // Your Code
            root = new Node(Record, color, inputColor);
        }
        // Any Code You Want to Add
        int getX(){
            // Your Code
            return root->Bestx();
        }
        int getY(){
            // Your Code
            return root->Besty();
        }
    private:
        int x;
        int y;
        Node* root;
};