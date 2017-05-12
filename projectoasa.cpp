/*	Christian Sousa @ ist.utl.pt
	Projecto de Analise e Sintese de Algoritmos - Entrega 1
	Descricao:	Programa que dado o input com a ordenacao conhecida 
				das fotografias devolve a ordenacao das fotografias dadas.
				O input e dado da seguinte forma:(1) Uma linha com N numero de fotografias
				(N>=2) e o numero de pares para os quais e conhecida a ordem L separados
				por um espaco em branco.
				(2) Uma lista de L linhas em que cada linha contem dois inteiros u e v 
				(separados por um espaco em branco) indicando que a primeira fotografia
				ocorreu antes da segunda.
*/
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3
using namespace std;
vector<list<int> > G; // Vector com a lista de adjacencias
int edges,vertices,Time; // Ligacoes, Vertices e Tempo 
vector <int> startTime; // Vector com o tempo de inicio de visita dos vertices
vector <int> endTime; // Vector com o tempo de fim de visita dos vertices
vector <int> color; // Vector com as cores de cada vertice
vector <int> parent; // Vector com os vertices pai de cada vertice
vector <int> output; // Vector com a ordenacao topologica

int incoerente=0; // Flag para verificar se o output e incoerente

// Algoritmo de visita do vertice 
void DFS_VISIT(int u)
{
    Time=Time+1;
    startTime[u]=Time;
    color[u]=GRAY;
    list<int> :: iterator it;
    it=G[u].begin();
    while(it != G[u].end())
    {
        int v= (*it);
        if(color[v] == WHITE)
        {
            parent[v]=u;
            DFS_VISIT(v);
        }
        /*	Neste caso e verificado se o vertice adjacente ja foi visitado, caso seja 
        	verdade (o vertice tem a cor GRAY) a flag incoerente e colocada a 1
        */	
        if(color[v]==GRAY){
            incoerente=1;
        }
        it++;
    }
    color[u]=BLACK;
    /*	Quando o vertice e acabado de visitar e colocado a cor BLACK, o vertice
    	e colocado na lista de ordenacao topologica
    */
    output.push_back(u);
    Time++;
    endTime[u]=Time;
    
}
// Algoritmo de Depth-First Search (como nos slides das aulas teoricas)
void DFS()
{
    for(int u=1;u<=vertices;u++)
    {
        color[u]=WHITE;
        parent[u]=0;
    }
    Time=0;
    for(int u=1;u<=vertices;u++)
    {
        if(color[u]==WHITE)
            DFS_VISIT(u);
    }
}
// Cria a lista de adjacencias
void creategraph()
{
    int v1,v2;
    for(int i=1;i<=edges;i++)
    {
        cin>>v1>>v2;
        G[v1].push_back(v2);
    }
}
int main()
{
	cin>>vertices>>edges; // Recebe o input N e L
	
	/*	Se o numero de fotografias a ordenar e superior ou igual a 2 o programa continua
		caso contrario o programa termina
	*/
	if(vertices<2){
		return 0;
	}
    /*	Alocacao dos vectores que irao ser utilizados para evitar a utilizacao de
    	vectores com dimensao estatica pois nao temos informacao sobre o numero
    	maximo de inputs que se recebem
    */	
    startTime.resize(vertices);
    startTime.reserve(vertices);
    endTime.resize(vertices);
    endTime.reserve(vertices);
    color.resize(vertices);
    color.reserve(vertices);
    parent.resize(vertices);
    parent.reserve(vertices);
    G.resize(vertices+1);
    G.reserve(vertices+1);
     
    creategraph(); // Cria o grafo
    DFS(); // Faz a Depth-First Search
    
    /*	Faz a verificacao da flag incoerente, devolve o output caso esta esteja
    	diferente de 0 e termina o programa
    */
    if(incoerente!=0){
        cout << "Incoerente\n";
        return 0;  
    }
    /*	Percorre o vector que tem a ordenacao topologica e para cada um desses 
    	valores vai a lista de adjacencias do valor e verifica se esta contem o 
    	valor da posicao seguinte do vector que tem a ordenacao topologica, isto e,
    	para cada vertice da ordenacao topologica verifica-se se na lista de 
    	adjacencias esta o vertice a seguir da ordenacao topologica
    */  
    for(int i=vertices-1; i>0; i--){
        int flag=0;
        int a = output[i];
        list<int> adj= G[a];
        int b = output[i-1];
        if(adj.size()>1){
            list<int> :: iterator it3;
            it3=adj.begin();
            
            while(it3 != adj.end()){
                if(*it3 == b){
                    flag=1;
                }
                *it3++;   
            }
        }
        else{
            if(*adj.begin() == b){
                flag=1;
            }
        }
        if(flag==0){
            cout << "Insuficiente\n";
            return 0;
        }
    }
    

    /*	Caso final em que o output nao e Incoerente nem Insuficiente, ou seja, e possivel
    	e possivel organizar as fotografias, vai ser devolvida uma linha de numeros 
    	correspondentes a organizacao temporal das fotografias 
    */
    for(int i=vertices-1; i>0; i--){ 
        cout << output[i] << " ";
    }
    cout << output[0];
    cout << "\n";
    return 0;
}