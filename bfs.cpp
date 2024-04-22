// commands to execute code
//> gcc -o bfs -fopenmp bfs.cpp -lstdc++
//> ./bfs

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

vector<bool> visited;
vector<vector<int>> graph;

void edge(int a,int b)
{
    graph[a].pb(b);
}
void bfs(int start)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    #pragma omp parallel
    {
        #pragma omp single
        {
            while (!q.empty())
            {
                int vertex = q.front();
                q.pop();
                cout<<vertex<<" ";

                #pragma omp task firstprivate(vertex)
                {
                    for (auto i=graph[vertex].begin();i!=graph[vertex].end();i++)
                    {
                        if (!visited[*i])
                        {
                            q.push(*i);
                            visited[*i] = true;
                            
                        }
                    }
                }
            }

        }
   }
  
}

int main()
{
    visited.assign(8,false);
    graph.assign(8,vector<int>());
    
    int a,b;
    cout<<"Enter vertex:"<<endl;
    for (int i = 0; i < 8; i++)
    {
        cin >> a >> b;
        edge(a, b);
    }
   double st=omp_get_wtime();
    for (int i = 0; i < 8; i++)
    {
        if (!visited[i])
         bfs(i);
    }
    double et=omp_get_wtime();
    cout <<"parallel bfs time:"<<et-st <<endl;

 
  return 0;
}

