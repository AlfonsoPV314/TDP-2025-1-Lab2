#ifndef APV_H
#define APV_H

#include "STP.h"
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class APV : public STP {
    public:
    APV(Graph* g);
    std::pair<std::vector<std::pair<int, int>>, double> solve() const override;
    void print(const std::pair<std::vector<std::pair<int, int>>, double>& AproxST) const;

private:
    std::pair<std::vector<std::pair<int, int>>, double> buildSteinerTree(
        Graph* GPrima,
        const std::vector<std::vector<std::vector<std::pair<std::pair<int, int>, double>>>>& pathMap
    ) const;
};


#endif