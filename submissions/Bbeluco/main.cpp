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
    //Ideia:
    //A ideia eh simples, saber o que vale mais a pena
    //exemplo com 4 slotes disponiveis
    //4
    //3 + 1
    //2 + 2
    //1 + 1 + 1 + 1
    while(total_land > 0) {
        std::cout << '\n';
        std::cout << "Terra atual: " << total_land << '\n';

        VectorPair ultimo_grupo_disponivel { groups[groups.size() - 1]};
        int qtd_terra_ultimo_grupo { ultimo_grupo_disponivel[0].first };
        if(qtd_terra_ultimo_grupo > total_land) {
            groups.pop_back();
            continue;
        }

        if(groups.size() == 0) {
            break;
        }

        int maior_ganho_possivel{ ultimo_grupo_disponivel[ultimo_grupo_disponivel.size() - 1].second };
        std::cout << "Maior ganho possivel: " << maior_ganho_possivel << '\n';
        
        bool achou{false};
        int numero_menor{0};
        for(int numero_maior {groups.size() - 2}; numero_maior > 0; --numero_maior) {
            int ganhoA{};
            int ganhoB{};
            ganhoA = groups[numero_maior][groups[numero_maior].size() - 1].second;
            int terraA { groups[numero_maior][groups[numero_maior].size() - 1].first };
            ganhoB = groups[numero_menor][groups[numero_menor].size() - 1].second;
            int terraB { groups[numero_menor][groups[numero_menor].size() - 1].first };

            if(terraA == terraB) {
                ganhoA = groups[numero_maior][groups[numero_maior].size() - 1].second;
                ganhoB = groups[numero_menor][groups[numero_menor].size() - 2].second;
            }

            std::cout << "ganhoA + ganhoB: " << ganhoA + ganhoB << '\n';
            std::cout << "N1: " << terraA << '\n';
            std::cout << "N2: " << terraB << '\n';

            if(ganhoA + ganhoB > maior_ganho_possivel) {
                achou = true;
                total_earns += ganhoA + ganhoB;
                total_land -= terraA + terraB;
                std::cout << "ganhoA+ganhoB removendo " << terraA + terraB << " de terra\n";
                groups[numero_maior].pop_back();
                groups[numero_menor].pop_back();
                break;
            }
            ++numero_menor;
            if(numero_menor > numero_maior){
                break;
            }
        }

        if(achou) {
            continue;
        }

        if(!achou && groups[0].size() >= total_land ) {
            int somatoriaDo1{0};
            for(int i{groups[0].size() - 1}; i >= qtd_terra_ultimo_grupo; --i) {
                somatoriaDo1 += groups[0][i].second;
            }
            if(somatoriaDo1 > maior_ganho_possivel){
                for(int i{groups[0].size() - 1}; i >= qtd_terra_ultimo_grupo; --i) {
                    groups[0].pop_back();
                    total_land -= 1;
                }
                std::cout << "RegraDo1 removendo " << qtd_terra_ultimo_grupo << " de terra\n";

                total_earns += somatoriaDo1;
                continue;
            }
        }

        total_earns += maior_ganho_possivel;
        ultimo_grupo_disponivel.pop_back();
        total_land -= qtd_terra_ultimo_grupo;
        std::cout << "qtd_terra_ultimo_grupo removendo " << qtd_terra_ultimo_grupo << " de terra\n";
    }

    std::cout << "Sobrou isso de terra: " << total_land << '\n';
    return total_earns;
}

int main() {
    int total_land{ 36 };
    VectorPair space_and_earn_per_seed{ {3,86},{1,80},{3,71},{2,39},{2,53},{3,47},{2,46},{1,32},{1,69},{2,89},{4,58},{3,86},{3,54},{3,53},{1,64},{4,82},{1,46},{2,48},{4,53},{1,68},{3,94},{1,87} };
    std::vector<VectorPair> groups(4);

    populateGroups(space_and_earn_per_seed, groups);
    sortGroups(groups);

    int resultado { calculateEarns(groups, total_land) };
    std::cout << "Resultado: " << resultado << '\n';    
    return 0;
}