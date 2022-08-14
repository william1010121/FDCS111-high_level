#include<bits/stdc++.h>
using namespace std;

#define V vector
#define F first
#define S second 
#define MEM(x) memset( x, 0, sizeof(x));
#define ALL(x) begin(x), end(x)
#define EB emplace_back
#define EP emplace

typedef long long ll;
typedef pair<int,int> pii;

constexpr int mxN = 1e5+1;

#define de(...) do{\
	fprintf(stderr, "%s-%d (%s):", __func__, __LINE__, #__VA_ARGS__);\
	_DO(__VA_ARGS__);\
}while(0);

template<typename T> void _DO(T&&x) {cerr << x << '\n'; }
template<typename A, typename ...B> void _DO( A&&a, B&&...b) {cerr << a << ','; _DO(b...);}
int main () {
	int N, M, st, ed;
	cin >> N >> M >> st >> ed;

	vector<pii> graph[N+1];
	for( int i = 0; i < M; i++  ){
		int a, b, w; cin >> a >> b >> w;
		graph[a].EB(w, b);
	}

	priority_queue<pii, V<pii>, greater<pii>> pq;

	pq.EP(0, st);
	int dis[ N+1 ];
	MEM(dis);
	while(!pq.empty() ) {
		auto a = pq.top(); pq.pop();
		if( dis[ a.S ] != 0 ) continue;;
		dis[ a.S ] = a.F;
		for( auto &i : graph[ a.S ] ) {
			if( i.S == st ) continue;
			if( dis[ i.S ] != 0 ) continue;
			pq.EP( i.F+a.F, i.S );
		}
	}

	cout << (dis[ ed ] == 0 ? -1 : dis[ ed ] ) << '\n';
}
