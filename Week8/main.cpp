#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<stack>
#include<string>
#include<sstream>
using namespace std;
vector<vector<int>> convertMatrixToList(const string& filename) {
	vector<vector<int>>m_to_l;

	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "Error\n";
		return m_to_l;
	}
	int n;
	fin >> n;
	m_to_l.resize(n);
	string line;
	getline(fin, line);
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			int value;
			fin >> value;
			if (value == 1) {
				
				m_to_l[i].push_back(j);
			}
		}
		


	}
	return m_to_l;
}
vector<vector<int>> convertListToMatrix(const string& filename) {
	vector<vector<int>>l_to_m;
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "Error\n";
		return l_to_m;
	}
	int n;
	fin >> n;
	l_to_m.resize(n, vector<int>(n, 0));
	string line;
	getline(fin, line);
	for (int i = 0; i < n; i++) {
		getline(fin, line);
		stringstream ss(line);
		int edge;
		ss >> edge;
		int value;
		while (ss >> value) {
			l_to_m[i][value] = 1;
		}
		
	}
	return l_to_m;
}
bool isDirected(const vector<vector<int>>& adjMatrix) {
	int s = adjMatrix.size();
	for (int i = 0; i < s; i++) {
		for (int j = i + 1; j < s; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix) {
	int count = 0;
	int s = adjMatrix.size();
	if (isDirected(adjMatrix)) {
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s; j++) {
				if (adjMatrix[i][j] == 1) {
					count++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < s; i++) {
			for (int j = i + 1; j < s; j++) {
				if (adjMatrix[i][j] == 1) {
					count++;
					
				}
			}
		}
	}
	return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> vertices;
	int n = adjMatrix.size();
	for (int i = 0; i < n; ++i) {
		bool isolated = true;
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
				isolated = false;
				break;
			}
		}
		if (isolated) vertices.push_back(i);
	}
	return vertices;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	if (adjMatrix.empty()) return true;
	int s = adjMatrix.size();
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			if (i == j) {//cheo 1 thi sai 0 thi dung
				if (adjMatrix[i][j] == 1)return false;
			}
			else {
				if (adjMatrix[i][j] == 0)return false;
			}
		}
		
	}
	return true;

}
bool isBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	for (int start = 0; start < n; ++start) {
		if (color[start] == -1) {
			queue<int> q;
			q.push(start);
			color[start] = 0;
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int v = 0; v < n; ++v) {
					if (adjMatrix[u][v]) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[v] == color[u]) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> group(n, -1);
	for (int i = 0; i < n; ++i) {
		if (group[i] == -1) {
			queue<int> q;
			q.push(i);
			group[i] = 0;
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int v = 0; v < n; ++v) {
					if (adjMatrix[u][v]) {
						if (group[v] == -1) {
							group[v] = 1 - group[u];
							q.push(v);
						}
						else if (group[v] == group[u]) {
							return false;
						}
					}
				}
			}
		}
	}
	
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			if (u != v) {
				if (group[u] != group[v] && !adjMatrix[u][v]) return false;
				if (group[u] == group[v] && adjMatrix[u][v]) return false;
			}
		}
	}
	return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> undirected(n, vector<int>(n, 0));
	for (int u = 0; u < n; ++u)
		for (int v = 0; v < n; ++v)
			if (adjMatrix[u][v] || adjMatrix[v][u])
				undirected[u][v] = undirected[v][u] = 1;
	return undirected;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> complement(n, vector<int>(n, 0));
	for (int u = 0; u < n; ++u)
		for (int v = 0; v < n; ++v)
			if (u != v)
				complement[u][v] = adjMatrix[u][v] ? 0 : 1;
	return complement;
}
bool hasEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	bool directed = isDirected(adjMatrix);

	if (directed) {
		vector<int> in(n, 0), out(n, 0);
		for (int u = 0; u < n; ++u)
			for (int v = 0; v < n; ++v)
				if (adjMatrix[u][v]) {
					out[u]++;
					in[v]++;
				}
		for (int i = 0; i < n; ++i)
			if (in[i] != out[i]) return false;

		
		vector<bool> visited(n, false);
		queue<int> q;
		int start = -1;
		for (int i = 0; i < n; ++i)
			if (out[i] > 0) {
				start = i;
				break;
			}
		if (start == -1) return false; // Không có cạnh nào

		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; ++v)
				if (adjMatrix[u][v] && !visited[v]) {
					visited[v] = true;
					q.push(v);
				}
		}
		for (int i = 0; i < n; ++i)
			if ((in[i] > 0 || out[i] > 0) && !visited[i]) return false;
		return true;
	}
	else {
		vector<bool> visited(n, false);
		queue<int> q;
		int start = -1;
		for (int i = 0; i < n; ++i) {
			int deg = 0;
			for (int j = 0; j < n; ++j) deg += adjMatrix[i][j];
			if (deg > 0) {
				start = i;
				break;
			}
		}
		if (start == -1) return false;

		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v] && !visited[v]) {
					visited[v] = true;
					q.push(v);
				}
			}
		}

		for (int i = 0; i < n; ++i) {
			int deg = 0;
			for (int j = 0; j < n; ++j) deg += adjMatrix[i][j];
			if (deg > 0 && !visited[i]) return false;
			if (deg % 2 != 0) return false;
		}
		return true;
	}
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	if (!hasEulerCycle(adjMatrix)) return {};
	int n = adjMatrix.size();
	bool directed = isDirected(adjMatrix);

	vector<vector<int>> graph = adjMatrix;
	stack<int> stk;
	vector<int> cycle;
	stk.push(0);

	while (!stk.empty()) {
		int u = stk.top();
		bool hasEdge = false;
		for (int v = 0; v < n; ++v) {
			if (graph[u][v] > 0) {
				stk.push(v);
				graph[u][v]--;
				if (!directed)
					graph[v][u]--;
				hasEdge = true;
				break;
			}
		}
		if (!hasEdge) {
			cycle.push_back(u);
			stk.pop();
		}
	}

	reverse(cycle.begin(), cycle.end());
	return cycle;
}

