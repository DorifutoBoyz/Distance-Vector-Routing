#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Initiate Struct link
struct Link {
    int hop, dest, wt;
};

// Initiate Struct Network
struct Network {
    int H, L;
    struct Link *link;
};

// Fungsi BellmanFordnya
void bellmanFord(struct Network* n, int S) {
    int H = n->H;
    int L = n->L;
    int dist[H];

    // Initialize all distances to INT_MAX
    for (int i = 0; i < H; i++)
        dist[i] = INT_MAX;

    // Distance from source to itself is always 0
    dist[S] = 0;

    // Relax all edges H-1 times
    for (int i = 1; i < H; i++) {
        for (int j = 0; j < L; j++) {
            int u = n->link[j].hop;
            int v = n->link[j].dest;
            int wt = n->link[j].wt;
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < L; i++) {
        int u = n->link[i].hop;
        int v = n->link[i].dest;
        int wt = n->link[i].wt;
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            printf("Network contains negative weight cycle\n");
            return;
        }
    }

    // Print the results
    printf("\nHop\tDistance from source\n");
    for (int i = 0; i < H; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \tINF\n", i);
        } else {
            printf("%d \t%d\n", i, dist[i]);
        }
    }
}

int main() {
    int H, L, S;

    // Untuk Menginputkan input pengguna
    printf("Distance Vector Routing using Bellman Ford Algorithm:\nEnter number of hops: ");
    scanf("%d", &H);
    printf("Enter number of links: ");
    scanf("%d", &L);
    printf("Enter source hop: ");
    scanf("%d", &S);

    // Untuk Mengalokasikan Memori untuk struktur networknya
    struct Network* n = (struct Network*) malloc(sizeof(struct Network));
    n->H = H;
    n->L = 2 * L; // Karena setiap link memiliki arah dua arah
    n->link = (struct Link*) malloc(n->L * sizeof(struct Link));

    // Untuk Menginputkan Sumber, Destinasi, dan Beban / Jarak
    for (int i = 0; i < L; i++) {
        int hop, dest, wt;
        printf("\nLink %d: enter source, destination and weight: \n", i + 1);
        scanf("%d %d %d", &hop, &dest, &wt);
        n->link[2 * i].hop = hop;
        n->link[2 * i].dest = dest;
        n->link[2 * i].wt = wt;
        n->link[2 * i + 1].hop = dest;
        n->link[2 * i + 1].dest = hop;
        n->link[2 * i + 1].wt = wt;
    }

    // Untuk Initiate fungsi BellmanFord
    bellmanFord(n, S);

    // Free allocated memory
    free(n->link);
    free(n);

    return 0;
}
