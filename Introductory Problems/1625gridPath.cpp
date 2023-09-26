#include<bits/stdc++.h>
using namespace std;

#define speed_ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define ll long long
#define ld long double

#define vt vector
#define pb push_back

#define all(x) (x).begin(), (x).end()
#define fact(n) tgamma(n + 1)


/* Trie */
struct Trie{
    bool isPresent;
    Trie *next[26];

    Trie(){
        memset(next, 0, sizeof(next));
        isPresent = false;
    }
};
int res = 0;
vector<int> dir = {-1, 0, 1, 0, -1};
void findPath(int x, int y, string& path, string& grid, vector<bool>& vis, int ind = 0){
    if(path.length()> 48)return;
    if(x == 6 && y == 0){
        if(path.length() == 48){
            cout<<path<<endl;
            res++;
        }
        return;
    }
    if(x == 0 && y == 0){
        vis[0] = true;
        path+="D";
        findPath(x+1, y, path, grid, vis, ind+1);
    }
    else{
        // collision with wall or we can say the current position divides the grid
        // to two parts having not visited cells
        
        vector<char> move = {'U', 'R', 'D', 'L'};
        for(int i = 0; i< 4; ++i){
            int X = x+dir[i], Y = y+dir[i+1];
            if(min(X, Y)< 0 || max(X, Y)>= 7 || vis[X*7+Y] || (grid[ind] != '?' && move[i] != grid[ind]))continue;

            int xx = X, yy = Y; // one step ahead
            if(move[i] == 'L')yy--;
            else if(move[i] == 'R')yy++;
            else if(move[i] == 'U')xx--;
            else xx++;

            if(min(xx, yy)< 0 || max(xx, yy)>= 7 || vis[7*xx+yy]){
                if(path.back() == 'R' || path.back() == 'L'){
                    if(X+1< 7 && X-1>= 0 && !vis[(7*(X+1)+Y)] && !vis[7*(X-1)+Y])continue;
                }
                else{
                    if(Y+1< 7 && Y-1>= 0 && !vis[(7*X+Y+1)] && !vis[7*X+Y-1])continue;
                }
            }

            path += move[i];
            vis[X*7+Y] = true;
            findPath(X, Y, path, grid, vis, ind+1);
            vis[X*7+Y] = false;
            path.pop_back();
        }
    }
}

void solve(){
    string grid = "";
    cin>>grid;
    vector<bool> vis(49);
    string path = "";
    findPath(0, 0, path, grid, vis);
    cout<<res*2<<endl;
}

int main(){
    speed_;
    ll t = 1;
    // cin>>t;

    while (t--){
        solve();
    }
    
    return 0;
}