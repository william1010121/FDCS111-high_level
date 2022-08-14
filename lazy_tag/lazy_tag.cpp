#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
constexpr int mxN = 3e5;

ll ar[ mxN ];
ll seg[ mxN<<2 ];
ll tag[ mxN<<2 ];

int N;
void pull(const int &id) {
	seg[ id ] = seg[ id<<1 ] + seg[ id<<1|1 ];
}

void push( const int &l, const int &r, const int &id ) {
	int mid = (l+r)>>1;
	if( r-l == 1 ) return;	
	seg[ id<<1 ] += tag[ id ]*( mid-l );
	seg[ id<<1|1 ] += tag[ id ]*( r-mid );
	tag[ id<<1 ] += tag[ id ];
	tag[ id<<1|1 ] += tag[ id ];
	tag[ id ] = 0;
	return;
}
void build(int l=0, int r=N, int id=1) {
	const int mid = (l+r)>>1;
	if( r-l == 1 ) return seg[ id ] = ar[ l ], void();
	build( l, mid, id<<1 ); build( mid, r, id<<1|1 );
	pull( id );
}

int query( int ql, int qr, int l=0, int r=N, int id=1 ) {
	const int mid = (l+r)>>1;
	if( ql >= r || qr <= l ) return 0;
	push( l, r, id );
	if( ql <= l && r <= qr ) return seg[id];
	return query( ql, qr, l, mid, id<<1 ) + query( ql, qr, mid, r, id<<1|1 );	
}
void update( int ul, int ur, long long k, int l=0, int r=N, int id=1 ) {
	const int mid = (l+r)>>1;
	if( ul >= r || ur <= l ) return;
	push( l, r, id );
	if( ul <= l && r <= ur ) {
		seg[ id ] += k*( r-l );
		tag[ id ] += k;
		push(l, r, id );
		return;
	}
	update( ul, ur, k, l, mid, id<<1 );
	update( ul, ur, k, mid, r, id<<1|1 );
	pull(id);
	return;
}



int main () {
	int Q; cin >> N >> Q;
	for( int i = 0; i < N; ++i ) {
		cin >> ar[ i ];
	}	

	build();
	for( int i = 0; i < Q; ++i ) {
		bool md; cin >> md;
		if( md ) {
			int l, r; cin >> l >> r;
			--l;
			cout << query( l, r ) << '\n';	
		}
		else {
			int l, r;
			long long k;
			cin >> l >> r >> k;
			--l;
			update(l, r, k);
		}
	}
}
