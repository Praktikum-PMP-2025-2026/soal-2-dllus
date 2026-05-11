#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

void tambahEdge(Node** graf, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graf[u];
    graf[u] = newNode; 
}

bool deteksiSiklusDFS(int v, Node** graf, bool* visited, bool* recStack) {  
    visited[v] = true;
    recStack[v] = true;
    
    Node* temp = graf[v];
    while (temp != NULL) {
        int tetangga = temp->vertex;
        
        
        if (!visited[tetangga]) {
            if (deteksiSiklusDFS(tetangga, graf, visited, recStack)) {
                return true; 
            }
        } 
        else if (recStack[tetangga]) {
            return true;
        }
        
        temp = temp->next;
    }
    
    recStack[v] = false;
    return false;
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;
    Node** graf = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++) {
        graf[i] = NULL;
    }
    
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tambahEdge(graf, b, a);
    }
    
    bool* visited = (bool*)calloc(N, sizeof(bool));
    bool* recStack = (bool*)calloc(N, sizeof(bool));
    
    bool adaSiklus = false;
    
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            if (deteksiSiklusDFS(i, graf, visited, recStack)) {
                adaSiklus = true;
                break; 
            }
        }
    }
    
    if (adaSiklus) {
        printf("TIDAK BISA\n");
    } else {
        printf("BISA\n");
    }
    
    free(visited);
    free(recStack);
    for (int i = 0; i < N; i++) {
        Node* curr = graf[i];
        while (curr != NULL) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graf);
    
    return 0;
}
