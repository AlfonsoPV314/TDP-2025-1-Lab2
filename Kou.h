#include "Strategy.h"

class Kou: public Strategy {
public:
    Kou(Graph* g);

    pair<vector<pair<int, int>>, double> solve() const override;

    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};