void dfsHelper(int u, const vector<vector<int>>& adjMatrix, vector<vector<int>>& tree, vector<bool>& visited) {
	visited[u] = true;
	int n = adjMatrix.size();
	for (int v = 0; v < n; ++v) {
		if (adjMatrix[u][v] && !visited[v]) {
			tree[u][v] = tree[v][u] = 1; // thêm vào cây bao trùm
			dfsHelper(v, adjMatrix, tree, visited);
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	dfsHelper(start, adjMatrix, tree, visited);
	return tree;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				q.push(v);
			}
		}
	}
	return tree;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;
	q.push(u);
	visited[u] = true;
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		if (curr == v) return true;
		for (int i = 0; i < n; ++i) {
			if (adjMatrix[curr][i] && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return false;
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;
	vector<bool> visited(n, false);
	for (int i = 0; i < n; ++i) {
		int u = -1;
		for (int j = 0; j < n; ++j)
			if (!visited[j] && (u == -1 || dist[j] < dist[u]))
				u = j;
		if (u == -1 || dist[u] == INT_MAX) break;
		visited[u] = true;
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
				dist[v] = dist[u] + adjMatrix[u][v];
				prev[v] = u;
			}
		}
	}
	if (dist[end] == INT_MAX) return {};
	vector<int> path;
	for (int at = end; at != -1; at = prev[at]) path.push_back(at);
	reverse(path.begin(), path.end());
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;
	for (int k = 0; k < n - 1; ++k) {
		for (int u = 0; u < n; ++u) {
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v] && dist[u] != INT_MAX &&
					dist[u] + adjMatrix[u][v] < dist[v]) {
					dist[v] = dist[u] + adjMatrix[u][v];
					prev[v] = u;
				}
			}
		}
	}
	if (dist[end] == INT_MAX) return {};
	vector<int> path;
	for (int at = end; at != -1; at = prev[at]) path.push_back(at);
	reverse(path.begin(), path.end());
	return path;
}


