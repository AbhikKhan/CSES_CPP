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

#define repP(x,s,e) for(ll x = s; x< e; ++x)
#define repN(x,s,e) for(ll x = s; x> e; --x)
#define repA(x,e) for(auto &x: e)
#define repIt(x,e) for(auto x = e.begin(); x != e.end(); x++)


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
    repA(x,X)
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
    repA(x,X)cout<<x<<" ";
    return ostream;
}
template <typename U, typename V> /* pair */
ostream& operator<<(ostream &ostream, const pair<U,V> &X){
    cout<<X.F<<" "<<X.S;
    return ostream;
}

/**************************************************************************************/
void solve(){
    ll q;
    cin>>q;
    ll powOfTen[19];
    powOfTen[0] = 1;
    repP(i,1,19){
        powOfTen[i] = powOfTen[i-1]*10;
    }
    while(q--){
        ll index;
        cin>>index;
        ll startOfBlock = 0;
        ll block = 0;
        ll totalDigits = 0;
        repP(i,1,19){
            totalDigits += (powOfTen[i]-powOfTen[i-1])*i;
            if(totalDigits >= index){
                block = i;
                break;
            }
            startOfBlock += (powOfTen[i]-powOfTen[i-1])*i;
        }
        ll left = powOfTen[block-1], right = powOfTen[block]-1;
        ll res = 0;
        ll startingOfRes = startOfBlock+1;
        while(left<= right){
            ll mid = (left+right)/ 2;
            ll pos = (mid-powOfTen[block-1])*block + startOfBlock+1;
            if(pos <= index){
                if(res< mid){
                    res = mid;
                    startingOfRes = pos;
                }
                left = mid+1;
            }
            else right = mid-1;
        }
        string str = to_string(res);
        cout<<str[index-startingOfRes]<<endl;
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
