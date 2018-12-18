#include <stdio.h>

long long int inv = 0;

void invmerge(int a[], int lo, int mid, int hi)
{
    int l[mid - lo + 3];
    int r[hi - mid + 2];
    
    for(int k = lo ; k <= mid ; k++)
        l[k - lo + 1] = a[k];
    
    for(int k = mid+1 ; k <= hi ; k++)
        r[k - mid] = a[k];
    
    l[mid-lo+2] = 1000000000;
    r[hi-mid+1] = 1000000000;
    
    int i = 1, j = 1;
    int i_inv = 1, j_inv = 1;
    for(int k = lo ; k <= hi ; k++)
    {
        if(l[i_inv] > 2*r[j_inv])
        {
            if(i_inv != mid - lo + 2)
                inv += mid - i_inv - lo + 2;
            
            // printf("%d %d %d\n", l[i_inv], r[j_inv], mid-i_inv-lo+2);
            // for(int m = lo ; m <= hi ; m++)
            //     printf("%d ", a[m]);
            // printf("\n");
            
            j_inv++;
        }
        else
            i_inv++;
        
        if(l[i] <= r[j])
            a[k] = l[i++];
        else if(l[i] > r[j])
            a[k] = r[j++];
    }
}

void mergesort(int a[], int lo, int hi)
{
    if(hi > lo)
    {
        int mid = (lo + hi)/2;
    
        mergesort(a, lo, mid);
        mergesort(a, mid+1, hi);
        invmerge(a, lo, mid, hi);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    
    for(int k = 0 ; k < t ; k++)
    {
        inv = 0;
        
        int n;
        scanf("%d", &n);
        
        int a[n+1];
        
        for(int i = 1 ; i <= n ; i++)
            scanf("%d", &a[i]);
        
        mergesort(a, 1, n);
        printf("%lld\n", inv);
    }
    
    return 0;
}