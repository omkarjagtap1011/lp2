#include<iostream>
#include<iomanip>
#include<queue>
#include<tuple>
#include<vector>
using namespace std;

class Graph {
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
                    cout<<"Enter cost of edge from node "<< i + 1 << " to " << j + 1 <<": ";
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

    void primsAlgo(){
        // (weight, current node, parent)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        vector<bool> visited(n, false);

        // enqueue the initial node
        // (0, 0, -1)
        tuple<int, int, int> tp;
        get<0>(tp) = adjmat[0][0];
        get<1>(tp) = 0;
        get<2>(tp) = -1;
        pq.push(tp);

        // Weight of mst
        int sum = 0;

        // to store order of edges
        vector<tuple<int, int, int>> result;

        // temporary tuple
        tuple<int, int, int> temp;

        while(!pq.empty()){
            // pop the top edge of pq
            tp = pq.top();
            pq.pop();

            int wt = get<0>(tp);
            int curNode = get<1>(tp);
            int parent = get<2>(tp);

            // if node is already visited then continue else Mark it visited
            if (visited[curNode]) continue;
            visited[curNode] = true;

            // Push the edge in result (excluding initial edge)
            if(parent!=-1) result.push_back(tp);

            // Update the sum
            sum += wt;


            for(int i=0; i<n; i++){
                if(adjmat[curNode][i] && !visited[i]){
                    get<0>(temp) = adjmat[curNode][i];
                    get<1>(temp) = i;
                    get<2>(temp) = curNode;

                    pq.push(temp);
                }
            }
        }
        
        cout<<"\nWeight of minimum Spanning tree: "<<sum<<endl;
        cout<<"Order of edges:"<< endl;

        for(auto e: result){
            cout<<"("<<get<1>(e) + 1 <<", "<<get<2>(e) + 1 <<")";
        }
    }
};

int main(){
    Graph obj;
    obj.createGraph();
    obj.displayGraph();
    obj.primsAlgo();
    return 0;
}