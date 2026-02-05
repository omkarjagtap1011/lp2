/*

rank = [0, 0, 0, 0, 0, 0]

parent = [1, 2, 3, 4, 5, 6]

edges:-
(weight, node1, node2)
(2, 4, 5)
(2, 4, 6)
(3, 3, 4)
(3, 2, 3)
(4, 3, 5)
(5, 5, 6)
(6, 2, 5)
(7, 1, 2)
(8, 1, 3)

Result = [(4, 5), (4, 6), (3, 4), (2, 3), (1, 2)]

1) Edge: (4, 5)

find(4){
    parent[4] == 4 is true hence return i i.e 4
}

similarly for find(5)


ultimate parent of 4 = pu4 = 4
ultimate parent of 5 = pu5 = 5

hence 4 and 5 belong to different group

rank(pu4) is 0
rank(pu5) is 0

rank is same, therefore put 
parent[pu5] = pu4
rank[pu4]++

add edge to result

rank = [0, 0, 0, 1, 0, 0]
parent = [1, 2, 3, 4, 4, 6]

2) Edge (4, 6)

find(4){
    parent[4] == 4
    therefore return 4
}

find(6) also returns 6

pu4 = 4
pu6 = 6

hence both nodes belong to different nodes

rank(pu4) is 1

rank(pu6) is 0

therfore parent[pu6] = pu4

rank = [0, 0, 0, 1, 0, 0]

parent = [1, 2, 3, 4, 4, 4]

Add edge to result6)

3) Edge (3, 4)

find(3) -> 3
find(4) -> 4

pu3 = 3
pu4 = 4

both belong to different groups

rank(pu3)-> 0
rank(pu4)-> 1


rank of pu4 > rank of pu3, therefore
parent[pu3] = pu4;

rank = [0, 0, 0, 1, 0, 0]
parent = [1, 2, 4, 4, 4, 4]

add edge to result

4) Edge (2, 3)

find(2) -> 2

find(3){
    parent[3] == 3 is false because parent[3] is 4

    therefore parent[3] = find(parent[3])
                        = find(4)
                        = 4
    
    return 4;
} -> 4

both belong to different groups

rank[2]->0
rank[4]->1

therefore
parent[2] = 4

rank = [0, 0, 0, 1, 0, 1]
parent = [1, 4, 4, 4, 4, 4]

add edge to result

5) Edge (3, 5)

find(3)-> 4
find(5)->4

both belong to same group, hence skip this node because cycle will form

6) Edge (5, 6)-> same group

7) Edge (2, 5)-> same group

8) Edge (1, 2) will be added to result
*/

#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

class DisjointSet{
    vector<int> parent;
    vector<int> rank;
    int V;

    public:
    DisjointSet(int v){
        V = v;
        rank.resize(V+1, 0);
        parent.resize(V+1);

        for(int i=0; i<V+1; i++){
            parent[i] = i;
        }
    }

    // Finds the ultimate parent
    int find(int i){
        return (parent[i] == i)? i: (parent[i] = find(parent[i]));
    }

    void unite(int n1, int n2){
        int pu1 = find(n1);
        int pu2 = find(n2);

        if(pu1 != pu2){
            if(rank[pu1] > rank[pu2]) parent[pu2] = pu1;
            else if(rank[pu1] < rank[pu2]) parent[pu1] = pu2;
            else{
                parent[pu2] = pu1;
                rank[pu1]++;
            }
        }
    }

};

bool cmp(tuple<int, int, int>& a, tuple<int, int, int>& b){
    return get<0>(a)<get<0>(b);
};

int main(){
    int V;
    cout<<"Enter no. of vertices: ";
    cin>>V;

    DisjointSet ds(V);

    vector<tuple<int, int, int>> edges;
    tuple<int, int, int> tp;

    int sum = 0;

    vector<tuple<int, int, int>> result;
    int E;
    cout<<"Enter no. of edges: ";
    cin>>E;

    cout<<"Enter edges in (weight, N1, N2) format"<<endl;
    for(int i=0; i<E; i++){
        cout<<"Enter edge 1:"<<endl;

        cout<<"Enter weight: ";
        cin>>get<0>(tp);

        cout<<"Enter Node1: ";
        cin>>get<1>(tp);

        cout<<"Enter Node2: ";
        cin>>get<2>(tp);

        edges.push_back(tp);
    }



    // Sort edges by weight
    sort(edges.begin(), edges.end(), cmp);

    for(auto edge: edges){
        int weight = get<0>(edge);
        int n1 = get<1>(edge);
        int n2 = get<2>(edge);

        if(ds.find(n1) != ds.find(n2)){
            ds.unite(n1, n2);
            sum+=weight;
            result.push_back(edge);

            if(result.size() == (V-1)) break;
        }
    }

    cout<<"\nWeight of MST: "<<sum<<endl;

    for(auto edge: result){
        cout<<"(" << get<1>(edge)<<", "<<get<2>(edge)<<")"<<endl;
    }
}