#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
using namespace std;

class trpnode
{
public:
    trpnode* lc;
    int p;
    char key;
    trpnode* rc;
    trpnode()
    {
    	p = 0;
        lc = rc = NULL;
    }
};

deque<trpnode> nodeCache;

trpnode* newtrpnode()
{
    nodeCache.push_back(trpnode());
    trpnode* node = &nodeCache.back();
    return node;
}

trpnode* leftR(trpnode* T)
{
	trpnode* x = T->rc;
	trpnode* T2 = x->lc;

	x->lc = T;
	T->rc = T2;

	return x;
}

trpnode* rightR(trpnode* T)
{
	trpnode* x = T->lc;
	trpnode* T2 = x->rc;

	x->rc = T;
	T->lc = T2;

	return x;
}


void insert(trpnode* &T,trpnode*& par,char k,int p)
{
    if (T==NULL)
    {
        T = newtrpnode();
        T->key = k;
        T->p = p;
    }
    else
    {
        if (T->key == k)
            return;
        else if (k<T->key)
        {
        	par = T;
            insert(T->lc,par,k,p);
        }
        else if (k> T->key)
        {
        	par = T;
            insert(T->rc,par,k,p);
        }
    }
}

void del(trpnode* &T)
{
	if (T->lc == NULL && T->rc == NULL) 
	{ 
		T = NULL;return;
	}

	if (T->lc == NULL && T->rc !=NULL) 
	{
		T = T->rc;
		return;
	}
	else if (T->lc != NULL && T->rc == NULL)
	{
		T = T->lc;
		return;
	}
	else
	{
		if (T->lc->key < T->rc->key)
		{
			T->key = T->lc->key;
			T->p = T->lc->p;
			del(T->lc);
		}
		else
		{
			T->key = T->rc->key;
			T->p = T->rc->p;
			del(T->rc);
		}
	}
}

void findDel(trpnode* &T,char m)
{
	if (T->key==m)
	{
		del(T);
		return;
	}
	else if (T->key<m) findDel(T->rc,m);
	else findDel(T->lc,m);
}

void findUpd(trpnode* &T,trpnode* &par,char m)
{
	if (T->key==m)
	{
		T = par;
		return;
	}
	else if (T->key<m) findUpd(T->rc,par,m);
	else findUpd(T->lc,par,m);
}

void inorder(trpnode* T)
{
    if (T==NULL) return;
    inorder(T->lc);
    cout<<T->key<<" "<<T->p<<" ";
    inorder(T->rc);
} 

int main() 	
{
	char k;int p;

	trpnode* TRP=NULL,*par;

	
	while(true)
	{
		cin>>k;
		if (k == '#') break;
		cin>>p;
		par = NULL;
		insert(TRP,par,k,p);

		if (par!=NULL)
		{
			if (par->lc!=NULL && par->lc->p < par->p)
			{
				char m = par->key;
				par = rightR(par);
				findUpd(TRP,par,m);
			}
			else if (par->rc!=NULL & par->rc->p < par->p){
				char m = par->key;
				par = leftR(par);
				findUpd(TRP,par,m);
			}
		}
	}
	inorder(TRP);
    cout<<"\n";
	string str;
	cin>>str;
	char k1 = str[0];
	char k2 = str[1];
	findDel(TRP,k1);
	
	findDel(TRP,k2);
	inorder(TRP);

	return 0;
}


/*
nput1 : p 45 s 63 h 21 m 36 e 27 g 9 #

output1 : inorder : LDR   :

e 27 g 9 h 21 m 36 p 45 s 63

input 2 ( delete  read two keys one by one without space) :  gh

output2 ( after deleting g, h) : LDR :

e 27 m 36 p 45 s 63
*/