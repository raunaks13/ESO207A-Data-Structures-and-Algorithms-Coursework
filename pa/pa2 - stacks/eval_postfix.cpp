#include <iostream>

using namespace std;

class Stack
{
    public:
        struct node
        {
            struct node *next;
            long double key;
        };
        
        struct node* head = NULL;
        
        void push(long double val)
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
        
        long double pop()
        {
            if(head != NULL)
            {
                long double value = head->key;
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
        
        long double top()
        {
            if(head != NULL)
                return head->key;
            else return -1;
        }
};

long long int my_round(long double a)
{
    if(a > 0)
        return (long long int) (a+0.5);
    else if(a < 0)
        return (long long int) (a - 0.5);
    else if(a == 0)
        return 0;
}

long long int power(long long int a, long long int b)
{
    long long int res = 1;
    for(int i = 0;i < b;i++)
        res = res*a;
    
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    long long int t;
    cin >> t;
    cin.ignore(2, '\n');
    
    Stack S;
    
    for(long long int k = 1 ; k <= t ; k++)
    {
        string str;
        getline(cin, str);
        
        for(int q = 0;q< static_cast <int> (str.length());q++)
        {
            if(str[q] == ' ')
                continue;
            
            char arr[1000];
            int p = 0;
            int lenn = 0;

            while(q < static_cast <int> (str.length()) && str[q] != ' ')
            {
                arr[p++] = str[q++];
                lenn++;
            }
            
            char arr2[lenn+1];
            for(int k = 0;k<lenn;k++)
                arr2[k] = arr[k];
            arr2[lenn] = '\0';
            
            string next(arr2);
            
            if(next == "~")
            {
                long double a = S.pop();
                S.push(-1*a);
            }
            else if(next == "+" || next == "-" || next == "*" || next == "/" || next == "%" || next == "^")
            {
                long double a = S.pop();
                long double b = S.pop();
                
                if(next == "+")
                    S.push(b+a);
                else if(next == "-")
                    S.push(b-a);
                else if(next == "*")
                    S.push(b*a);
                else if(next == "/")
                    S.push(b/a);
                else if(next == "%")
                    S.push(((long long int) b)%((long long int) a));
                else if(next == "^")
                    S.push(power((long long int) b, (long long int) a));
            }
            else
            {
                S.push((long double) stoi(next));
            }
        }
        
        cout << my_round(S.top()) << endl;
    }
    
    return 0;
}