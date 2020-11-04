#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

class TreeNode
{
public:
    TreeNode* left;
    int data;
    TreeNode* right;
    TreeNode()
    {
        left = right = NULL;
    }
};

void convT(TreeNode*&T)
{
    if (T==NULL) return;

    if (T->left ==NULL && T->right==NULL) return;

    if (T->left!=NULL && T->right==NULL)
    {
        int a,b;
        a = T->data;b = T->left->data;
        T->data = max(a,b);T->left->data = min(a,b);
        convT(T->left);
    }

    else if (T->left==NULL && T->right !=NULL)
    {
        int a,b;
        a = T->data;b = T->right->data;
        T->data = min(a,b);T->right->data = max(a,b);
        convT(T->right);
    }

    else{
        vector<int>v(3,0);
        v[0]=T->data;v[1]=T->left->data;v[2]=T->right->data;
        sort(v.begin(),v.end());
        T->left->data = v[0];
        T->data = v[1];
        T->right->data = v[2];
        convT(T->left);
        convT(T->right);
    }
}

int minT(TreeNode*T)
{
    if (T==NULL ) return INT_MAX;
    while(T->left!=NULL && T->right==NULL)
        T=T->left;
    
    return T->data;
}

int maxT(TreeNode*T)
{
    if (T==NULL) return INT_MIN;
    while(T->left !=NULL && T->right!=NULL)
        T=T->right;

    return T->data;
}

bool check_bst(TreeNode* &T)
{   
       if (T->left == NULL && T->right == NULL) return true;

        bool o;
        if (T->left !=NULL && T->right ==NULL)
        {
            int a = maxT(T->right);
            //b=T->left->data;
            //if (a==b) return false;
            if (T->data > a)
            {
                o = check_bst(T->left);
                if (!o)
                {
                    cout<<T->data<<"\n";
                    return false;
                }
                return true;
            }
            else 
                {
                    cout<<T->data<<"\n";
                    return false;
                }
        }
        else if (T->left == NULL && T->right !=NULL)
        {
            int b = minT(T->right);
            //if (a==b) return false;
            if (T->data < b)
            {
                o = check_bst(T->right);
                if (!o) 
                {
                    cout<<T->data<<"\n";
                    return false;
                }
                else return true;
            }
            else 
                {
                    cout<<T->data<<"\n";
                    return false;
                }
        }
            
        else
        {
            int a = maxT(T->left);
            int b = minT(T->right);
            if (a<T->data && T->data < b)
            {   
                o = check_bst(T->left);
                if (!o) 
                {
                    cout<<T->data<<"\n";
                    return false;
                }

                o = check_bst(T->right);
                if (!o)
                {
                    cout<<T->data<<"\n";
                    return false;
                }

                return true;
            }
            else 
                {
                    cout<<T->data<<"\n";
                    return false;
                }
        }

}

void inorder(TreeNode* T)
{
    if (T==NULL) return;

    if (T->left !=NULL )
    {
        inorder(T->left);
    }
    cout<<T->data<<" ";
    if (T->right != NULL)
    {
        inorder(T->right);
    }
}



int main()
{
    int a;
    TreeNode* T = new TreeNode(),*tmp;
    //Input 1
    T->data = 7; 
    tmp = new TreeNode();tmp->data = 9;
    T->left = tmp;
    tmp = new TreeNode();tmp->data = 6;
    T->right = tmp;
    tmp = new TreeNode();tmp->data = 2;
    T->left->left = tmp;
    tmp = new TreeNode();tmp->data = 4;
    T->left->right = tmp;
    tmp = new TreeNode();tmp->data = 1;
    T->right->left = tmp;
    tmp = new TreeNode();tmp->data = 3;
    T->right->right = tmp;
    tmp = new TreeNode();tmp->data = 8;
    T->left->left->left = tmp;
    tmp = new TreeNode();tmp->data = 11;
    T->left->left->right = tmp;
    
    
    cout<<minT(T)<<" = min "<<maxT(T)<<" = max";
    //Input 2
    /*T->data = 5;
    tmp = new TreeNode();tmp->data = 8;
    T->left =tmp;
    tmp = new TreeNode();tmp->data = 11;
    T->right = tmp;
    tmp = new TreeNode();tmp->data = 2;
    T->right->left = tmp;
    tmp = new TreeNode();tmp->data = 4;
    T->right->right = tmp;
    tmp = new TreeNode();tmp->data = 1;
    T->right->left->left = tmp;
    tmp = new TreeNode();tmp->data = 10;
    T->right->left->right = tmp;
    tmp = new TreeNode();tmp->data = 6;
    T->right->left->left->left =tmp;*/
    bool o = check_bst(T);
    if (o) cout<<"YES\n";
    else cout<<"NO\n";
    
    convT(T);
    inorder(T);
    o = check_bst(T);
    if (o) cout<<"YES\n";
    else cout<<"NO\n";
    cout<<T->left->data<<endl<<endl;
    return 0;
}

dvb