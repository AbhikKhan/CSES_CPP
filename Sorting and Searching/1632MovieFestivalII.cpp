#include<bits/stdc++.h>
using namespace std;

#define speed_ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define ll long long
#define ld long double

#define vt vector
#define PQ priority_queue
#define UM unordered_map
#define US unordered_set
#define pb push_back
#define F first
#define S second

#define loopP(x,s,e) for(ll x = s; x< e; ++x)
#define loopN(x,s,e) for(ll x = s; x> e; --x)
#define loopA(x,e) for(auto &x: e)
#define loopIt(x,e) for(auto x = e.begin(); x != e.end(); x++)


#define all(x) (x).begin(), (x).end()
#define fact(n) tgamma(n + 1)

/* Declaration */
ll gcd(ll a,ll b);
ll lcm(ll a,ll b);
double pw(double x, int n);
bool isPrime(ll n);

/* Trie */
struct Trie{
    bool isPresent;
    Trie *next[26];

    Trie(){
        memset(next, 0, sizeof(next));
        isPresent = false;
    }
};

/* Inputs */
template <typename T> /* vector */
istream& operator>>(istream &istream, vt<T> &X){
    loopA(x,X)
        cin>>x;
    
    return istream;
}
template <typename U, typename V> /* pair */
istream& operator>>(istream &istream, pair<U,V> &X){
    cin>>X.F>>X.S;
    return istream;
}

/* Outputs */
template <typename T> /* vector */
ostream& operator<<(ostream &ostream, const vt<T> &X){
    loopA(x,X)cout<<x<<" ";
    return ostream;
}
template <typename U, typename V> /* pair */
ostream& operator<<(ostream &ostream, const pair<U,V> &X){
    cout<<X.F<<" "<<X.S;
    return ostream;
}

/**************************************************************************************/
void solve(){
    ll n, k;
    cin>>n>>k;
    // Greedy approach
    // assign movies to already assigned person if the end time of assigned movie is <= startTime of
    // current movie else if anyother person is left assigned the movie to him
    // else increase bad movie count
    vt<vt<ll>> movies(n, vector<ll>(2));
    cin>>movies;
    sort(all(movies), [](vt<ll>& movie1, vt<ll>& movie2){
        return movie1[1]< movie2[1];
    });
    set<pair<ll, ll>> assignMovies;
    ll badMovies = 0;
    loopP(i,0,n){
        if(assignMovies.size() == 0){
            assignMovies.insert({movies[i][1]*-1, i});
        }
        else{
            auto t = assignMovies.lower_bound({movies[i][0]*-1, -1});
            if(t != assignMovies.end()){
                assignMovies.erase(t);
                assignMovies.insert({movies[i][1]*-1, i});
            }
            else if(t == assignMovies.end() && assignMovies.size()< k){
                assignMovies.insert({movies[i][1]*-1, i});
            }
            else badMovies++;
        }
    }
    cout<<n-badMovies<<endl;
}
int main(){
    speed_;
    ll t = 1;
    // cin>>t;
    while (t--)solve();
    return 0;
}

/* Functions */
ll gcd(ll a,ll b){
    if(a == 0)return b;
    return gcd(b % a, a);
}
ll lcm(ll a,ll b){
    return (a*b)/gcd(a,b);
}
double pw(double x, int n) {
    if(n == 0)return 1;
    if(n == 1)return x;
    double k = pw(x, abs(n/2));
    k = (n % 2 == 0?1: x) * k * k;
    return n> 0? k: 1/ k;
}
bool isPrime(ll n){ 
    if (n <= 1)return false;
    if (n <= 3)return true;

    if (n % 2 == 0 || n % 3 == 0)return false;
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)return false;

    return true;
}