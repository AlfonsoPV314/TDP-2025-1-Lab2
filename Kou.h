#ifndef KOU_H
#define KOU_H

#include "STP.h"

class Kou: public STP {
public:
    Kou(Graph* g);

    pair<vector<pair<int, int>>, double> solve() const override;

    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};

#endif