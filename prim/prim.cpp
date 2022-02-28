#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph
{
	int V; 
	list< pair<int, int> > *adj;

public:
	Graph(int V); 
	void addEdge(int u, int v, int w);

	void primMST();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Graph::primMST()
{
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int src = 0;
	vector<int> key(V, INF);

	vector<int> parent(V, -1);

	vector<bool> inMST(V, false);

    pq.push(make_pair(0, src));
	key[src] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		
		if(inMST[u] == true){
			continue;
		}
	
		inMST[u] = true; 

		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;

			if (inMST[v] == false && key[v] > weight)
			{
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	for (int i = 1; i < V; ++i)
		printf("(%d,%d) ", parent[i], i);
    printf("\n");
}

void printHelp()
{
	cout << "\n## Prim - Comandos Válidos ##\n\n";
    cout << "1. Calcula o custo da AGM com o grafo de entrada\n";
    cout << "./prim -f <arquivo-de-entrada>\n";
    cout << "\n";
}


int main(int argc, char *argv[])
{
	int V = 9;
    int i = 1, v, e;
	Graph g(V);

    for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-h") == 0)
		{
			printHelp();
			return 0;
		}
	}

    for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-f") == 0)
		{
			ifstream inputFile(argv[++i]);

			if (inputFile.is_open())
			{
				string line;

				getline(inputFile, line);

				sscanf(line.data(), "%d %d", &v, &e);

				//g = new Graph(v+1, e);

				int v1, v2, weight;

				while (!inputFile.eof())
				{
					getline(inputFile, line);

					int inputLength = sscanf(line.data(), "%d %d %d", &v1, &v2, &weight);

					if (inputLength == 3)
					{
						g.addEdge(v1, v2, weight);
					}

					else
					{
						g.addEdge(v1, v2, 1);
					}

				}

				inputFile.close();
			}
			else
			{
				cout << "Erro ao abrir arquivo de leitura\n";
				return 0;
			}

		}

	}
	g.primMST();
	return 0;
}
