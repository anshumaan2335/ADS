#include<bits/stdc++.h>
using namespace std;

class DisjointUnionSets
{

public:
    vector<int> rank, parent;
    int n;

    DisjointUnionSets(int n);
    void makeSet();
    int find(int x);
    void Union(int x, int y);
};

DisjointUnionSets::DisjointUnionSets(int n)
{
    rank.resize(n);
    parent.resize(n);
    this->n = n;
    makeSet();
}

void DisjointUnionSets::makeSet()
{
    for(int i=0; i<n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int DisjointUnionSets:: find(int x)
{
    if(parent[x] == x)
        return x;
    else
        return find(parent[x]);
}

void DisjointUnionSets::Union(int x, int y)
{
    int xRoot = find(x);
    int yRoot = find(y);

    if(xRoot == yRoot)
        return;

    if( rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else if (rank[yRoot] > rank[xRoot])
        parent[xRoot] = yRoot;
    else
    {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
    
}

int countIslands(vector<vector<int>>a)
{
    int n = a.size();
    int m = a[0].size();

    DisjointUnionSets *obj = new DisjointUnionSets(n*m);

    for(int j=0; j<n; j++)
    {
        for(int k=0; k<n; k++)
        {
            if(a[j][k] == 0)
                continue;

            if(j+1 < n && a[j+1][k] == 1)
                obj->Union(j*m + k, (j+1)*m + k);
                
            if(j-1 >= 0 && a[j-1][k] == 1)
                obj->Union(j*m + k, (j-1)*m + k);
                
            if(k+1 < m && a[j][k+1] == 1)
                obj->Union(j*m + k, j*m + k+1);
                
            if(k-1 >= 0 && a[j][k-1] == 1)
                obj->Union(j*m + k, j*m + k-1);
                
            if(j-1 >= 0 && k+1 < m && a[j-1][k+1] == 1)
                obj->Union(j*m + k, (j-1)*m + k+1);
                
            if(j+1 < n  && k+1 < m && a[j+1][k+1] == 1)
                obj->Union(j*m + k, (j+1)*m + k+1);
                
            if(j-1 >= 0 && k-1 >= 0 && a[j-1][k-1] == 1)
                obj->Union(j*m + k, (j-1)*m + k-1);
                
            if(j+1 < n  && k-1 >= 0 && a[j+1][k-1] == 1)
                obj->Union(j*m + k, (j+1)*m + k-1);
        }
    }

    int numberOfIslands = 0;
    int *c = new int[n*m];

    for(int i=0; i<n*m; i++)
    {
        c[i] = 0;
    }

    for(int j=0; j<n; j++)
    {
        for(int k=0; k<m; k++)
        {
            if(a[j][k] == 1)
            {
                int x = obj->find(j*m + k);

                if(c[x] == 0)
                {
                    c[x]++;
                    numberOfIslands++;
                }
                else
                    c[x]++;
            }
        }
    }
    return numberOfIslands;
}

int main()
{
    
    vector<vector<int>>a ={{1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1},
            {1, 0, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1}};
            
    cout<<"Number of islands = "<<countIslands(a)<<endl;
    return 0;
}
