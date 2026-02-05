#include<iostream>
#include<iomanip>
#include<queue>
#include<limits>
#include<set>
using namespace std;

class Graph{
    int n;
    int **adjmat;

    public:
    Graph(){
        cout<<"Enter no. of vertices: ";
        cin>>n;

        adjmat = new int*[n];
        
        for(int i=0; i<n; i++){
            adjmat[i] = new int[n];
        }
    }

    void createGraph(){
        cout<<"\nEnter edges cost\n";
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(i==j){
                    adjmat[i][j] = 0;
                }else{
                    cout<<"Enter cost of edge from node "<< i << " to " << j <<": ";
                    cin>>adjmat[i][j]; 
                }
            }
        }
    }


    void displayGraph(){
        cout<<"\n   ";
        for(int i=0; i<n; i++){
            cout<<right<<setw(7)<<"O"<<i+1;
        }

        cout<<"\n   ";
        for(int i=0; i<n; i++){
            cout<<"--------";
        }

        for(int i=0; i<n; i++){
            cout<<endl;
            cout<<"O"<<i+1;
            for(int j=0; j<n; j++){
                cout<<right<<" | "<<setw(5)<<adjmat[i][j];
            }
            cout<<" |";
        }

        cout<<"\n   ";
        for(int i=0; i<n; i++){
            cout<<"--------";
        }
    }

    void dijkstrasAlgo(){
        cout<<"\nEnter source node: ";
        int source;
        cin>>source;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(n, INT_MAX);

        dist[source] = 0;

        pq.push({0, source});
        while(!pq.empty()){
            pair<int, int> p;
            p = pq.top(); pq.pop();

            int d = p.first;
            int u = p.second;

            if(d > dist[u]){
                continue;
            }

            for(int i=0; i<n; i++){
                if(adjmat[u][i] != 0){
                    int v = i;
                    int w = adjmat[u][i];

                    if(dist[u] + w < dist[v]){
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        for(int i=0; i<n; i++){
            cout<<dist[i]<<" ";
        }
    }

};

int main(){
    Graph g;
    g.createGraph();
    g.displayGraph();
    g.dijkstrasAlgo();
    return 0;
}