#include<bits/stdc++.h>
using namespace std;

#define speed_ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define ll long long
#define ld long double

#define vt vector
#define PQ priority_queue
#define UM unordered_map
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
    ll n;
    cin>>n;
    vt<vt<ll>> intervals(n, vt<ll>(3));
    loopP(i,0,n){
        cin>>intervals[i][0]>>intervals[i][1];
        intervals[i][2] = i;
    }
    /*
        Sort the interval so that left[i] <= left[j] where i<j
        Now for contains iterate one time from left and if right[j] <= any right[i] where i< j then i contains j
        Now for contains iterate one time from right and if right[j] <= any right[i] where i< j then i contained j
    */
    sort(all(intervals), [](vt<ll>& a, vt<ll>& b){return a[0] == b[0]? a[1]> b[1]: a[0]< b[0];});
    vt<int> contains(n, 0), contained(n, 0);
    ll maxR = 0;
    for(ll i = 0; i< n; ++i){
        if(maxR < intervals[i][1]){
            maxR = intervals[i][1];
            continue;
        }
        contains[intervals[i][2]] = 1;
    }
    ll minR = 1e9+1;
    for(ll i = n-1; i>= 0; --i){
        if(minR > intervals[i][1]){
            minR = intervals[i][1];
            continue;
        }
        contained[intervals[i][2]] = 1;
    }
    cout<<contained<<endl<<contains<<endl;
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
