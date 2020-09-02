#include <vector>
#include <stack>

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){};
};


std::vector<std::vector<edge>> makeDAG_Cost(std::vector<std::vector<edge>>& G, std::vector<int>& d, int goal){
    int V(G.size());
    std::vector<std::vector<edge>> DAG(V);
    for(int i(0); i < V; ++i){
        if(d[i] > d[goal]) continue;
        if(d[i] == d[goal] && i != goal) continue;
        for(auto e : G[i]){
            if(d[e.to] > d[goal]) continue;
            if(d[e.to] == d[goal] && e.to != goal) continue;
            if(d[e.to] == d[i] || d[e.to] < d[i]) continue;
            DAG[i].push_back({e.to, 1});
        }
    }
}

std::vector<std::vector<int>> makeDAGWithoutCost(std::vector<std::vector<int>>& G, std::vector<int>& d, int goal){
    int V(G.size());
    std::vector<std::vector<int>> DAG(V);
    for(int i(0); i < V; ++i){
        if(d[i] > d[goal]) continue;
        if(d[i] == d[goal] && i != goal) continue;
        for(auto e : G[i]){
            if(d[e] > d[goal]) continue;
            if(d[e] == d[goal] && e != goal) continue;
            if(d[e] != d[i] + 1) continue;
            DAG[i].push_back(e);
        }
    }
}


//stackはsetやqueueでもよい
//隣接リストがCost持ち
std::vector<int> topologicalSort_Cost(std::vector<std::vector<edge>>& DAG){
    std::vector<int> ret;
    int V(DAG.size());
    std::vector<int> h(V, 0); //入次数
    for(int i(0); i < V; ++i){
        for(auto& e : DAG[i]){
            ++h[e.to];
        }
    }
    std::stack<int> st;
    for(int i(0); i < V; ++i)
        if(!h[i]) st.push(i);
    while(st.size()){
        int i(st.top()); st.pop();
        ret.push_back(i);
        for(auto& e: DAG[i]){
            --h[e.to];
            if(!h[e.to]) st.push(e.to);
        }
    }
    return ret;
}

//隣接リストがCostなし
std::vector<int> topologicalSortWithoutCost(std::vector<std::vector<int>>& DAG){
    std::vector<int> ret;
    int V(DAG.size());
    std::vector<int> h(V, 0); //入次数
    for(int i(0); i < V; ++i){
        for(auto& e : DAG[i]){
            ++h[e];
        }
    }
    std::stack<int> st;
    for(int i(0); i < V; ++i)
        if(!h[i]) st.push(i);
    while(st.size()){
        int i(st.top()); st.pop();
        ret.push_back(i);
        for(auto& e: DAG[i]){
            --h[e];
            if(!h[e]) st.push(e);
        }
    }
    return ret;
}