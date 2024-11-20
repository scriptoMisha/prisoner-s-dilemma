#include "strategy.h"
#include <random>
using namespace std;

char SimpleStrategy1::make_move(int n, vector<string> moves, int order)
{
    return 'C';
};
char SimpleStrategy2::make_move(int n, vector<string> moves, int order)
{
    return 'D';
};
char SimpleStrategy3::make_move(int n, vector<string> moves, int order)
{
    int count = moves.size(); // moves count
    if (count % 2 == 0)
    {
        return 'D';
    }
    else
    {
        return 'C';
    }
};
char StrategyRandom::make_move(int n, vector<string> moves, int order)
{
    vector<char> choice{'C', 'D'};
    int random = rand() % 2;
    return choice[random];
}
char GrimTrigger::make_move(int n, vector<string> moves, int order)
{
    if (trigger)
    {
        return 'D';
    }
    int count = moves.size();
    string report;
    if (count > 0)
    {
        report = moves[count - 1];
        for (int i = 1; i < 4; i++)
        {
            if (i != order && report[i - 1] == 'D')
            {
                trigger = true;
                return 'D';
            }
        }
    }
    return 'C';
}

char TitForTat::make_move(int n, vector<string> moves, int order)
{
    int count = moves.size();
    string report;
    if (count > 0)
    {
        report = moves[count - 1];
        for (int i = 1; i < 4; i++)
        {
            if (i != order && report[i - 1] == 'D')
            {
                return 'D';
            }
        }
    }
    return 'C';
}
char TitForTatWithForgivness::make_move(int n, vector<string> moves, int order)
{
    int count = moves.size();
    string report;
    if (count > 0)
    {
        report = moves[count - 1];
        for (int i = 1; i < 4; i++)
        {
            if (i != order && report[i - 1] == 'D')
            {
                // Initialize a random number generator
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distrib(1, 100);
                int random_value = distrib(gen);

                char result;
                if (random_value > probability_of_forgivness)
                {
                    return 'D';
                }
                else
                {
                    return 'C';
                }
            }
        }
    }
    return 'C';
}


StrategyInterface *StrategyFactory::create(const string &id) const
{
    auto it = FactoryMap.find(id);
    if (it != FactoryMap.end())
    {
        return it->second();
    }
    else
    {
        return nullptr;
        // exception
    }
}

// С- silent (молчит) D - testifies - (свидетельствует)
