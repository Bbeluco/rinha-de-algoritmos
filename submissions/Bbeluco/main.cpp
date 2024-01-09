#include <iostream>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

using Pair = std::pair<int, int>;
using VectorPair = std::vector<Pair>;

bool compareEarns(Pair p1, Pair p2) {
    return (p1.second < p2.second);
}

void populateGroups(const VectorPair& space_and_earn_per_seed, std::vector<VectorPair>& groups) {
    for(Pair p : space_and_earn_per_seed) {
        VectorPair info {p};
        groups[p.first - 1].push_back(p);
    }
}

void sortGroups(std::vector<VectorPair>& groups) {
    for(VectorPair& p : groups) {
        std::sort(p.begin(), p.end(), compareEarns);
    }
}

int calculateEarns(std::vector<VectorPair>& groups, int& total_land) {
    int total_earns{0};
    /*
    Cola resposta certa
    1 87
    1 78
    2 64
    1 49
    3 84
    2 45

    O que vale mais a pena?
    1 + 1 / 2?
    1 + 1 + 1 / 3?
    1 + 1 + 1 + 1/ 4?
    */
    while(total_land > 0) {
        std::cout << "total_land: " << total_land << '\n';
        std::cout << "total_earns: " << total_earns << '\n';

        std::cout << '\n';

        Pair maior_numero_individual{0, 0};
        for(size_t i{0}; i < groups.size(); ++i) {
            Pair grupo_atual{ groups[i][groups[i].size() - 1] };
            if(maior_numero_individual.second < grupo_atual.second){
                maior_numero_individual.first = grupo_atual.first;
                maior_numero_individual.second = grupo_atual.second;
            }
        }
        bool achou{false};
        for(int i{static_cast<int>(maior_numero_individual.first - 2)}; i > 0; --i) {
            for(size_t j{0}; j < i; ++j) {
                int a{groups[i][groups[i].size() - 1].second};
                int b{groups[j][groups[j].size() - 1].second};

                if(maior_numero_individual.second < a+b){
                    total_earns += a+b;
                    total_land -= i+(j+2);
                    groups[i].pop_back();
                    groups[j].pop_back();
                    achou = true;
                    break;
                }
            }
            if(achou){
                break;
            }
        }

        if(!achou) {
            total_earns += maior_numero_individual.second;
            total_land -= maior_numero_individual.first;
            groups[maior_numero_individual.first - 1].pop_back();
        }
    }
    return total_earns;
}

int main() {
    std::clock_t start, end;
    start = clock();

    int total_land{ 36 };
    VectorPair space_and_earn_per_seed{ {3,86},{1,80},{3,71},{2,39},{2,53},{3,47},{2,46},{1,32},{1,69},{2,89},{4,58},{3,86},{3,54},{3,53},{1,64},{4,82},{1,46},{2,48},{4,53},{1,68},{3,94},{1,87} };
    std::vector<VectorPair> groups(4);

    populateGroups(space_and_earn_per_seed, groups);
    sortGroups(groups);

    int resultado { calculateEarns(groups, total_land) };
    std::cout << "Resultado: " << resultado << '\n';
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed 
         << time_taken << std::setprecision(5);
    std::cout << " sec " << '\n';
    return 0;
}