#include<bits/stdc++.h>
using namespace std;
#define de(...) do{ \
     fprintf(stderr, "%s-%d (%s):", __func__, __LINE__, #__VA_ARGS__);\
    _DO(__VA_ARGS__);\
}while(0);

template<typename T> void _DO(T&&x) {cerr <<x << '\n'; }
template<typename A, typename ...B> void _DO(A&&a, B&&...b) {cerr << a << ','; _DO(b...);}

mt19937 rd(time(NULL));
struct treap {
	struct  node {
		node *l, *r;
		int val, sz;
		int pri;

		node( int k ) {l=r=nullptr; val=k; sz=1; pri=rd();}
		void pull() {sz = (l?l->sz:0) + (r?r->sz:0) + 1;}
	}*root=nullptr;

	int size(node*cur) {return (cur?cur->sz:0);}
	node* merge( node*a, node*b ) { //a < b
		if( !a || !b ) return (a?a:b);
		if( a->pri > b->pri )
			return a->r=merge(a->r, b), a->pull(),a;
		else
			return b->l=merge(a, b->l), b->pull(), b;
	}
	void split(node*cur, node*&a, node*&b, int k) {
		if( !cur ) {a = b = nullptr; return;}
		if( cur->val < k ) {
			a = cur;
			split( cur->r, a->r, b, k);
			a->pull();
		}
		else {
			b = cur;
			split( cur->l, a, b->l, k);
			b->pull();
		}

	}

	void ssplit(node*cur, node*&a, node*&b, int kth ) {
		if( !cur ) {a = b = nullptr; return;}
		//de(cur->val);
		if( size(cur->l)+1 <= kth ) {
			kth -= size(cur->l)+1;
			a = cur;
			ssplit( cur->r, a->r, b, kth);
			a->pull();
		}
		else {
			b = cur;
			ssplit( cur->l, a, b->l, kth);
			b->pull();
		}

	}

	void insert( node*&cur, int k ) {
		node*a, *b;
		a = b = nullptr;
		split( cur, a, b, k );
		cur = merge( a, merge( new node( k ), b ));
	};

	int get_kth( node*&cur, int kth ) {
		node*a, *b, *c;
		a = b = c = nullptr;
		//de("ok");
		ssplit( cur, a, b, kth);
		//de("ok");
		ssplit( a, a, c, kth-1);
        int ans = c->val;
        //cout << ans << '\n';
		return cur=merge( a, merge(c, b)),ans;
	};

	void insert( int k ) {insert(root, k);}
	int get_kth( int kth ) {return get_kth(root, kth);}

	void print( node*cur ) {
        if(!cur) return;
        print( cur->l );
        cout << cur->val << ' ';
        print(cur->r);

	}

	void print() {print(root); cout << '\n';}

};
int main () {
    //de("OK");
	treap t;
	for(int i = 0; i < 10; ++i) {
        int a; cin >> a;
        t.insert(a);
	}
	//cout << '\n';
	int T; cin >> T;
	//t.print();
	for( int i = 0; i < T; ++i ) {
		int a, b;
		cin >> a >> b;
		t.insert(a);
		//de(i);
		cout << t.get_kth(b) << '\n';
	}
}
