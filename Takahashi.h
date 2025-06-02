#ifndef TAKAHASHI_H
#define TAKAHASHI_H

#include "STP.h"

class Takahashi: public STP {
public:
    Takahashi(Graph* g);

    pair<vector<pair<int, int>>, double> solve() const override;

    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};

#endif