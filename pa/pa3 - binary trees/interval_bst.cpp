#include <iostream>

using namespace std;

struct Interval
{
    long long int lo;
    long long int hi;
};

struct node
{
    struct Interval key;
    struct Interval key_max;
    struct node *left = NULL;
    struct node *right = NULL;
    struct node *p = NULL;
};

struct node *T;
struct node *T_hi;
struct Interval null_interval;
    
void Insert_hi(struct Interval I)
{
    struct node *x = T_hi;
    struct node *y = NULL;
    
    struct node *ptr;
    ptr = (struct node *) malloc(sizeof(struct node));
    ptr->key = I;
    
    if(T_hi == NULL)
    {
        T_hi = ptr;
        return;
    }
    
    while(x != NULL)
    {
        y = x;
        
        if(I.hi < (x->key).hi)
            x = x->left;
        else if(I.hi > (x->key).hi)
            x = x->right;
    }

    if(I.hi < (y->key).hi)
        y->left = ptr;
    else
        y->right = ptr;
        
    ptr->p = y;
}

void InorderWalk(struct node *x)
{
    if(x != NULL)
    {
        InorderWalk(x->left);
        cout << (x->key).lo << " " << (x->key).hi << " " << endl;
        InorderWalk(x->right);
    }
}

void Insert(struct Interval I)
{
    struct node *x = T;
    struct node *y = NULL;
    
    struct node *ptr;
    ptr = (struct node *) malloc(sizeof(struct node));
    ptr->key = I;
    
    while(x != NULL)
    {
        y = x;
        
        if(I.lo < (x->key).lo)
            x = x->left;
        else if(I.lo > (x->key).lo)
            x = x->right;
    }
    
    ptr->p = y;
    ptr->key_max = ptr->key;
    
    if(y == NULL)
        T = ptr;
    else if(I.lo < (y->key).lo)
        y->left = ptr;
    else
        y->right = ptr;
    
    while(ptr != NULL)
    {
        if(I.hi > (ptr->key_max).hi)
            ptr->key_max = I;
        
        ptr = ptr->p;
    }
}

struct node * Min(struct node *T)
{
    struct node *x = T;
    
    while(x != NULL && x->left != NULL)
        x = x->left;
    
    return x;
}

void Transplant(struct node *f, struct node *g)
{
    if(f->p == NULL) 
        T = g;
    else if(f == f->p->right) 
        f->p->right = g;
    else 
        f->p->left = g;
    
    if(g != NULL) g->p = f->p;
}

void Transplant_hi(struct node *f, struct node *g)
{
    if(f->p == NULL) 
        T_hi = g;
    else if(f == f->p->right) 
        f->p->right = g;
    else 
        f->p->left = g;
    
    if(g != NULL) g->p = f->p;
}

void DeleteFix(struct node *q)
{
    //assumes q has transplanted it's ancestor so as to affect all new ancestors of q
    struct node *ptr = q;
    
    while(ptr != NULL)
    {
        struct Interval temp_max = ptr->key;
        if(ptr->right != NULL && (ptr->right->key_max).hi > temp_max.hi)
            temp_max = ptr->right->key_max;
        if(ptr->left != NULL && (ptr->left->key_max).hi > temp_max.hi)
            temp_max = ptr->left->key_max;
        
        ptr->key_max = temp_max;
        ptr = ptr->p;
    }
}

