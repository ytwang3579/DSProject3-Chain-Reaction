    #include <bits/stdc++.h>
    //#define DEBUG_MODE
    //#define SIM_MODE
    //#define CHECK
    using namespace std;

    enum PlayStatus{
        // not important
        Terminate,
        Done,
        Continue
    };

    enum Color{
        White, // Initital 0
        Blue, // Player One
        Red, // Player Two
        Black //Explosion
    };

    namespace playerOne
    {
        // Your Code
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
                    if(Max[x][y]==2 && color[x][y]==White) value += 50;
                    if(y>0) if(color[x][y-1]==White) if(color[x][y]==White) value += 10; else value += 5;
                    if(y<5) if(color[x][y+1]==White) if(color[x][y]==White) value += 10; else value += 5;
                    if(x>0) if(color[x-1][y]==White) if(color[x][y]==White) value += 10; else value += 5;
                    if(x<4) if(color[x-1][y]==White) if(color[x][y]==White) value += 10; else value += 5;
                    Record[x][y]++; color[x][y] = input;
                    if(Record[x][y]==Max[x][y]){
                        status = Continue;
                        if(y>0) {
                            if(Record[x][y-1]==(Max[x][y-1]-2)) {
                                if(color[x][y-1]==Blue) value += 50;
                                if(y>1) if(color[x][y-2]==Red && Record[x][y-2]==(Max[x][y-2]-1)) value -= 50;
                                if(x>0) if(color[x-1][y-1]==Red && Record[x-1][y-1]==(Max[x-1][y-1]-1)) value -= 50;
                                if(x<4) if(color[x+1][y-1]==Red && Record[x+1][y-1]==(Max[x+1][y-1]-1)) value -= 50;
                            }
                        }
                        if(y<5) {
                            if(Record[x][y+1]==(Max[x][y+1]-2)) {
                                if(color[x][y+1]==Blue) value += 50;
                                if(y<4) if(color[x][y+2]==Red && Record[x][y+2]==(Max[x][y+2]-1)) value -= 50;
                                if(x>0) if(color[x-1][y+1]==Red && Record[x-1][y+1]==(Max[x-1][y+1]-1)) value -= 50;
                                if(x<4) if(color[x+1][y+1]==Red && Record[x+1][y+1]==(Max[x+1][y+1]-1)) value -= 50;
                            }
                        }
                        if(x>0) {
                            if(Record[x-1][y]==(Max[x-1][y]-2)) {
                                if(color[x-1][y]==Blue) value += 50;
                                if(x>1) if(color[x-2][y]==Red && Record[x-2][y]==(Max[x-2][y]-1)) value -= 50;
                                if(y>0) if(color[x-1][y-1]==Red && Record[x-1][y-1]==(Max[x-1][y-1]-1)) value -= 50;
                                if(y<5) if(color[x-1][y+1]==Red && Record[x-1][y+1]==(Max[x-1][y+1]-1)) value -= 50;
                            }
                        }
                        if(x<4) {
                            if(Record[x+1][y]==(Max[x+1][y]-2)) {
                                if(color[x-1][y]==Blue) value += 50;
                                if(x<3) if(color[x+2][y]==Red && Record[x+2][y]==(Max[x+2][y]-1)) value -= 50;
                                if(y>0) if(color[x+1][y-1]==Red && Record[x+1][y-1]==(Max[x+1][y-1]-1)) value -= 50;
                                if(y<5) if(color[x+1][y+1]==Red && Record[x+1][y+1]==(Max[x+1][y+1]-1)) value -= 50;
                            }
                        }

                        if(y>0) if(Record[x][y-1]==(Max[x][y-1]-1)) if(color[x][y-1]==Blue) value += 500; else value -= 50;
                        if(y<5) if(Record[x][y+1]==(Max[x][y+1]-1)) if(color[x][y+1]==Blue) value += 500; else value -= 50;
                        if(x>0) if(Record[x-1][y]==(Max[x-1][y]-1)) if(color[x-1][y]==Blue) value += 500; else value -= 50;
                        if(x<4) if(Record[x+1][y]==(Max[x+1][y]-1)) if(color[x-1][y]==Blue) value += 500; else value -= 50;
                    } else {
                        if(y>0) {
                            if(Record[x][y-1]==(Max[x][y-1]-1)) {
                                if(Record[x][y]==(Max[x][y]-1)){
                                    if(color[x][y-1]==Red) value += 20;
                                    else value -= 50;
                                } else if(Record[x][y]==(Max[x][y]-2)){
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
                                    else value -= 50;
                                } else if(Record[x][y]==(Max[x][y]-2)){
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
                                    else value -= 50;
                                } else if(Record[x][y]==(Max[x][y]-2)){
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
                                    else value -= 50;
                                } else if(Record[x][y]==(Max[x][y]-2)){
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
                            if(Record[i][j]==(Max[i][j]-1)) value += (5-Max[i][j]);
                        } /*else if(color[i][j]==Blue){
                            value--;
                            if(Record[i][j]==(Max[i][j]-1)) value -= (5-Max[i][j]);
                        } */else if(color[i][j]==White){
                            value++;
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
    };

    namespace playerTwo
    {
        // Your Code
        class Student{
            public:
                void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
                    // Your Code
                    clock_t t;
                    int tmpi, tmpj;
                    do{
                        t = clock();
                        tmpi = t % 5;
                        t = clock();
                        tmpj = t % 6;
                    } while(color[tmpi][tmpj]!=White && color[tmpi][tmpj]!=inputColor);
#ifndef CHECK
                    x = tmpi;
                    y = tmpj;
#endif
#ifdef CHECK
                    cin >> x >> y;
                    x--; y--;
#endif
                }
                // Any Code You Want to Add
                int getX(){
                    // Your Code
                    return x;
                }
                int getY(){
                    // Your Code
                    return y;
                }
            private:
                int x;
                int y;
        };
    };

    int main()
    {
        // something check who is the winner
        int Record[5][6] = {{0}};
        int Max[5][6] = {{2,3,3,3,3,2}, {3,4,4,4,4,3}, {3,4,4,4,4,3}, {3,4,4,4,4,3}, {2,3,3,3,3,2}};
        Color color[5][6] = {{White}};
        PlayStatus status = Done;
        playerOne::Student student1;
        playerOne::Student student2;
        int x, y;
        cout << "Start\n";

        while(status){
            student1.makeMove(Record, Max, color, Blue);
            x = student1.getX(); y = student1.getY();
            if(color[x][y]==Blue || color[x][y]==White) {
#ifndef SIM_MODE
                cout << "Player One : (" << x+1 << "," << y+1 << ")\n";
#endif
                Record[x][y]++; color[x][y] = Blue;
                if(Record[x][y]==Max[x][y]) status = Continue;
            } else {
                cout << "Player Two Win !\n"; break;
            }
            
            while(status==Continue){

#ifdef DEBUG_MAIN
                int debugtmp;
                cout << "Record : \n";
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        cout << Record[i][j] << ' ';
                    }
                    cout << '\n';
                }
                cout << "x : " << x+1 << " y : " << y+1 << '\n';
                cin >> debugtmp;
#endif
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
                cout << "Player One Win !\n"; break;
            }
            
            student2.makeMove(Record, Max, color, Red);
            x = student2.getX(); y = student2.getY();
            if(color[x][y]==Red || color[x][y]==White) {
#ifndef SIM_MODE
                cout << "Player Two : (" << x+1 << "," << y+1 << ")\n";
#endif
                Record[x][y]++; color[x][y] = Red;
                if(Record[x][y]==Max[x][y]) status = Continue;
            } else {
                cout << "Player One Win !\n"; break;
            }
            
            while(status==Continue){
#ifdef DEBUG_MAIN
                int debugtmp;
                cout << "Record : \n";
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        cout << Record[i][j] << ' ';
                    }
                    cout << '\n';
                }
                cout << "x : " << x+1 << " y : " << y+1 << '\n';
                cin >> debugtmp;
#endif
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
                if(x<6){
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
                };
                
            }

            status = Terminate;
            for(x=0; x<5; x++){
                for(y=0; y<6; y++){
                    if(color[x][y]==White || color[x][y]==Blue){
                        status = Done; break;
                    }
                }
                if(status) break;
            }
            if(status==Terminate){
                cout << "Player Two Win !\n"; break;
            }
        }
        
        return 0;
    }