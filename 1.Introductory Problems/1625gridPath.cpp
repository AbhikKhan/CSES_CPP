#include<bits/stdc++.h>
using namespace std;
#define isValid(x, a, b) (x>=a && x< b? 1: 0) 

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int vis[7][7];

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3

string grid;

int findPath(int x, int y, int pos){
    if(pos == 48){
        return x == 6 && y == 0;
    }
    if(x == 6 && y == 0)return 0;
    if(vis[x][y])return 0;

    vector<bool> visited(4, -1); // to keep track of neighbouring vis/unvisited cells
    for(int i = 0; i< 4; ++i){
        if(isValid(x+dx[i],0,7) && isValid(y+dy[i],0,7))
            visited[i] = vis[x+dx[i]][y+dy[i]]; // U R D L
    }
    if(visited[UP] && visited[DOWN] && !visited[LEFT] && !visited[RIGHT])return 0; // collision to wall
    if(!visited[UP] && !visited[DOWN] && visited[LEFT] && visited[RIGHT])return 0; // or collision with other visited cell

    // corner cases
    /*
        [V][N]  [c][N]  [N][V]  [N][c]  N: not visited, V: visited, c: current Pos
        [N][c]  [N][V]  [c][N]  [V][N]
    */
    if(isValid(x-1,0,7) && isValid(y+1,0,7) && vis[x-1][y+1])
        if(!visited[RIGHT] && !visited[UP])return 0;
    if(isValid(x+1,0,7) && isValid(y+1,0,7) && vis[x+1][y+1])
        if(!visited[RIGHT] && !visited[DOWN])return 0;
    if(isValid(x-1,0,7) && isValid(y-1,0,7) && vis[x-1][y-1])
        if(!visited[LEFT] && !visited[UP])return 0;
    if(isValid(x+1,0,7) && isValid(y-1,0,7) && vis[x+1][y-1])
        if(!visited[LEFT] && !visited[DOWN])return 0;
    
    vis[x][y] = 1;
    int res = 0;
    if(grid[pos] == '?'){
        for(int i = 0; i< 4; ++i){
            if(isValid(x+dx[i], 0, 7) && isValid(y+dy[i], 0, 7))
                res += findPath(x+dx[i], y+dy[i], pos+1);
        }
    }
    else if(grid[pos] == 'U' && x-1 >= 0)
            res += findPath(x-1, y, pos+1);
    else if(grid[pos] == 'R' && y+1 < 7)
            res += findPath(x, y+1, pos+1);
    else if(grid[pos] == 'D' && x+1 < 7)
            res += findPath(x+1, y, pos+1);
    else if(grid[pos] == 'L' && y-1 >= 0)
            res += findPath(x, y-1, pos+1);
    vis[x][y] = 0;
    return res;
}

int main(){
    cin>>grid;
    cout<<findPath(0,0,0)<<endl;
    return 0;
}