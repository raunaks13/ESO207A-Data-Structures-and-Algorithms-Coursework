#include <iostream>

using namespace std;

class Stack
{
    public:
        struct node
        {
            struct node *next;
            long long int key;
        };
        
        struct node* head = NULL;
        
        void push(long long int val)
        {
            struct node *newnode = (struct node*) malloc(sizeof(struct node));
            newnode->key = val;
            
            if(head == NULL)
            {
                head = newnode;
                head->next = NULL;
                return;
            }
            
            newnode->next = head;
            head = newnode;
        }
        
        long long int pop()
        {
            if(head != NULL)
            {
                long long int value = head->key;
                head = head->next;
                return value;
            }
        }
        
        int isempty()
        {
            if(head == NULL)
                return 1;
            else return 0;
        }
        
        long long int top()
        {
            if(head != NULL)
                return head->key;
            else return -1;
        }
};

int main()
{
    std::ios::sync_with_stdio(false);
    
    int t;
    cin >> t;
    Stack S;

    for(int k = 0; k < t;k++)
    {
        int m;
        cin >> m;
        
        long long int arr[m];
        long long int left[m];
        long long int final[m];

        for(int i = 0;i<m;i++)
            cin >> arr[i];
        
        long long int min = 21474836480;

        //store minimum values from right side
        for(int i = m-1;i>=0;i--)
        {
            if(arr[i] < min)
            {
                min = arr[i];
                left[i] = min;
            }
            else
                left[i] = min;
        }
        
        
        int fin_index = 0, left_min = left[0];
        for(int j = 0;j<m;j++)
        {
            S.push(arr[j]);

            left_min = left[j];
            if(left_min == S.top())
            {
                while(!S.isempty() && left_min == S.top())
                {
                    final[fin_index++] = S.pop();
                    if(j+1 < m && !S.isempty() && S.top() < left[j+1])
                        left_min = S.top();
                }
            }
        }
        
        while(!S.isempty())
            final[fin_index++] = S.pop();
        
        for(int i = 0;i<m;i++)
            cout << "v" << final[i];
        cout << endl;
    }
    
    return 0;
}