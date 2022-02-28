#include<bits/stdc++.h>
using namespace std;  
typedef  pair<int, int> iPair;
  
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;

    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
  
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
  
    int kruskalAGM();
};
  
struct unpackSets
{
    int *parent, *rank;
    int n;
  
    unpackSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];
  
        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;
            parent[i] = i;
        }
    }
  
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;
  
        if (rank[x] == rank[y])
            rank[y]++;
    }
};

int Graph::kruskalAGM()
{
    int agm_weight = 0;
  
    sort(edges.begin(), edges.end());
  
    unpackSets ds(V);
  
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        if (set_u != set_v)
        {
            agm_weight += it->first;
            ds.merge(set_u, set_v);
        }
    }
  
    return agm_weight;
}

void printHelp()
{
	cout << "\n## Kruskal - Comandos Válidos ##\n\n";
    cout << "1. Calcula o custo da AGM com o grafo de entrada\n";
    cout << "./kruskal -f <arquivo-de-entrada>\n";
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int i = 1, v, e;
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

				g = new Graph(v+1, e);

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
				cout << "Erro ao abrir arquivo de leitura\n";
				return 0;
			}

		}

	}
  
    int agm_weight = g->kruskalAGM();
  
    cout << agm_weight << "\n";
    
    return 0;
}