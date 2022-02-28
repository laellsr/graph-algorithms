#include <bits/stdc++.h>
#include <list>
using namespace std;

#define vertices 6

class Graph
{
private:
	int V;
	list<pair<int, int> > * adj;

public:

	Graph(int V)
	{
		this->V = V;
		adj = new list<pair<int, int> >[V];
	}

	void addEdge(int v1, int v2, int weight)
	{
		adj[v1].push_back(make_pair(v2, weight));
	}
};

int minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < vertices; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

void printMST(int parent[], int graph[vertices][vertices])
{
	for (int i = 1; i < vertices; i++)
		cout<<"("<<parent[i]<<","<<i<<")"<<"\t"<<graph[i][parent[i]]<<" \n";
}

void primMST(int graph[vertices][vertices])
{
	int parent[vertices];
	
	int key[vertices];
	
	bool mstSet[vertices];

	for (int i = 0; i < vertices; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < vertices - 1; count++)
	{
		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < vertices; v++)

			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	printMST(parent, graph);
}

void printHelp()
{
	cout << "\n## Dijkstra - Comandos Válidos ##\n\n";
    cout << "1. Calcula a distancia mínima do vértice 1 até o vértice 5\n";
    cout << "./dijkstra -f <arquivo-de-entrada> -i 1 -l 5\n";
    cout << "\n";
    
    cout << "2. Imprime a distância do vértice inicial 1 até os demais\n";
    cout << "./dijkstra -f <arquivo-de-entrada> -i 1\n";
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int i = 1, initialV = 0, finalV = 0, v, e;
    bool ascSolution = false;
	Graph *g;

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

				g = new Graph(v+1);

				int v1, v2, weight;

				while (!inputFile.eof())
				{
					getline(inputFile, line);

					int inputLength = sscanf(line.data(), "%d %d %d", &v1, &v2, &weight);

					if (inputLength == 3)
					{
						g->addEdge(v1, v2, weight);
					}

					else
					{
						g->addEdge(v1, v2, 1);
					}

				}

				inputFile.close();

			}
			else
			{
				cout << "Erro ao abrir arquivo de leitura";
				return 0;
			}

		}

		else if (strcmp(argv[i], "-i") == 0)
		{
			sscanf(argv[++i], "%d", &initialV);
		}

		else if (strcmp(argv[i], "-l") == 0)
		{
			sscanf(argv[++i], "%d", &finalV);
		}

	}
    /*
	int graph[vertices][vertices] = {
                        { 0, 2, 0, 6, 0 },
						{ 2, 0, 3, 8, 5 },
						{ 0, 3, 0, 0, 7 },
						{ 6, 8, 0, 0, 9 },
						{ 0, 5, 7, 9, 0 } };
    */
	primMST(graph);

	return 0;
}
