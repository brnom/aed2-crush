#include <iostream>
#include <list>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Grafo {
private:
	int V; // número de vértices
	list<pair<int, int> > * adj; // ponteiro para um array contendo as listas de adjacências

public:
	// construtor
	Grafo(int V){
		this->V = V;
		adj = new list<pair<int, int> >[V];
	}

	void addAresta(int v1, int v2, int custo){
		adj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest){
		int dist[V];
		int visitados[V];

		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		for(int i = 0; i < V; i++){
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		dist[orig] = 0;

		pq.push(make_pair(dist[orig], orig));

		while(!pq.empty()){
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			if(visitados[u] == false){
				visitados[u] = true;
				list<pair<int, int> >::iterator it;
				for(it = adj[u].begin(); it != adj[u].end(); it++){
					int v = it->first;
					int custo_aresta = it->second;
					if(dist[v] > (dist[u] + custo_aresta)){
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		return dist[dest];
	}
};





int main(int argc, char const *argv[]){

    char file_name[100]; 
    int v, e;

    // arquivo
    FILE *entrada;
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL){
        printf("\nNao encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(entrada, "%d %d ", &v, &e);

    //receber os inputs
    int **arestas = (int**) malloc(sizeof(int*) *e );
    for(int i=0; i<e; i++){
        arestas[i]= (int *) malloc(3 * sizeof(int));
        fscanf(entrada, "%d %d %d ", &arestas[i][0], &arestas[i][1], &arestas[i][2]);
    }
        



    Grafo dale(v);
    for(int i=0; i<e; i++){
        dale.addAresta(arestas[i][0], arestas[i][1], arestas[i][2]);
    }
    cout << dale.dijkstra(0, v-1) << endl;





    //desaloc
    for(int i=0; i<e; i++)
        free(arestas[i]);
    free(arestas);

    fclose(entrada);

    return 0;    
}