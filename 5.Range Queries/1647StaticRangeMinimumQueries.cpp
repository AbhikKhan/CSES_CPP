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
vt<ll> SieveOfEratosthenes(ll n);

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
vt<int> tree;
int getMin(int node, int low, int high, int query_low, int query_high){
    if(query_low <= low && query_high >= high)return tree[node];
    if(query_low> high || low > query_high)return 1e9+1;
    int last_in_left = (low + high)/ 2;
    return min(getMin(2*node, low, last_in_left, query_low, query_high),
                getMin(2*node+1, last_in_left+1, high, query_low, query_high));
}
void solve(){
    int n, q;
    cin>>n>>q;
    vt<int> nums(n);
    cin>>nums;
    n = 1<< (int)ceil(log2(n));
    tree.resize(2*n, 1e9+1);
    for(int i = 0; i< nums.size(); ++i){
        tree[i+n] = nums[i];
    }
    for(int i = n-1; i>= 1; --i){
        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    // cout<<tree<<endl;
    int a, b;
    while(q--){
        cin>>a>>b;
        cout<<getMin(1, 0, n-1, a-1, b-1)<<endl;
    }
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
vt<ll> SieveOfEratosthenes(ll n){
    vt<bool> flag(n+1, true);
    for (ll p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (flag[p]) {
            for (int i = p * p; i <= n; i += p)
                flag[i] = false;
        }
    }
    vt<ll> primes;
    for (ll p = 2; p <= n; p++)
        if (flag[p])
            primes.pb(p);
    
    return primes;
}
