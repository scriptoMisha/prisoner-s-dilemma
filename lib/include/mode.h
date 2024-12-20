#pragma once
#include "strategy.h"

class DetailedCompetition
{
public:
    DetailedCompetition()
    {
        point_table = {0, 0, 0};
    }
    // player competes with 2 strategys
    void play(unique_ptr<StrategyInterface>& strategy1,unique_ptr<StrategyInterface>& strategy2, int n, map<string, int[3]> matrix);

private:
    vector<string> moves_vector;
    vector<int> point_table;
};

class WithoutDetail
{
public:
    WithoutDetail()
    {
        point_table = {0, 0, 0};
    }
    void play(unique_ptr<StrategyInterface>& strategy1, unique_ptr<StrategyInterface>& strategy2, unique_ptr<StrategyInterface>& strategy3, int n, map<string, int[3]> &matrix);
    void print_winner();
    vector<int> get_point_table();

private:
    vector<string> moves_vector;
    vector<int> point_table;
};

class Tournament
{
public:
    Tournament()
    {
    }
    void play(StrategyFactory &factory, int n, map<string, int[3]> &matrix);
    void print_winner();

private:
    vector<string> moves_vector;
    map<string, unique_ptr<StrategyInterface>> prisoners_map;
    map<string, int> prisoners_score;
};
