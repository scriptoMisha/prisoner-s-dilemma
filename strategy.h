#pragma once
#include <map>
#include <iostream>
#include <vector>

using namespace std;


class StrategyInterface
{
public:
    virtual char make_move(int n, vector<string> moves, int order) = 0;
    virtual ~StrategyInterface() {};
};

class SimpleStrategy1 : public StrategyInterface // always stay silent
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~SimpleStrategy1() override = default;
};
class SimpleStrategy2 : public StrategyInterface // alwa    ys testifies
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~SimpleStrategy2() override = default;
};

class SimpleStrategy3 : public StrategyInterface // through once
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~SimpleStrategy3() override = default;
};

class StrategyRandom : public StrategyInterface // through once
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~StrategyRandom() override = default;
};
class GrimTrigger : public StrategyInterface
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~GrimTrigger() override = default;

private:
    bool trigger = false;
};

class TitForTat : public StrategyInterface // око за око
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~TitForTat() override = default;
};
class TitForTatWithForgivness : public StrategyInterface // око за око
{
public:
    char make_move(int n, vector<string> moves, int order) override;
    ~TitForTatWithForgivness() override = default;

private:
    // тут внести чтение конфигурации из файла
    float probability_of_forgivness = 50;
};
typedef StrategyInterface *(*fInstantiator)();

//std::function
//std::callable

class StrategyFactory
{
public:
    template <class C>
    void add(const string &id)
    {
        auto it = FactoryMap.find(id);
        if (it == FactoryMap.end())
        {

            FactoryMap[id] = &instantiator<C>;
        }
        else
        {
            throw invalid_argument("this id have already been in factory");
            // exception
        }
    }
    template <class C>
    static StrategyInterface *instantiator()
    {
        return new C;
    }
    StrategyInterface *create(const string &id) const;
    map<string, fInstantiator> &get_map()
    {
        return FactoryMap;
    }

private:
    map<string, fInstantiator> FactoryMap;
};

// s- silent (молчит) t - testifies - (свидетельствует)
//  у стратегий есть ссылка на таблицу с ходами
