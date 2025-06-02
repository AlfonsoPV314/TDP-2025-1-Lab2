#ifndef STP_H
#define STP_H

#include "Graph.h"


class STP{
protected:
    Graph* g;
    STP(Graph* g);
    virtual pair<vector<pair<int, int>>, double> solve() const;
    virtual void print(const pair<vector<pair<int, int>>, double>& AproxST) const;
    virtual ~STP();
public:
    bool verifyValidity(const vector<pair<int, int>>& Te, double totalWeight) const;
};

#endif 