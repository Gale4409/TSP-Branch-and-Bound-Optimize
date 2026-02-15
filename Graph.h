#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct graph *G;

typedef struct { int v; int w; int wt; } Edge;

G GRAPHinit (int V);
G GRAPHload (FILE *input);
void GRAPHinsertE (G graph, Edge e);
void GRAPH_TSP (G graph, int start);
void GRAPHfree (G graph);

#endif
