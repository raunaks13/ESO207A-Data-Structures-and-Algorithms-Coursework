#include <iostream>

using namespace std;

struct AdjListNode
{
    int key;
    struct AdjListNode* next;
};

int d[10000000];
int visited[10000000];
int p[10000000];
int l_bridge[10000000];
int l[10000000];
int art[10000000];
int t = 0;

struct AdjListNode* bridge[10000000];

void DFS_Visit(struct AdjListNode * Adj[], int V, int E, int u)
{
    visited[u] = 1;
    t++;
    d[u] = t;
    l[u] = t;
    int root_adj = 0;
    
    struct AdjListNode *ptr = Adj[u];
    
    ptr = Adj[u];
    while(ptr != NULL)
    {
        root_adj++;

        if(visited[ptr->key] == 0)
        {
            p[ptr->key] = u;

            DFS_Visit(Adj, V, E, ptr->key);
            
            if(p[u] == -10)
            {
                if(root_adj>=2) art[u] = 1;
            }
            else
            {
                if(l[ptr->key] < l[u])
                    l[u] = l[ptr->key];//l[u] maintains a record of ancestral backedge
                if(l[ptr->key] >= d[u])
                    art[u] = 1;
            }
        }
        else if(visited[ptr->key] == 1 && p[u] != ptr->key)//back edge
        {
            if(l[u] > d[ptr->key])
                l[u] = d[ptr->key];
        }
        
        ptr = ptr->next;
    }
    
    t++;
}

void DFS_Visit_Bridge(struct AdjListNode * Adj[], int V, int E, int u)
{
    visited[u] = 1;
    t++;
    d[u] = t;
    l_bridge[u] = t;
    
    struct AdjListNode *ptr = Adj[u];
    
    ptr = Adj[u];
    while(ptr != NULL)
    {
        if(visited[ptr->key] == 0)
        {
            p[ptr->key] = u;

            DFS_Visit_Bridge(Adj, V, E, ptr->key);
            
            if(l_bridge[ptr->key] < l_bridge[u])
                l_bridge[u] = l_bridge[ptr->key];//l[u] maintains a record of ancestral backedge
            
            if(l_bridge[ptr->key] > d[u])
            {
                // cout << "YO" << u << " " << ptr->key << "YO" << endl;
                if(ptr->key < u)
                {
                    struct AdjListNode* pt = bridge[ptr->key];
                    struct AdjListNode* node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
                    node->key = u;
                    // node->next = NULL;
                    
                    if(pt == NULL)
                    {
                        node->next = bridge[ptr->key];
                        bridge[ptr->key] = node;
                    }
                    else if(pt->key > u)
                    {
                        node->next = bridge[ptr->key];
                        bridge[ptr->key] = node;
                    }
                    else if(pt != NULL)
                    {
                        while(pt->next != NULL && pt->next->key <= u)
                            pt = pt->next;
                        
                        node->next = pt->next;
                        pt->next = node;
                    }
                }
                else 
                {
                    struct AdjListNode* pt = bridge[u];
                    struct AdjListNode* node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
                    node->key = ptr->key;
                    // node->next = NULL;
                    
                    if(pt == NULL)
                    {
                        node->next = bridge[u];
                        bridge[u] = node;
                    }
                    else if(pt->key > ptr->key)
                    {
                        node->next = bridge[u];
                        bridge[u] = node;
                    }
                    else if(pt != NULL)
                    {
                        while(pt->next != NULL && pt->next->key <= ptr->key)
                            pt = pt->next;
                        
                        node->next = pt->next;
                        pt->next = node;
                    }
                }
            }
        }
        else if(visited[ptr->key] == 1 && p[u] != ptr->key)//back edge
        {
            if(l_bridge[u] > d[ptr->key])
                l_bridge[u] = d[ptr->key];
        }
        
        ptr = ptr->next;
    }
    
    t++;
}

void DFS(struct AdjListNode* Adj[], int V, int E, int u, int bridge)
{
    if(!bridge)
    {
        for(int i = 0;i<V;i++)
        {
            visited[i] = 0;
            p[i] = -10;
            art[i] = 0;
        }
        
        DFS_Visit(Adj, V, E, u);
    }
    else if(bridge)
    {
        for(int i = 0;i<V;i++)
        {
            visited[i] = 0;
            p[i] = -10;
        }
        
        t = 0;
        DFS_Visit_Bridge(Adj, V, E, u);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    
    struct AdjListNode* Adj[V];
    
    for(int m = 0;m<V;m++)
    {
        Adj[m] = NULL;
        bridge[m] = NULL;
    }
    
    //input all edges into adjacency list
    for(int m = 0;m<E;m++)
    {
        int p, q;
        cin >> p >> q;
        
        struct AdjListNode* ptr = Adj[p];
        struct AdjListNode* node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
        node->key = q;
        // node->next = NULL;
        
        if(ptr == NULL)
        {
            node->next = Adj[p];
            Adj[p] = node;
        }
        else if(ptr->key > q)
        {
            node->next = Adj[p];
            Adj[p] = node;
        }
        else if(ptr != NULL)
        {
            while(ptr->next != NULL && ptr->next->key <= q)
                ptr = ptr->next;
            
            node->next = ptr->next;
            ptr->next = node;
        }
        
        ptr = Adj[q];
        struct AdjListNode* node2 = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
        node2->key = p;
        // node2->next = NULL;
        
        if(ptr == NULL)
        {
            node2->next = Adj[q];
            Adj[q] = node2;
        }
        else if(ptr->key > p)
        {
            node2->next = Adj[q];
            Adj[q] = node2;
        }
        else if(ptr != NULL)
        {
            while(ptr->next != NULL && ptr->next->key <= p)
                ptr = ptr->next;
            
            node2->next = ptr->next;
            ptr->next = node2;
        }
        
    }
    
    DFS(Adj, V, E, 0, 0);
    
    // struct AdjListNode *pp = Adj[2];
    // while(pp != NULL)
    // {
    //     cout << pp->key;
    //     pp = pp->next;
    // }
    
    int found = 0;
    for(int i = 0;i<V;i++)
    {
        if(art[i] == 1)
        {
            found = 1;
            cout << i << " ";
        }
    }
    if(found == 0)  cout << "EMPTY";
    cout << endl;
    
    DFS(Adj, V, E, 0, 1);
    
    for(int i = 0;i<V;i++)
    {
        struct AdjListNode *ppp = bridge[i];
        while(ppp != NULL)
        {
            if(i < ppp->key)
                cout << i << " " << ppp->key << endl;
            ppp = ppp->next;
        }
    }
    
    // for(int i = 0;i<V;i++)
    //     cout << endl << l_bridge[i] << " ";
    
    // int degree[V] = {};
    // for(int i = 0;i<V;i++)
    // {
    //     struct AdjListNode *ptr = Adj[i];
    //     while(ptr != NULL)
    //     {
    //         degree[i]++;
    //         ptr = ptr->next;
    //     }
    // }
}