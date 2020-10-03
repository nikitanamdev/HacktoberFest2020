#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

class Edge{
    public:
    int v=0;
    int w=0;
    Edge(int v,int w){
        this->v=v;
        this->w=w;
    }
    Edge(){

    }
};
class BFS_Pair{
    public :
    int vt=0;
    int wt=0;
    BFS_Pair(int vt,int wt){
        this->vt=vt;
        this->wt=wt;
    }
    BFS_Pair(){

    }
};
vector<vector<Edge*>> graph;
void addEdge(int u, int v, int w){
    if (u < 0 || v < 0 || u >= graph.size() || v >= graph.size())
        return;

    graph[u].push_back(new Edge(v, w));
}
void display(){
    for(int i=0;i<graph.size();i++){
        cout<<i<<" => ";
        for(int j=0;j<graph[i].size();j++){
            cout<<"( "<<graph[i][j]->v<<", "<<graph[i][j]->w<<" )";
        }
        cout<<endl;
    }
}
void BFS(int src,vector<bool> &vis){
    vis[src]=true;
    queue<BFS_Pair*> q;
    BFS_Pair *bp=new BFS_Pair(0,0);
    q.push(bp);
    while(q.size()>0){
        BFS_Pair* rpair=q.front();
        q.pop();
        for (Edge *e:graph[rpair->vt]){
            if(!vis[e->v]){
                BFS_Pair *npair=new BFS_Pair(e->v,0);
                q.push(npair);
            }
        }
    }
}
//------------TOPOLOGICAL SORT-----------------------
bool topological_sort(int src,vector<bool> &vis,vector<bool> &cycle,vector<int> &result){

    vis[src]=true;
    cycle[src]=true;
    for(Edge *e:graph[src]){
        int nbr=e->v;
        if(!vis[nbr]){
            topological_sort(nbr,vis,cycle,result);
        }        
        if(cycle[nbr])
        return false;
    }
    result.push_back(src);
    cycle[src]=false;
}
//-----------------TOPOLOGICAL SORT(USING KAHN'S ALGO)-----------------------
void kahn_algo(){
    vector<int> inedge(graph.size());
    for(int i=0;i<graph.size();i++){
        for(Edge *e:graph[i]){
            inedge[e->v]++;
        }
    }

    queue<int> q;
    for(int i=0;i<inedge.size();i++){
        if(inedge[i]==0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int rem=q.front();
        q.pop();
        cout<<rem<<"->";
        for(Edge *e:graph[rem]){
            inedge[e->v]--;
            if(inedge[e->v]==0)
            q.push(e->v);
        }
    }
}
void solve(){
    for(int i=0;i<8;i++){
        vector<Edge *> ar;
        graph.push_back(ar);
    }

    // addEdge(0,1,10);
    // addEdge(0,3,10);
    // addEdge(3,0,10);
    // addEdge(1,2,10);
    // addEdge(2,3,40);
    // addEdge(3,4,2);
    // addEdge(4,5,2);
    // addEdge(4,6,3);
    // addEdge(5,6,8);
    // addEdge(0,1,0);
    // addEdge(0,5,0);
    // addEdge(1,2,0);
    // addEdge(2,3,0);
    // addEdge(4,5,0);
    // addEdge(4,6,0);
    // addEdge(6,3,0);

    addEdge(7,5,0);
    addEdge(7,6,0);
    addEdge(5,4,0);
    addEdge(5,2,0);
    addEdge(6,4,0);
    addEdge(6,3,0);
    addEdge(2,1,0);
    addEdge(3,1,0);
    addEdge(1,0,0);
    // vector<bool> vis(graph.size(),false);
    // vector<bool> cycle(graph.size(),false);
    // vector<int> result;
    // bool res=true;
    // for(int i=0;i<graph.size();i++){
    //     if(!vis[i]){
    //         res=topological_sort(i,vis,cycle,result);
    //     }
    // }
    // cout<<boolalpha<<res<<endl;
    // for(int i=result.size()-1;i>=0;i--)
    // cout<<result[i]<<"->";
    // cout<<endl;
    kahn_algo();
    cout<<endl;
    display();

}
int main(){
    solve();
    return 0;
}