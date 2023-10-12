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
int getPizza(vt<int>& tree, int node, int low, int high, int query_low, int query_high){
    if(low>= query_low && high<= query_high)return tree[node];
    if(query_low> high || query_high< low)return 2e9;
    
    int leftMax = (low+high)/ 2;
    int left = getPizza(tree, 2*node, low, leftMax, query_low, query_high);
    int right = getPizza(tree, 2*node+1, leftMax+1, high, query_low, query_high);
    return min(left, right);
}
void solve(){
    int n, q;
    cin>>n>>q;
    vt<int> pizza(n);
    cin>>pizza;
    ll m = 1LL<<(int)ceil(log2(n));
    vt<int> tree1(2*m, 1e9+1), tree2(2*m, 1e9+1);
    for(int i = 0; i< n; ++i){
        tree1[i+m] = pizza[i]-i;
        tree2[i+m] = pizza[i]+i;
    }
    for(int i = m-1; i>= 1; --i){
        tree1[i] = min(tree1[2*i], tree1[2*i+1]);
        tree2[i] = min(tree2[2*i], tree2[2*i+1]);
    }
    int a, b;
    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            cin>>a>>b;
            int node = m+a-1;
            tree1[node] = b-a+1;
            node/= 2;
            while(node >= 1){
                tree1[node] = min(tree1[2*node], tree1[2*node+1]);
                node /= 2;
            }
            node = m+a-1;
            tree2[node] = b+a-1;
            node/= 2;
            while(node >= 1){
                tree2[node] = min(tree2[2*node], tree2[2*node+1]);
                node /= 2;
            }
            pizza[a-1] = b;
        }
        else{
            cin>>a;
            int left = getPizza(tree1, 1, 0, m-1, 0, a-2);
            int right = getPizza(tree2, 1, 0, m-1, a, m-1);
            cout<<min({pizza[a-1], left+a-1, right-a+1})<<endl;
        }
    }
}

int main(){
    speed_;
    ll t = 1;
    // cin>>t;
    #ifndef ONLINE_JUDGE
    freopen("2206PizzeriaQueries.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);
    #endif
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
