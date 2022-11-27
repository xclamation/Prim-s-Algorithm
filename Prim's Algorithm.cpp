// Prim's Algorithm.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

void print_matrix(int** g, int vertices) {
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            std::cout << g[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void generate_matrix(int** g,int vertices) {
    for (int i = 0; i < vertices; ++i)
    {
        g[i] = new int[vertices];
    }
    /*Максимальный вес ребра*/
    int maxW = 100;
    /*Вес для конкретного ребра*/
    int w;
    srand(time(NULL));
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = i; j < vertices; ++j)
        {
            if (i == j) {
                g[i][j] = 0;
            }
            else {
                w = rand() % maxW;
                g[i][j] = w;
                g[j][i] = w;
            }
        }
        // Исключаем возможность появления несвязного графа
        int nu = 0;
        for (int j = i+1; j < vertices; ++j)
        {
            if (g[i][j] == 0) {
                ++nu;
              }
        }
        if (nu == vertices-1) {
            w = (rand() % (maxW - 1));
            g[i][rand() % (vertices-(i+1))] = 1 + w;
            g[rand()%(vertices-(i+1))][i] = 1 + w;
        }
    }
    //print_matrix(g, vertices);
}

void delete_matrix(int** g, int vertices) {
    for (int i = 0; i < vertices; ++i)
    {
        delete[] g[i];
    }
    delete[] g;
}

int minimum_key(int*k, int* mst, int vertices)    
{  
    int minimum  = INT_MAX, min,i;    
      
    /*iterate over all vertices to find the vertex with minimum key-value*/  
    for (i = 0; i < vertices; ++i)  
        if (mst[i] == 0 && k[i] < minimum )   
            minimum = k[i], min = i;    
    return min;    
}    
/* create prim() method for constructing and printing the MST.  
The g[vertices][vertices] is an adjacency matrix that defines the graph for MST.*/  
double prim(int vertices)    
{
    int** g = new int* [vertices];
    generate_matrix(g, vertices);
    double start = clock();
    /* create array of size equal to total number of vertices for storing the MST*/  
    int* parent = new int[vertices];    
    /* create k[vertices] array for selecting an edge having minimum weight*/  
    int* k = new int[vertices];       
    int* mst = new int[vertices];      
    int i, count,edge,v; /*Here 'v' is the vertex*/  
    for (i = 0; i < vertices; ++i)  
    {  
        k[i] = INT_MAX;  
        mst[i] = 0;    
    }  
    k[0] = 0; /*It select as first vertex*/  
    parent[0] = -1;   /* set first value of parent[] array to -1 to make it root of MST*/  
    for (count = 0; count < vertices-1; ++count)    
    {    
        /*select the vertex having minimum key and that is not added in the MST yet from the set of vertices*/  
        edge = minimum_key(k, mst,vertices);    
        mst[edge] = 1;    
        for (v = 0; v < vertices; ++v)    
        {  
            if (g[edge][v] && mst[v] == 0 && g[edge][v] <  k[v])    
            {  
                parent[v]  = edge, k[v] = g[edge][v];    
            }  
        }  
    }    
     /*Print the constructed Minimum spanning tree*/  
     /*printf("\n Edge \t  Weight\n");  
     for (i = 1; i < vertices; i++)    
     printf(" %d <-> %d    %d \n", parent[i], i, g[i][parent[i]]);*/    
    double end = clock();
    double time = end - start;
    delete[] parent;
    delete[] k;
    delete[] mst;
    delete_matrix(g, vertices);
    return time;
}    

void test_prim(int vertices, int mult, int maxIteration, int maxVert) {   
    std::ofstream out("output.txt");
    //out << "n: " << vertices << " - " << vertices * pow(mult, maxIteration - 1) << ", " << mult << '\n';
    int n = vertices;
    for (int i = 0; (i < maxIteration) && (vertices < maxVert); ++i)
    {
        n = vertices;
        out << prim(n) << ", ";
        std::cout << n << ", ";
        n = vertices + vertices/4;
        out << prim(n) << ", ";
        std::cout << n << ", ";
        n = vertices + vertices / 2;
        out << prim(n) << ", ";
        std::cout << n << ", ";
        n = vertices + 3*vertices / 4;
        out << prim(n) << ", ";
        std::cout << n << ", ";
        vertices*= mult;

    }
    out << '\n';
    out << n;

    out.close();
}

int main()    
{    
    /*n = {256, 320, 384, 448, 512, 640, 768, 896, 1024, 1280, 1536, 1792, 2048, 2560, 3072, 3584, 4096, 5120, 6144, 7168, 8192, 10240, 12288, 14336}*/
    test_prim(256, 2 , 14,10000);
    return 0;  
}  

