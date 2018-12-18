#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>

using namespace std;

#define PI acos(-1)

typedef std::pair<long double, long double> _pair;

_pair add_complex(_pair a1, _pair a2)   //To add complex numbers
{
    _pair out;
    
    out.first = a1.first + a2.first;
    out.second = a1.second + a2.second;
    
    return out;
}

_pair sub_complex(_pair a1, _pair a2)   //To subtract complex numbers
{
    _pair out;
    
    out.first = a1.first - a2.first;
    out.second = a1.second - a2.second;
    
    return out;
}

_pair mul_complex(_pair a1, _pair a2)   //To multiply complex numbers
{
    _pair out;
    
    out.first = (a1.first)*(a2.first) - (a1.second)*(a2.second);
    out.second = (a1.first)*(a2.second) + (a1.second)*(a2.first);
    
    return out;
}

//Returns an n element vector of outputs of A(w_n)
std::vector < _pair > DFT(std::vector < _pair > A, long long int n, long long int d, int inverse)
{
    std::vector < _pair > y(n);

    if(d == 1)//return same value A[0] for all inputs w if polynomial is constant
    {
        for(long long int i = 0 ; i < n ; i++)
            y[i] = A[0];
        
        return y;
    }
    else if(n == 1)//If recurrence on roots of unity finishes before that on degree of polynomial
    {
        _pair sum = std::make_pair(0.0, 0.0);
        
        for(long long int i = 0 ; i < d ; i++)
            sum = add_complex(sum, A[i]);
        
        y[0] = sum;
        
        return y;
    }
    
    long long int evensize;
    
    if(d%2 == 1)
        evensize = d/2 + 1;
    else if(d%2 == 0)
        evensize = d/2;
    
    std::vector < _pair > A_odd(d/2);
    std::vector < _pair > A_even(evensize);
    
    long long int k = 0;
    for(long long int i = 1; i < d ; i+=2, k++)//a1 + a3x + a5x^2 + ...
        A_odd[k] = A[i];

    k = 0;
    for(long long int i = 0, k = 0 ; i < d ; i+=2, k++)//a0 + a2x + a4x^2 + ...
        A_even[k] = A[i];
    
    std::vector < _pair > y_odd;
    std::vector < _pair > y_even;
    
    if(inverse == 0)
    {
        y_odd = DFT(A_odd, n/2, A_odd.size(), 0);
        y_even = DFT(A_even, n/2, A_even.size(), 0);
    }
    else if(inverse == 1)//Check if inverse DFT is to be done
    {
        y_odd = DFT(A_odd, n/2, A_odd.size(), 1);
        y_even = DFT(A_even, n/2, A_even.size(), 1);
    }

    
    _pair w(1.0, 0.0);
    _pair w_n;
    
    if(inverse == 0)
        w_n = std::make_pair(cos(2.0*PI/((long double) n)), 
                             sin(2.0*PI/((long double) n)));
    else if(inverse == 1)
        w_n = std::make_pair(cos(2.0*PI/((long double) n)), 
                             -sin(2.0*PI/((long double) n)));
    
    for(long long int i = 0 ; i < n/2 ; i++)//Combine results from A_even and A_odd using A(x) = A_even(x^2) + xA_odd(x^2)
    {
        y[i] = add_complex(y_even[i], mul_complex(w, y_odd[i]));
        y[i + n/2] = sub_complex(y_even[i], mul_complex(w, y_odd[i]));
        
        w = mul_complex(w, w_n);
    }
    
    return y;
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    int t;
    cin >> t;
    
    for(int k = 0 ; k < t ; k++)
    {
        int n;
        cin >> n;
        
        int size = n;
        n = 10*n+2;
        
        int var;        
        vector < _pair > A(n, make_pair(0.0, 0.0));
        vector < _pair > B(n, make_pair(0.0, 0.0));

        for(long long int i = 0 ; i < size ; i++)
        {
            cin >> var;
            A[var].first = 1;
            A[var].second = 0;
        }
        
        for(long long int i = 0 ; i < size ; i++)
        {
            cin >> var;
            B[var].first = 1;
            B[var].second = 0;
        }
    
        // for(long long int i = 0 ; i < n ; i++)
        // std::cout << (int) A[i].first << " ";

        int m = n;
        long long int C_size;
        
        if(log2(n+m-1) == floor(log2(n+m-1)))//Check if n is a power of 2
            C_size = n+m-1;
        else
            C_size = (long long int) pow(2, floor(log2(n+m-1)) + 1);
        
        vector < _pair > A_y(C_size);
        vector < _pair > B_y(C_size);
        vector < _pair > C_y(C_size);
        
        A_y = DFT(A, C_size, n, 0);
        B_y = DFT(B, C_size, m, 0);
    
        for(long long int i = 0 ; i < C_size ; i++)//Point-Value Multiplication
            C_y[i] = mul_complex(A_y[i], B_y[i]);
    
        vector <_pair > C_inv = DFT(C_y, C_size, C_size, 1);
        
        for(long long int i = 0 ; i < C_size ; i++)
        {
            C_inv[i].first = (C_inv[i].first)/C_size;
            
            //Tolerance of 10^-8 to avoid precision related issues (-0.00000)
            if(C_inv[i].first <= 0 && C_inv[i].first >= -pow(10, -8))
                C_inv[i].first = 0;
                
            C_inv[i].second = (C_inv[i].second)/C_size;
            
            if(C_inv[i].second <= 0 && C_inv[i].second >= -pow(10, -8))
                C_inv[i].second = 0;
        }
        
        int index = 0;
        for(long long int i = 0 ; i < n+m-1 ; i++)
        {
            if(C_inv[i].first > pow(10, -8))
                index++;
        }
        cout << index << endl;
        
        for(long long int i = 0 ; i < n+m-1 ; i++)
        {
            if(C_inv[i].first > pow(10, -8))
                cout << i << " " << (C_inv[i].first) << endl;
        }
    }

    return 0;
}