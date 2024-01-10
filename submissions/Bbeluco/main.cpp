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
        Pair maior_numero_individual{0, 0};
        for(size_t i{0}; i < groups.size(); ++i) {
            Pair grupo_atual{ groups[i][groups[i].size() - 1] };
            if(maior_numero_individual.second < grupo_atual.second && grupo_atual.first <= total_land){
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

    int total_land{ 10 };
    VectorPair space_and_earn_per_seed{ {3,44},{1,78},{2,64},{1,49},{4,69},{1,87},{3,78},{2,45},{3,84} };
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