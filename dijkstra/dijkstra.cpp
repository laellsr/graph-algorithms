#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <list>
#include <queue>
#define MAX 10000000

using namespace std;

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

	int dijkstra(int source, int dest)
	{

		int dist[V];
		int checked[V];

		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		for(int i = 0; i < V; i++)
		{
			dist[i] = MAX;
			checked[i] = false;
		}

		dist[source] = 0;

		pq.push(make_pair(dist[source], source));

		while(!pq.empty())
		{
			pair<int, int> p = pq.top();
			int u = p.second;
			pq.pop();

			if(checked[u] == false)
			{
				checked[u] = true;

				list<pair<int, int> >::iterator it;

				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					int v = it->first;
					int edgeWeight = it->second;

					if(dist[v] > (dist[u] + edgeWeight))
					{
						dist[v] = dist[u] + edgeWeight;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		return dist[dest];
	}
};

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

	if (initialV > 0 && finalV > 0)
	{
		cout << g->dijkstra(initialV, finalV) << endl;
	}
	else if (initialV > 0)
	{
        int dist;
        for (i = 1; i <= v; i++)
        {
            dist = g->dijkstra(initialV, i);
            if (i == v)
            {
                printf("%d:%d\n", i, dist);
            }
            else
            {
                printf("%d:%d ", i, dist);
            }   
        }
	}
	else
    {
        cout << "Vértice inicial e final não informados" << "\n";
    } 

	return 0;
}