#include "simulation.h"
#include "strategy.h"
#include <fstream>

Simulator::Simulator() : n(5)
{
    // adding all strategys in factory
    parse_matrix();
    factory.add<SimpleStrategy1>("strategy1");
    factory.add<SimpleStrategy2>("strategy2");
    factory.add<SimpleStrategy3>("strategy3");
    factory.add<StrategyRandom>("strategyRandom");
    factory.add<GrimTrigger>("GrimTrigger");
    factory.add<TitForTat>("TitForTat");
    factory.add<TitForTatWithForgivness>    ("TitForTatWithForgivness");
}
Simulator::Simulator(int N) : Simulator()
{
    n = N;
}

void Simulator::print_strategys()
{
    for (auto it = factory.get_map().begin(); it != factory.get_map().end(); ++it)
    {
        cout << "- " << it->first << endl;
    }
}
void Simulator::simulation() // 3 стратегии
{
    parse_matrix();
    // simulator mode:
    //     1 = DetailedCompetition
    //     2  = WithoutDetail
    //     3 = Tournament
    string user_in = "";
    while (user_in != "quit")
    {
        cout << "menu" << endl;
        cout << "choose mode:" << endl;
        cout << "1 = DetailedCompetition" << endl;
        cout << "2  = WithoutDetail" << endl;
        cout << "3 = Tournament" << endl;
        cin >> user_in;
        // exception
        if (user_in == "1")
        {
            cout << "choose 2 strategys which will compete with you" << endl;
            // здесь должен быть список стратегий
            // надо создать фабрику и вывести все ключи
            cout << "list available strategys: " << endl;
            print_strategys();
            string name1;
            string name2;
            cin >> name1;
            cin >> name2;
            unique_ptr<StrategyInterface> strat1 = factory.create(name1);
            unique_ptr<StrategyInterface> strat2 = factory.create(name2);
            // exception
            DetailedCompetition comp;
            comp.play(strat1, strat2, n, matrix);
            // print strategys
        }
        else if (user_in == "2")
        {
            cout << "choose 3 strategys which will compete between each other";
            cout << "list available strategys: " << endl;
            print_strategys();
            string name1;
            string name2;
            string name3;
            cin >> name1;
            cin >> name2;
            cin >> name3;
            unique_ptr<StrategyInterface> strat1 = factory.create(name1);
            unique_ptr<StrategyInterface> strat2 = factory.create(name2);
            unique_ptr<StrategyInterface> strat3 = factory.create(name3);
            // exception
            WithoutDetail comp;
            comp.play(strat1, strat2, strat3, n, matrix);
            comp.print_winner();
            // print strategys
        }
        else if (user_in == "3")
        {
            Tournament comp;
            comp.play(factory, n, matrix);
            comp.print_winner();
        }
    }
    cout << "game is over" << endl;
}

void Simulator::parse_matrix()
{
    string line;

    ifstream in("matrix.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            // erase all spaces
            for (int i = 0; i < line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    line.erase(i, 1);
                    --i;
                }
            }
            string str;
            str.push_back(line[0]);
            str.push_back(line[1]);
            str.push_back(line[2]);
            matrix[str][0] = line[3] - '0';
            matrix[str][1] = line[4] - '0';
            matrix[str][2] = line[5] - '0';
        }
    }
    in.close(); // закрываем файл
}