void Delete_hi(struct Interval I)
{
    struct node *z = T_hi;
    while(z != NULL && (z->key).hi != I.hi)
    {
        if(I.hi < (z->key).hi) z = z->left;
        else z = z->right;
    }

    if(z == NULL || (z->key).lo != I.lo) return;
    
    if(z->left == NULL)
        Transplant_hi(z, z->right);
    else if(z->right == NULL)
        Transplant_hi(z, z->left);
    else
    {
        struct node *y = Min(z->right);

        if(y->p != z)
        {
            Transplant_hi(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        
        Transplant_hi(z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

void Delete(struct Interval I)
{
    struct node *z = T;
    while(z != NULL && (z->key).lo != I.lo)
    {
        if(I.lo < (z->key).lo) z = z->left;
        else z = z->right;
    }

    if(z == NULL || (z->key).hi != I.hi) return;    //The interval is not present
    
    if(z->left == NULL)
    {
        Transplant(z, z->right);
        DeleteFix(z->p);
    }
    else if(z->right == NULL)
    {
        Transplant(z, z->left);
        DeleteFix(z->p);
    }
    else
    {
        struct node *y = Min(z->right);
        
        struct node *b = y->p;
        
        if(y->p != z)
        {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        
        DeleteFix(b);
    }
}

struct Interval Max()
{
    return T->key_max;
    // struct node *x = T_hi;
    
    // while(x != NULL && x->right != NULL)
    //     x = x->right;
    
    // return x->key;
}

struct Interval LoSucc(struct Interval I)
{
    struct node *x = T;
    while(x != NULL && (x->key).lo != I.lo)
    {
        if(I.lo < (x->key).lo) x = x->left;
        else x = x->right;
    }
    
    if(x == NULL) return null_interval;
    
    if(x->right != NULL) return Min(x->right)->key;
    else if(x->right == NULL)
    {
        struct node *y = x->p;
        while(y != NULL && x == y->right)
        {
            x = y;
            y = y->p;
        }
        
        if(y == NULL) return null_interval;
        else return y->key;
    }
}

struct Interval HiSucc(struct Interval I)
{
    struct node *x = T_hi;
    while(x != NULL && (x->key).hi != I.hi)
    {
        if(I.hi < (x->key).hi) x = x->left;
        else x = x->right;
    }
    
    if(x == NULL)
        return null_interval;
    
    if(x->right != NULL) return Min(x->right)->key;
    else if(x->right == NULL)
    {
        struct node *y = x->p;
        while(y != NULL && x == y->right)
        {
            x = y;
            y = y->p;
        }
        
        if(y == NULL) return null_interval;
        else return y->key;
    }
}

int IsOverlap(struct Interval I)
{
    int found = 0;
    struct node *x = T;
    
    while(x != NULL && found == 0)
    {
        if(I.lo <= (x->key).hi && I.hi >= (x->key).lo)
            found = 1;
        else if(x->left != NULL && I.lo <= (x->left->key_max).hi)
            x = x->left;
        else
            x = x->right;
    }
    
    return found;
    // return 1;
    
    // while(x!=NULL && !(I.lo<=(x->key.hi) && I.hi>=(x->key).lo))
    // {
    //     if(x->left != NULL && (x->left->key_max).hi >= I.lo)
    //         x = x->left;
    //     else x=x->right;
    // }
    
    // if(x==NULL) return 0;
    // else return 1;
}

int main()
{
    std::ios::sync_with_stdio(false);

    long long int M;
    cin >> M;
    
    null_interval.lo = NULL;
    null_interval.hi = NULL;

    for(long long int p = 0;p<M;p++)
    {
        T = NULL;
        T_hi = NULL;
        
        long long int N;
        cin >> N;
        
        for(long long int q = 0;q<N;q++)
        {
            string op;
            cin >> op;

            if(op == "+")
            {
                struct Interval I;
                cin >> I.lo >> I.hi;
                Insert(I);
                Insert_hi(I);
            }
            else if(op == "-")
            {
                struct Interval I;
                cin >> I.lo >> I.hi;
                Delete(I);
                Delete_hi(I);
            }
            else if(op == "min")
            {
                struct node *J = Min(T);
                cout << "[" << (J->key).lo << " " << (J->key).hi << "]" << endl;
            }
            else if(op == "max")
            {
                struct Interval J = Max();
                cout << "[" << J.lo << " " << J.hi << "]" << endl;
            }
            else if(op == "lsucc")
            {
                struct Interval I;
                cin >> I.lo >> I.hi;
                struct Interval J = LoSucc(I);
                if(J.lo == NULL) 
                    cout << "INVALID" << endl;
                else 
                    cout << "[" << J.lo << " " << J.hi << "]" << endl;
            }
            else if(op == "hsucc")
            {
                struct Interval I;
                cin >> I.lo >> I.hi;
                struct Interval J = HiSucc(I);
                if(J.hi == NULL)
                    cout << "INVALID" << endl;
                else
                    cout << "[" << J.lo << " " << J.hi << "]" << endl;
            }
            else if(op == "overlap")
            {
                struct Interval I;
                cin >> I.lo >> I.hi;
                cout << IsOverlap(I) << endl;
            }
        }
        
        // InorderWalk(T_hi);
    }
}