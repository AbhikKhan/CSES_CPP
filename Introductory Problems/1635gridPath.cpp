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

/* Segment Tree */
vector<vector<bool>> vis;
int t[7][7][49];

int helper(int i, string str, int x, int y){
    if(min(x, y)< 0 || max(x, y) >= 7)return 0;
    if(i == str.length()){
        return x == 6 && y == 0;
    }
    if(vis[x][y])return 0;
    
    if(t[x][y][str.length()-i] == -1){

        vis[x][y] = true;
        t[x][y][str.length()-i] = 0;

        if(str[i] == 'D'){
            t[x][y][str.length()-i] = helper(i+1, str, x+1, y);
        }
        else if(str[i] == 'L'){
            t[x][y][str.length()-i] = helper(i+1, str, x, y-1);
        }
        else if(str[i] == 'U'){
            t[x][y][str.length()-i] = helper(i+1, str, x-1, y);
        }
        else if(str[i] == 'R'){
            t[x][y][str.length()-i] = helper(i+1, str, x, y+1);
        }
        else{
            vector<int> dir = {-1, 0, 1, 0, -1};
            for(int k = 0; k< 4; ++k){
                t[x][y][str.length()-i] += helper(i+1, str, x+dir[k], y+dir[k+1]);
            }
        }
        vis[x][y] = false;
    }
    return t[x][y][str.length()-i];
}

int findPath(string str){
    // code here
    memset(t, -1, sizeof(t));
    vis.resize(7, vector<bool>(7, false));
    return helper(0, str, 0, 0);
}

void solve(){
    string str = "??????R??????U??????????????????????????LD????D?";
    // cin>>str;

    cout<<findPath(str)<<endl;

}

int main(){
    speed_;
    ll t;
    // cin>>t;
    solve();

    // while (t--)
    // {
    //     solve();
    // }
    
    return 0;
}