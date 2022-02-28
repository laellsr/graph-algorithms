#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};
 
struct Graph {
    int V, E;
    struct Edge* edge;
};
 
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
 
void printArr(int dist[], int n, int destination)
{
    if (destination > 0)
        printf("%d", dist[destination]);
    else
    {
        for (int i = 0; i < n; ++i)
            if(dist[i]<10000)
                printf("%d:%d ", i, dist[i]);
    }
    cout << "\n";
    // printf("Vértice   Peso\n");
    // for (int i = 0; i < n; ++i)
    //     printf("%d \t\t %d\n", i, dist[i]);
}
 
void BellmanFord(struct Graph* graph, int src, int destination)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;
 
    for (int i = 1; i <= V - 1; i++) 
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Ciclo de pesos negativos\n");
            return; 
        }
    }

    printArr(dist, V, destination);
    
    return;
}

void printHelp()
{
	cout << "\n## Bellman-Ford - Comandos Válidos ##\n\n";
    cout << "1. Calcula a distancia mínima com pesos negativos do vértice 1 até o vértice 5\n";
    cout << "./bellman-ford -f <arquivo-de-entrada> -i 1 -l 5\n";
    cout << "\n";
    
    cout << "2. Imprime a distância do vértice inicial 1 até os demais\n";
    cout << "./bellman-ford -f <arquivo-de-entrada> -i 1\n";
    cout << "\n";
}
 
// Driver program to test above functions
int main(int argc, char *argv[])
{

    int i = 1, initialV = 0, finalV = 0, v, e;
	struct Graph *g;

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

				g = createGraph(v+1, e);

				int v1, v2, weight, count = 0;

				while (!inputFile.eof())
				{
					getline(inputFile, line);

					int inputLength = sscanf(line.data(), "%d %d %d", &v1, &v2, &weight);

                    g->edge[count].src = v1;
                    g->edge[count].dest = v2;

					if (inputLength == 3)
                        g->edge[count].weight = weight;

					else
						g->edge[count].weight = 1;

                    count++;
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
			sscanf(argv[++i], "%d", &initialV);

		else if (strcmp(argv[i], "-l") == 0)
			sscanf(argv[++i], "%d", &finalV);

	}

	if (initialV > 0)
		BellmanFord(g, initialV, finalV);
	else
        cout << "Vértice inicial e/ou final não informados" << "\n";

    return 0;
}