#include <iostream>
#include <stack>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);

    stack <int> s;

    int n = 8;
    int P[n] = {0, 50,45,35,40,60,50,55};
    // int P[n] = {0, 50};

    int A[n];

    for(int i = 1;i<=n;i++)
    {
        while(!s.empty() && P[s.top()] <= P[i])
            s.pop();//O(1)
        
        if(s.empty())//O(1)
            A[i] = i;
        else
            A[i] = i - s.top();//O(1)

        s.push(i);//O(1)
    }

    for(int i = 1;i<=n;i++)
        cout << A[i] << " ";
    
    return 0;
}