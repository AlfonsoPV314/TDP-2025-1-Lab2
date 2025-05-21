#include "Graph.h"


class Strategy{
protected:
    Graph* g;
    Strategy(Graph* g);
    virtual pair<vector<pair<int, int>>, double> solve() const;
    virtual void print(const pair<vector<pair<int, int>>, double>& AproxST) const;
    virtual ~Strategy();
};