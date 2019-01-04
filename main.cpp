    #include <bits/stdc++.h>
    #define DEBUG_MODE
    //#define SIM_MODE
    #define CHECK
    #define DEBUG_MAIN
    
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
                    } else if(value[i][j]==bestvalue){
                        clock_t t = clock();
                        int tmp = t % 2;
                        if(tmp==1) {
                            bestvalue = value[i][j]; bestx = i; besty = j;
                        }
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
                    {
                        int i=x, j=y;
                        if(i>0) if(color[i-1][j]==Black) value--; 
                        if(i<4) if(color[i+1][j]==Black) value--; 
                        if(j>0) if(color[i][j-1]==Black) value--; 
                        if(j<5) if(color[i][j+1]==Black) value--; 
                    }
                    if(Record[x][y]==Max[x][y]){
                        status = Continue;
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
                            value += Record[i][j];
                            bool flag = false;

                            if(i>0) if(color[i-1][j]==Red && Record[i-1][j]==(Max[i-1][j]-1)) flag = true;
                            if(i<4) if(color[i+1][j]==Red && Record[i+1][j]==(Max[i+1][j]-1)) flag = true;
                            if(j>0) if(color[i][j-1]==Red && Record[i][j-1]==(Max[i][j-1]-1)) flag = true;
                            if(j<5) if(color[i][j+1]==Red && Record[i][j+1]==(Max[i][j+1]-1)) flag = true;
                            if(flag && (Record[i][j]==(Max[i][j]-1))) value--;
                            
                            flag = true;
                            if(i>0) if(color[i-1][j]==Blue && Record[i-1][j]==(Max[i-1][j]-1)) value -= (5-Max[i-1][j]);
                            if(i>0) if(color[i-1][j]==Blue && Record[i-1][j]==(Max[i-1][j]-1)) flag = false;
                            if(i<4) if(color[i+1][j]==Blue && Record[i+1][j]==(Max[i+1][j]-1)) value -= (5-Max[i+1][j]);
                            if(i<4) if(color[i+1][j]==Blue && Record[i+1][j]==(Max[i+1][j]-1)) flag = false;
                            if(j>0) if(color[i][j-1]==Blue && Record[i][j-1]==(Max[i][j-1]-1)) value -= (5-Max[i][j-1]);
                            if(j>0) if(color[i][j-1]==Blue && Record[i][j-1]==(Max[i][j-1]-1)) flag = false;
                            if(j<5) if(color[i][j+1]==Blue && Record[i][j+1]==(Max[i][j+1]-1)) value -= (5-Max[i][j+1]);
                            if(j<5) if(color[i][j+1]==Blue && Record[i][j+1]==(Max[i][j+1]-1)) flag = false;

                            if(i>0) if(color[i-1][j]==Blue && Record[i-1][j]==(Max[i-1][j]-2) && Record[i][j]==(Max[i][j]-1)) value += (5-Max[i-1][j]);
                            if(i<4) if(color[i+1][j]==Blue && Record[i+1][j]==(Max[i+1][j]-2) && Record[i][j]==(Max[i][j]-1)) value += (5-Max[i+1][j]);
                            if(j>0) if(color[i][j-1]==Blue && Record[i][j-1]==(Max[i][j-1]-2) && Record[i][j]==(Max[i][j]-1)) value += (5-Max[i][j-1]);
                            if(j<5) if(color[i][j+1]==Blue && Record[i][j+1]==(Max[i][j+1]-2) && Record[i][j]==(Max[i][j]-1)) value += (5-Max[i][j+1]);

                            if(flag){
                                if(Max[i][j]==2) value += 3;
                                if(Max[i][j]==3) value += 2;
                                if(Max[i][j]==4) value += 1;
                                if(Record[i][j]==(Max[i][j]-1)) value += 2;
                            }
                        }
                    }
                }
            }
            return value;
            
        }
#ifndef CHECK
        int Bestx(){bestvalue = -10001; return bestx;}
        int Besty(){bestvalue = -10001; return besty;}
#endif
#ifdef CHECK
        int Bestx(){cin >> bestx; return --bestx;}
        int Besty(){cin >> besty; return --besty;}
#endif
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

#ifdef DEBUG_MAIN
                
                cout << "Record : \n";
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        cout << Record[i][j] << ' ';
                    }
                    cout << '\n';
                }
                cout << "x : " << x+1 << " y : " << y+1 << '\n';
#endif

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

#ifdef DEBUG_MAIN
                
                cout << "Record : \n";
                for(int i=0; i<5; i++){
                    for(int j=0; j<6; j++){
                        cout << Record[i][j] << ' ';
                    }
                    cout << '\n';
                }
                cout << "x : " << x+1 << " y : " << y+1 << '\n';
#endif

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