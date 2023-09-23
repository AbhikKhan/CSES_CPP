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
vector<ll> costSlidingWindow(vector<ll>& nums, ll k) {
    // After getting the median of each k window calculate cost based on distance from the median
    set<ll, function<bool(ll, ll)>> ms(
        [&](ll i, ll j) {
            return nums[i] == nums[j]? i< j: nums[i]< nums[j];
        }
    );
    ll n = nums.size();
    vector<ll> res;
    bool b = k%2 == 1;
    ll incrdcr = 0;
    for(ll i = 0; i< k; ++i)ms.insert(i);
    auto it = ms.begin();
    for(ll i = 0; i< k/2; ++i){
        incrdcr -= nums[*it];
        it++;
    }
    if(b)it++;
    for(ll i = 0; i< k/2; ++i){
        incrdcr += nums[*it];
    }
    vector<ll> changes = {incrdcr};

    ll med_ind = (k+1)/ 2;
    auto med = ms.begin();
    
    for(ll i = 0; i< med_ind-1; ++i)med++;
    
    if(k%2 == 1)res.push_back(nums[*med]);
    else{
        auto next = med;
        next++;
        ll d = min(nums[*med], nums[*next]);
        res.push_back(d);
    }
    
    for(ll i = k; i< n; ++i){
        ms.insert(i);
        if(nums[i] >= nums[*med]){
            if(nums[i-k] <= nums[*med]){
                med++;
            }
        }
        else{
            if(nums[i-k] >= nums[*med]){
                med--;
            }
            if(*med == i-k)med++;
        }
        
        ms.erase(i-k);
        
        if(k%2 == 1)res.push_back(nums[*med]);
        else{
            auto next = med;
            next++;
            ll d = min(nums[*med], nums[*next]);
            res.push_back(d);
        }
    }
    for(ll i = 1; i< res.size(); ++i){
        if(!b)incrdcr -= res[i-1];
        // nums[i+k-1] is comming and nums[i-1] is going out
        if(nums[i-1] != res[i-1]){
            // the window holds the previous median which has no impact on sum previously
            incrdcr += res[i-1] == res[i]? 0: res[i-1]> res[i]?res[i-1]:-res[i-1];
            // nums[i-1] will be deleted from the window so adjust the sum
            incrdcr += nums[i-1]> res[i-1]? -nums[i-1]: nums[i-1];  
        }
        if(nums[i+k-1] != res[i]){
            // the incoming element is not median
            incrdcr += nums[i+k-1] > res[i]? nums[i+k-1]: -nums[i+k-1];
            incrdcr -= res[i] == res[i-1]? 0: res[i];
        }
        changes.push_back(incrdcr);
    }
    return changes;
}


void solve(){
    ll n, k;
    cin>>n>>k;
    vt<ll> nums(n);
    cin>>nums;
    vt<ll> res = costSlidingWindow(nums, k);
    cout<<res<<endl;
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

