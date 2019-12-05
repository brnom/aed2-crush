#include <iostream>
#include <string>

using namespace std;



//func pra montar a matriz de adjacencia
int** matriz_adj(int v, int e, int** in){

    // alocando
    int **matriz = (int**) malloc(v * sizeof(int*));
    for(int i=0; i<v; i++){
        matriz[i] = (int *) malloc(v * sizeof(int));
    }


    // zerante
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            matriz[i][j]=0;

    // arrumante
    for(int i=0; i<e; i++){
        int partindo = in[i][0];
        int recebendo = in[i][1];
        int peso = in[i][2];
        if(partindo!=recebendo){ //sem autoloop
            matriz[partindo][recebendo]=peso;
            matriz[recebendo][partindo]=peso;
        }
    }

    // retornar a braba
    return matriz;
}


int main(int argc, char const *argv[]){

    char file_name[100];
    
    int v, e;

    // arquivo
    FILE *entrada;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL){
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fscanf(entrada, "%d %d ", &v, &e);
    //getc(entrada);

    //receber os inputs
    int **arestas = (int**) malloc(sizeof(int*) *e );
    for(int i=0; i<e; i++){
        arestas[i]= (int *) malloc(3 * sizeof(int));
        fscanf(entrada, "%d %d %d ", &arestas[i][0], &arestas[i][1], &arestas[i][2]);
    }
        

    //matriz adjacentte criada
    int **adj=matriz_adj(v, e, arestas);

/*  impressão da matriz de adjacencia    
    for(int i=0; i<v; i++){
        printf("linha de %2d: ", i);
        for(int j=0; j<v; j++)
            printf("%2d ", adj[i][j]);
        printf("\n");
    }
*/

    //manipulação


    //desaloc
    for(int i=0; i<e; i++)
        free(arestas[i]);
    free(arestas);

    fclose(entrada);

    return 0;    
}