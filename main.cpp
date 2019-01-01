    #include <bits/stdc++.h>
    //#define DEBUG_MODE
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
                    x = tmpi;
                    y = tmpj;
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
                    x = tmpi;
                    y = tmpj;
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
        playerTwo::Student student2;
        int x, y;
        cout << "Start\n";

        while(status){
            student1.makeMove(Record, Max, color, Blue);
            x = student1.getX(); y = student1.getY();
            if(color[x][y]==Blue || color[x][y]==White) {
                cout << "Player One : (" << x+1 << "," << y+1 << ")\n";
                Record[x][y]++; color[x][y] = Blue;
                if(Record[x][y]==Max[x][y]) status = Continue;
            } else {
                cout << "Player Two Win !\n"; break;
            }
            
            while(status==Continue){
#ifdef DEBUG_MODE
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
                cout << "Player Two : (" << x+1 << "," << y+1 << ")\n";
                Record[x][y]++; color[x][y] = Red;
                if(Record[x][y]==Max[x][y]) status = Continue;
            } else {
                cout << "Player One Win !\n"; break;
            }
            
            while(status==Continue){
#ifdef DEBUG_MODE
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