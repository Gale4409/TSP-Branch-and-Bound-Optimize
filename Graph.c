#include "Graph.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ST.h"

#define MAXN 151 //buffer for string on the input file

typedef struct node *link;

struct node {
    int v; int wt; link next;
};

struct graph {
    int V; int E;
    link *ladj;
    ST tab;
};

static link newnode (int v, int wt, link next) {
    link x = malloc (sizeof(struct node));
    if (x == NULL) return NULL;
    x->v = v; x->next = next; x->wt = wt;
    return x;
}

static Edge EDGEcreate (int v, int w, int wt) { return (Edge){v, w, wt}; }

G GRAPHinit (int V) {
    G graph = malloc (sizeof(struct graph));
    if (graph == NULL) return NULL;
    graph->V = V;
    graph->tab = STinit(V);
    if (graph->tab == NULL) { free (graph); return NULL; }
    graph->ladj = calloc (V, sizeof(link));
    if (graph->ladj == NULL) { STfree(graph->tab); free(graph); return NULL; }
    graph->E = 0;
    return graph;
}

G GRAPHload (FILE *input) {
    if (input == NULL) return NULL;
    int V;
    fscanf (input, "%d", &V);
    if (V<=0) return NULL;
    G graph = GRAPHinit (V);
    if (graph == NULL) return NULL;
    int i;
    char name[MAXN];
    int population, altitude;
    for (i=0; i<V; i++) {
        fscanf (input, "%150s %d %d", name, &population, &altitude);
        STinsert (graph->tab, ITEMload(name, population, altitude), i);
    }
    int E, v, w, wt;
    char key1[MAXN], key2[MAXN];
    fscanf (input, "%d", &E);
    for (i=0; i<E; i++) {
        fscanf (input, "%150s %150s %d", key1, key2, &wt);
        City fake1 = ITEMload (key1, 0, 0);
        City fake2 = ITEMload (key2, 0, 0);
        v = STgetIndex (graph->tab, fake1); //creation of a fake item to use the key
        w = STgetIndex (graph->tab, fake2);
        ITEMfree(fake1); ITEMfree(fake2);
        if (v == -1 || w == -1) continue; //one of the key was not correct!
        GRAPHinsertE(graph, EDGEcreate(v, w, wt)); //creation of the Edge!
    }
    return graph;
}

void GRAPHinsertE (G graph, Edge e) {
    if (graph == NULL || e.v < 0 || e.v >= graph->V || e.w < 0 || e.w >= graph->V || e.wt < 0) return;
    graph->ladj[e.v] = newnode(e.w, e.wt, graph->ladj[e.v]); //head insertion
    graph->ladj[e.w] = newnode(e.v, e.wt, graph->ladj[e.w]); //head insertion in the opposite direction
}

static void copy_vet (int *v1, int *v2, int len) {
    int i;
    for (i=0; i<len; i++) v2[i] = v1[i];
}

static void GRAPH_STP_R (int len, int start, int v, G graph, int *visited, int *path, int dist, int *B_dist, int *B_path, int *pruned_branches) {
    if (dist > *B_dist) {
        (*pruned_branches)++;
        return;
    }
    if (v == start && len == graph->V+1) { //terminative case - is granted thanks to the pruning that is we enter here is also the best scenario till now!
        //the lenght of a Hamiltonian path is V-1, this is a cycle so we must check lenght == V
        copy_vet(path, B_path, graph->V+1);
        *B_dist = dist;
    }
    link x;
    for (x=graph->ladj[v]; x!=NULL; x=x->next) {
        if (visited[x->v] == 0 || (x->v == start && len == graph->V)) {
            if (x->v != start) visited[x->v] = 1;
            path[len] = x->v;
            GRAPH_STP_R(len + 1, start, x->v, graph, visited, path, dist + x->wt, B_dist, B_path, pruned_branches);
            if (x->v != start) visited[x->v] = 0; //backtrack
        }
    }
}

void GRAPH_TSP (G graph, int start) {
    if (graph == NULL || start < 0 || start >= graph->V) return;
    int *visited = calloc (graph->V, sizeof(int));
    int *path = malloc ((graph->V+1)*sizeof(int));
    int *B_path = malloc ((graph->V+1)*sizeof (int));
    int i;
    for (i=1; i<(graph->V+1); i++) path[i] = B_path[i] = -1;
    visited[start] = 1;
    path[0] = B_path[0] = start;
    int B_dist = INT_MAX, pruned_branches = 0;
    GRAPH_STP_R (1, start, start, graph, visited, path, 0, &B_dist, B_path, &pruned_branches);
    //output of the solution:
    if (B_dist == INT_MAX) printf ("\nPath not found\n");
    else {
        printf ("\nPath found with distance %dkm\n", B_dist);
        for (i=0; i<graph->V; i++) {
            printf ("%s -> ", ITEMgetname(STget(graph->tab, B_path[i])));
        }
        printf ("%s\n", ITEMgetname(STget(graph->tab, B_path[i])));
        printf ("\nPruned brunches: %d\n", pruned_branches);
    }
    free (visited); free (path); free (B_path);
}

void GRAPHfree (G graph) {
    if (graph == NULL) return;
    STfree (graph->tab);
    int i;
    for (i=0; i<graph->V; i++) {
        link x=graph->ladj[i], tmp;
        while (x != NULL) {
            tmp = x->next;
            free (x);
            x = tmp;
        }
    }
    free (graph->ladj);
    free (graph);
}