#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

// 图节点结构体
struct Node {
    int value;
    std::vector<std::pair<Node*, int>> neighbors;  // 邻居节点和边的权重

    Node(int val) : value(val) {}
};

// 图类
class Graph {
public:
    // 添加节点到图中
    void addNode(Node* node) {
        nodes.push_back(node);
    }

    // 添加边到图中
    void addEdge(Node* from, Node* to, int weight) {
        from->neighbors.push_back({to, weight});
        to->neighbors.push_back({from, weight});
    }

    // 广度优先搜索
    void BFS(Node* start) {
        std::vector<bool> visited(nodes.size(), false);
        std::queue<Node*> q;

        visited[start->value] = true;
        q.push(start);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->value << " ";

            for (const auto& neighbor : current->neighbors) {
                if (!visited[neighbor.first->value]) {
                    visited[neighbor.first->value] = true;
                    q.push(neighbor.first);
                }
            }
        }
        std::cout << std::endl;
    }

    // 深度优先搜索
    void DFS(Node* start) {
        std::vector<bool> visited(nodes.size(), false);
        DFSUtil(start, visited);
        std::cout << std::endl;
    }

    // Dijkstra算法求最短路径
    void shortestPath(Node* start) {
        std::vector<int> dist(nodes.size(), std::numeric_limits<int>::max());
        std::vector<bool> visited(nodes.size(), false);
        dist[start->value] = 0;

        std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<std::pair<int, Node*>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            Node* current = pq.top().second;
            pq.pop();

            if (visited[current->value]) continue;
            visited[current->value] = true;

            for (const auto& neighbor : current->neighbors) {
                int newDist = dist[current->value] + neighbor.second;
                if (newDist < dist[neighbor.first->value]) {
                    dist[neighbor.first->value] = newDist;
                    pq.push({newDist, neighbor.first});
                }
            }
        }

        // 输出最短路径
        for (int i = 0; i < nodes.size(); ++i) {
            std::cout << "从节点 " << start->value  << " 到节点 " << i << " 最短距离是: ";
            if (dist[i] == std::numeric_limits<int>::max()) {
                std::cout << "INF" << std::endl;
            } else {
                std::cout << dist[i] << std::endl;
            }
        }
    }

    // Prim算法求最小支撑树
    void minimumSpanningTree() {
        std::vector<bool> inMST(nodes.size(), false);
        std::vector<int> key(nodes.size(), std::numeric_limits<int>::max());
        std::vector<Node*> parent(nodes.size(), nullptr);

        // 从第一个节点开始
        key[0] = 0;
        parent[0] = nullptr;

        for (int i = 0; i < nodes.size() - 1; ++i) {
            int minKey = std::numeric_limits<int>::max(), minIndex;
            for (int v = 0; v < nodes.size(); ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }

            Node* u = nodes[minIndex];
            inMST[u->value] = true;

            for (const auto& neighbor : u->neighbors) {
                Node* v = neighbor.first;
                int weight = neighbor.second;
                if (!inMST[v->value] && weight < key[v->value]) {
                    parent[v->value] = u;
                    key[v->value] = weight;
                }
            }
        }

        // 输出最小支撑树
        std::cout << "最小生成树:" << std::endl;
        for (int i = 1; i < nodes.size(); ++i) {
            std::cout << parent[i]->value << " - " << i << " 具有权重 " << key[i] << std::endl;
        }
    }

private:
    // DFS辅助函数
    void DFSUtil(Node* node, std::vector<bool>& visited) {
        visited[node->value] = true;
        std::cout << node->value << " ";

        for (const auto& neighbor : node->neighbors) {
            if (!visited[neighbor.first->value]) {
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    std::vector<Node*> nodes;
};



int main() {
    // 创建节点
    Node* node0 = new Node(0);
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);

    // 创建图并添加节点和边
    Graph graph;
    graph.addNode(node0);
    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);

    graph.addEdge(node0, node1, 4);
    graph.addEdge(node0, node2, 2);
    graph.addEdge(node1, node2, 5);
    graph.addEdge(node1, node3, 10);
    graph.addEdge(node2, node3, 3);

    // 测试BFS
    std::cout << "从节点0开始广度搜索: ";
    graph.BFS(node0);

    // 测试DFS
    std::cout << "从节点0开始深度搜索: ";
    graph.DFS(node0);

    // 测试最短路径算法
    std::cout << "从零开始的最短路径: " << std::endl;
    graph.shortestPath(node0);

    // 测试最小支撑树算法
    graph.minimumSpanningTree();

    // 释放内存
    delete node0;
    delete node1;
    delete node2;
    delete node3;

    return 0;
}