#include <iostream>

using namespace std;

struct state
{
    int key1, key2, key3;
};

class Queue
{
    public:
        struct node
        {
            struct node *next;
            struct state s;
        };
        
        //head->...->...->tail
        struct node* head = NULL;//pointer to remove nodes
        struct node* tail = NULL;//pointer to add nodes
        
        void enqueue(int a, int b, int c)
        {
            struct node *newnode = (struct node*) malloc(sizeof(struct node));
            (newnode->s).key1 = a;
            (newnode->s).key2 = b;
            (newnode->s).key3 = c;
            
            if(tail == NULL)
            {
                head = newnode;
                head->next = NULL;
            }
            else
                tail->next = newnode;
            
            newnode->next = NULL;
            tail = newnode;
        }
        
        struct state dequeue()
        {
            if(head != NULL)
            {
                if(head->next == NULL)
                    tail = NULL;
                struct state s = head->s;
                head = head->next;
                return s;
            }
        }
        
        int isempty()
        {
            if(head == NULL && tail == NULL)
                return 1;
            else return 0;
        }
};

int main()
{
    std::ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    for(int k = 0;k<T;k++)
    {
        int A, B, C, p, q, r;
        cin >> A >> B >> C >> p >> q >> r;
        
        int N;
        cin >> N;
        
        for(int m = 0;m<N;m++)
        {
            int visited[A+1][B+1][C+1] = {};
            int steps[A+1][B+1][C+1] = {};
            int a_f, b_f, c_f;
            cin >> a_f >> b_f >> c_f;
            
            visited[p][q][r] = 1;
            steps[p][q][r] = 1;
            Queue Q;
            
            Q.enqueue(p, q, r);
            int found = 0;
            // cout << p << " " << q << " " << r << " ";

            while(!Q.isempty())
            {
                struct state u = Q.dequeue();
                int a = u.key1;
                int b = u.key2;
                int c = u.key3;
                // cout << a << " " << b << " " << c << " " << steps[a][b][c] << endl;

                int a_n, b_n, c_n;
                
                if(visited[0][b][c] == 0)
                {
                    visited[0][b][c] = 1;
                    steps[0][b][c] = steps[a][b][c] + 1;
                    Q.enqueue(0, b, c);
                }
                
                if(0 == a_f && b == b_f && c == c_f)
                {
                    cout << steps[0][b][c] << endl;
                    found = 1;
                    break;
                }
                
                if(visited[a][0][c] == 0)
                {
                    visited[a][0][c] = 1;
                    steps[a][0][c] = steps[a][b][c] + 1;
                    Q.enqueue(a, 0, c);
                }
                
                if(a == a_f && 0 == b_f && c == c_f)
                {
                    cout << steps[a][0][c] << endl;
                    found = 1;
                    break;
                }
                
                if(visited[a][b][0] == 0)
                {
                    visited[a][b][0] = 1;
                    steps[a][b][0] = steps[a][b][c] + 1;
                    Q.enqueue(a, b, 0);
                }
                
                if(a == a_f && b == b_f && 0 == c_f)
                {
                    cout << steps[a][b][0] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from A to B
                if(a <= B-b) {
                    a_n = 0; b_n = a+b; c_n = c;
                }
                else {
                    a_n = a+b-B; b_n = B; c_n = c;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from A to C
                if(a <= C-c) {
                    a_n = 0; b_n = b; c_n = a+c;
                }
                else {
                    a_n = a+c-C; b_n = b; c_n = C;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from B to A
                if(b <= A-a) {
                    a_n = a+b; b_n = 0; c_n = c;
                }
                else {
                    a_n = A; b_n = a+b-A; c_n = c;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from B to C
                if(b <= C-c) {
                    a_n = a; b_n = 0; c_n = b+c;
                }
                else {
                    a_n = a; b_n = b+c-C; c_n = C;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from C to A
                if(c <= A-a) {
                    a_n = a+c; b_n = b; c_n = 0;
                }
                else {
                    a_n = A; b_n = b; c_n = a+c-A;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
                
                //Pour from C to B
                if(c <= B-b) {
                    a_n = a; b_n = b+c; c_n = 0;
                }
                else {
                    a_n = a; b_n = B; c_n = b+c-B;
                }
                
                if(visited[a_n][b_n][c_n] == 0)
                {
                    visited[a_n][b_n][c_n] = 1;
                    steps[a_n][b_n][c_n] = steps[a][b][c] + 1;
                    Q.enqueue(a_n, b_n, c_n);
                }
                
                if(a_n == a_f && b_n == b_f && c_n == c_f)
                {
                    cout << steps[a_n][b_n][c_n] << endl;
                    found = 1;
                    break;
                }
            }
            
            if(found == 0)
                cout << "IMPOSSIBLE" << endl;
        }
    }
}