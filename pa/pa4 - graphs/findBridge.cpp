#include <iostream>

using namespace std;

struct AdjListNode
{
    int key;
    struct AdjListNode* next;
};

int visited[10000000];
int cycle_exists = 0;

void DFS_Visit(struct AdjListNode * Adj[], int V, int E, int u, int v)
{
    visited[u] = 1;
    struct AdjListNode *ptr = Adj[u];
    while(ptr != NULL)
    {
        if(ptr->key == v)
            cycle_exists = 1;
        if(visited[ptr->key] == 0)
            DFS_Visit(Adj, V, E, ptr->key, v);
        
        ptr = ptr->next;
    }
}

void DFS(struct AdjListNode* Adj[], int V, int E, int u, int v)
{
    for(int i = 1;i<=V;i++)
        visited[i] = 0;
    
    DFS_Visit(Adj, V, E, u, v);
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    for(int k = 0;k<T;k++)
    {
        cycle_exists = 0;
        
        int V, E;
        cin >> V >> E;
        
        struct AdjListNode* Adj[V+1];
        
        for(int m = 1;m<=V;m++)
            Adj[m] = NULL;
        
        for(int m = 0;m<E;m++)
        {
            int p, q;
            cin >> p >> q;
            
            struct AdjListNode* node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
            node->key = q;
            node->next = Adj[p];
            Adj[p] = node;
            
            struct AdjListNode* node2 = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
            node2->key = p;
            node2->next = Adj[q];
            Adj[q] = node2;
        }
        
        int u, v;
        cin >> u >> v;
        
        if(Adj[u] != NULL && Adj[u]->key == v)
            Adj[u] = Adj[u]->next;
        
        struct AdjListNode* ptr = Adj[u];
        while(ptr != NULL && ptr->next != NULL)
        {
            if(ptr->next->key == v)
            {
                ptr->next = ptr->next->next;
                break;
            }
            ptr = ptr->next;
        }
        
        if(Adj[v] != NULL && Adj[v]->key == u)
            Adj[v] = Adj[v]->next;
        
        ptr = Adj[v];
        while(ptr != NULL && ptr->next != NULL)
        {
            if(ptr->next->key == u)
            {
                ptr->next = ptr->next->next;
                break;
            }
            ptr = ptr->next;
        }
        
        DFS(Adj, V, E, u, v);
        
        if(cycle_exists == 1)
            cout << "Not Bridge" << endl;
        else if(cycle_exists == 0)
            cout << "Bridge" << endl;
        
        // ptr = Adj[9];
        // while(ptr != NULL)
        // {
        //     cout << ptr->key << " ";
        //     ptr = ptr->next;
        // }
    }
}
