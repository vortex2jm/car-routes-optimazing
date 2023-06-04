#include <stdio.h>
#include <stdlib.h>
#include "../include/PQ.h"
#include "../include/node.h"

static int *map;
static int N;

static void swap(Node *pq, int i, int j)
{
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Node *pq, int k)
{
    while (k > 1 && greater(pq[k / 2], pq[k]))
    {
        swap(pq, k, k / 2);
        k = k / 2;
    }
}

void fix_down(Node *pq, int sz, int k)
{
    while (2 * k <= sz)
    {
        int j = 2 * k;
        if (j < sz && greater(pq[j], pq[j + 1]))
        {
            j++;
        }
        if (!greater(pq[k], pq[j]))
        {
            break;
        }
        swap(pq, k, j);
        k = j;
    }
}

void PQ_init(Node *pq, int maxN)
{
    pq = (Node *)malloc((maxN + 1) * sizeof(Node));
    map = (int *)malloc((maxN + 1) * sizeof(int));
    N = 0;
}

void PQ_insert(Node *pq, Node v)
{
    N++;
    pq[N] = v;
    map[id(v)] = N;
    fix_up(pq, N);
}

Node PQ_delmin(Node *pq)
{
    Node min = pq[1];
    swap(pq, 1, N);
    N--;
    fix_down(pq, N, 1);
    return min;
}

Node PQ_min(Node *pq)
{
    return pq[1];
}

void PQ_decrease_key(Node *pq, int id, double value)
{
    int i = map[id];
    value(pq[i]) = value;
    fix_up(pq, i);
}

bool PQ_empty()
{
    return N == 0;
}

int PQ_size()
{
    return N;
}

void PQ_finish(Node *pq)
{
    free(pq);
    free(map);
}
