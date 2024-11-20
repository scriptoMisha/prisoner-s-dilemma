#pragma once
#include "strategy.h"
#include "mode.h"
class Simulator
{
public:
    Simulator();
    Simulator(int N);
    void parse_matrix();
    void simulation();
    void print_strategys();

private:
    int n;
    map<string, int[3]> matrix;
    StrategyFactory factory;
};