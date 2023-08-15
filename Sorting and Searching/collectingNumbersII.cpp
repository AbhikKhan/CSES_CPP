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
    ll n, q, k;
    cin>>n>>q;
    vt<ll> nums(n);
    cin>>nums;

    vt<ll> ind(n);
    loopP(i,0,n){
        ind[nums[i]-1] = i;
    }
    ll res = 1;
    loopP(i,1,n){
        res += ind[i]<ind[i-1];
    }
    ll i, j;
    while(q--){
        cin>>i>>j;
        i--, j--;
        
        ll x = nums[i]-1, y = nums[j]-1;
        if(x> y)swap(x, y);
        swap(nums[i], nums[j]);

        ll l1 = x-1, r1 = x+1, l2 = y-1, r2 = y+1;

        res -= l1>=0 && ind[l1]>ind[x];
        if(abs(y-x) > 1)res -= l2>=0 && ind[l2]>ind[y];
        res -= r1<n && ind[r1]<ind[x];
        res -= r2<n && ind[r2]<ind[y];

        swap(ind[x], ind[y]);

        res += l1>=0 && ind[l1]>ind[x];
        if(abs(y-x) > 1)res += l2>=0 && ind[l2]>ind[y];
        res += r1<n && ind[r1]<ind[x];
        res += r2<n && ind[r2]<ind[y];

        cout<<res<<endl;
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