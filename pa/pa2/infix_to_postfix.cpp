#include <iostream>

using namespace std;

#define ADD_VAL 1
#define SUB_VAL 2
#define MUL_VAL 3
#define DIV_VAL 4
#define MOD_VAL 5
#define POW_VAL 6
#define LEFT_VAL 10
#define RIGHT_VAL 11

struct Token
{
    string tktype;
    int tkval;
};

class Stack
{
    public:
        struct node
        {
            struct node *next;
            char key;
        };
        
        struct node* head = NULL;
        
        void push(char val)
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
        
        char pop()
        {
            if(head != NULL)
            {
                char value = head->key;
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
        
        char top()
        {
            if(head != NULL)
                return head->key;
            else return 'X';
        }
};

struct Token get_next_token(string next)
{
    struct Token token;
    
    if(next == "+" || next == "-" || next == "*" || next == "/" || next == "%" || next == "^")
    {
        token.tktype = "operator";
        
        if(next == "+")
            token.tkval = ADD_VAL;
        else if(next == "-")
            token.tkval = SUB_VAL;
        else if(next == "*")
            token.tkval = MUL_VAL;
        else if(next == "/")
            token.tkval = DIV_VAL;
        else if(next == "%")
            token.tkval = MOD_VAL;
        else if(next == "^")
            token.tkval = POW_VAL;
    }
    else if(next == "(" || next == ")")
    {
        token.tktype = "parentheses";
        
        if(next == "(")
            token.tkval = LEFT_VAL;
        else if(next == ")")
            token.tkval = RIGHT_VAL;
    }
    else
    {
        token.tktype = "operand";
        for(int i = 0;i < static_cast <int> (next.length()) ; i++)
        {
            if(next[i] > '9' || next[i] < '0')
            {
                token.tkval = -1;
                return token;
            }
        }
        token.tkval = stoi(next);
    }
    
    return token;
}

int isValid(string str)
{
    struct Token a[str.length()];
    int len = 0;
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
        struct Token token = get_next_token(next);
        a[len] = token;
        len++;
    }
    
    int left_paren = 0;
    int right_paren = 0;
    
    int operators = 0;
    int operands = 0;
    
    for(int j = 0;j<len;j++)
    {
        if(a[j].tktype == "operand" && a[j].tkval == -1)
            return 0;
        
        if(a[j].tktype == "operand")
            operands++;
        
        if(a[j].tktype == "operator")
            operators++;
        
        if(a[j].tktype == "parentheses")
        {
            if(a[j].tkval == LEFT_VAL) left_paren++;
            else if(a[j].tkval == RIGHT_VAL) right_paren++;
        }
        
        if(right_paren > left_paren)
            return 0;
        
        if(j>0)
        {
            if(a[j].tktype == "operator" && 
            (a[j-1].tktype == "operator" || (a[j-1].tktype == "parentheses" && 
            a[j-1].tkval == LEFT_VAL)))// ( +
                return 0;
            
            if((a[j].tktype == "parentheses" && a[j].tkval == RIGHT_VAL) && 
            a[j-1].tktype == "operator")// + )
                return 0;
            
            if(a[j].tktype == "operand" && a[j-1].tktype == "operand")// 2 3
                return 0;
            
            if((a[j].tktype == "parentheses" && a[j].tkval == LEFT_VAL) && 
            (a[j-1].tktype == "parentheses" && a[j-1].tkval == RIGHT_VAL))// )(
                return 0;
            
            if((a[j-1].tktype == "parentheses" && a[j-1].tkval == LEFT_VAL) && 
            (a[j].tktype == "parentheses" && a[j].tkval == RIGHT_VAL))// ()
                return 0;
            
            if(a[j].tktype == "parentheses" && a[j-1].tktype == "operand" && 
            a[j].tkval == LEFT_VAL)// 2 (
                return 0;
            
            if(a[j].tktype == "operand" && a[j-1].tktype == "parentheses" && 
            a[j-1].tkval == RIGHT_VAL)// ) 2 
                return 0;
        }
    }
    
    if(operators >= operands)
        return 0;
        
    if(a[len-1].tktype == "operator" || a[0].tktype == "operator")
        return 0;

    if(left_paren != right_paren)
        return 0;
    
    return 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    int t;
    cin >> t;
    cin.ignore(2, '\n');
    
    int prec[7];
    prec[ADD_VAL] = 1;
    prec[SUB_VAL] = 1;
    prec[MUL_VAL] = 2;
    prec[DIV_VAL] = 3;
    prec[MOD_VAL] = 3;
    prec[POW_VAL] = 4;

    char assoc[7];
    assoc[ADD_VAL] = 'l';
    assoc[SUB_VAL] = 'l';
    assoc[MUL_VAL] = 'l';
    assoc[DIV_VAL] = 'l';
    assoc[MOD_VAL] = 'l';
    assoc[POW_VAL] = 'r';
    
    Stack S;
    
    for(int k = 1 ; k <= t ; k++)
    {
        string str;
        getline(cin, str);

        if(!isValid(str))
        {
            cout << "INVALID" << endl;
            continue;
        }
        
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
            
            struct Token token = get_next_token(next);
            
            if(token.tktype == "operand")
                cout << token.tkval << " ";
            else if(token.tktype == "operator")
            {
                char op = next[0];
                string top(1, S.top());
                
                if(S.isempty() || S.top() == '(')
                {
                    S.push(op);
                    continue;
                }
                else if(prec[get_next_token(top).tkval] > prec[token.tkval])
                {
                    while(prec[get_next_token(top).tkval] >= prec[token.tkval])
                    {
                        if(prec[get_next_token(top).tkval] == prec[token.tkval])
                        {
                            if(assoc[token.tkval] == 'l')
                            {
                                cout << S.pop() << " ";
                                break;
                            }
                            else if(assoc[token.tkval] == 'r')
                                break;
                        }
                        else
                        {
                            cout << S.pop() << " ";
                            if(!S.isempty())
                                top[0] = S.top();
                            else
                                break;
                        }
                    }
                    S.push(op);
                }
                else if(prec[get_next_token(top).tkval] == prec[token.tkval])
                {
                    if(assoc[token.tkval] == 'l')
                    {
                        cout << S.pop() << " ";
                        S.push(op);
                    }
                    else if(assoc[token.tkval] == 'r')
                        S.push(op);
                }
                else if(prec[get_next_token(top).tkval] < prec[token.tkval])
                    S.push(op);
            }
            else if(next == "(")
                S.push('(');
            else if(next == ")")
            {
                while(1)
                {
                    char val = S.pop();
                    if(val == '(' || val == 'X')
                        break;
                    else cout << val << " ";
                }
            }
        }
        
        while(!S.isempty())
            cout << S.pop() << " ";
        
        cout << endl;
    }
    
    return 0;
}