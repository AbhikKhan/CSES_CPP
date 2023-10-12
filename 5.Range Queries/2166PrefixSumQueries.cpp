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
vt<ll> tree;
vt<ll> late;
ll getValue(ll node, ll low, ll high, ll query_low, ll query_high){
    tree[node] += late[node];
    if(low != high){
        late[2*node] += late[node];
        late[2*node+1] += late[node];
    }
    late[node] = 0;
    if(query_low <= low && query_high >= high)return tree[node];
    if(query_low > high || query_high< low)return -1e14-1;
    ll left_max = (low+high)/ 2;
    return max(getValue(2*node, low, left_max, query_low, query_high), 
                getValue(2*node+1, left_max+1, high, query_low, query_high));

}
void update(ll node, ll low, ll high, ll query_low, ll query_high, ll value){
    tree[node] += late[node];
    if(low != high){
        late[2*node] += late[node];
        late[2*node+1] += late[node];
    }
    late[node] = 0;
    if(query_low <= low && query_high >= high){
        tree[node] += value;
        if(low != high){
            late[2*node] += value;
            late[2*node+1] += value;
        }
        return;
    }
    if(query_low > high || query_high< low)return;
    ll left_max = (low+high)/ 2;
    update(2*node, low, left_max, query_low, query_high, value);
    update(2*node+1, left_max+1, high, query_low, query_high, value);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}
void solve(){
    ll m, q, k;
    cin>>m>>q;
    vt<ll> nums(1, 0);
    for(int i = 1; i<= m; ++i){
        cin>>k;
        nums.push_back(k);
    }
    ll h = (int)ceil(log2(m));
    ll n = 1LL<<h;
    tree.resize(2*n);
    late.resize(2*n, 0);
    for(int i = 0; i< m; ++i)tree[i+n] = tree[i+n-1] + nums[i+1];
    for(int i = n-1; i>= 1; --i){
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
    ll a, b;
    while(q--){
        int type;
        cin>>type;
        if(type == 2){
            cin>>a>>b;
            ll pS = 0;
            if(a> 1)pS = getValue(1, 0, n-1, a-2, a-2);
            ll maxSum = getValue(1, 0, n-1, a-1, b-1);
            maxSum -= pS;
            maxSum = max(maxSum, 0LL);
            cout<<maxSum<<endl;
        }
        else{
            cin>>a>>b;
            update(1, 0, n-1, a-1, n-1, b-nums[a]);
            nums[a] = b;
        }
        // for(int i = 1, j = 0; i< 2*n; ++i){
        //     cout<<tree[i]<<" ";
        //     if(i == (1<<(j+1))-1){
        //         j++;
        //         cout<<endl;
        //     }
        // }
        // for(int i = 1, j = 0; i< 2*n; ++i){
        //     cout<<late[i]<<" ";
        //     if(i == (1<<(j+1))-1){
        //         j++;
        //         cout<<endl;
        //     }
        // }
        // cout<<"--------------------------"<<endl;
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
