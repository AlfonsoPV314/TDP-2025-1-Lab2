#include "Strategy.h"

class Takahashi: public Strategy {
public:
    Takahashi(Graph* g);

    pair<vector<pair<int, int>>, double> solve() const override;

    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};