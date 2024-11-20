#include "mode.h"
#include <algorithm>
void DetailedCompetition::play(StrategyInterface *strategy1, StrategyInterface *strategy2, int n, map<string, int[3]> matrix)
{
    string player_inp;
    int count = 0;
    while (count < n)
    {
        cout<< "---------------------------------------------------------------------------------" << endl << endl;
        cout<<"choose your option \"C\" - stay silent  \"D\" - testifies"<< endl;
        cin >> player_inp; // d // c quit
        if (player_inp != "quit" && player_inp != "D" && player_inp != "C")
        {
            throw invalid_argument("invalid argument");
        }
        else if (player_inp == "quit")
        {
            cout << "game is finished";
            return;
        }
        else
        {
            // every strategy make its move
            char strategy1_move = strategy1->make_move(n, moves_vector, 2);
            char strategy2_move = strategy2->make_move(n, moves_vector, 3);
            // calculate point
            cout << "Move second player: " << strategy1_move << endl;
            cout << "Move third player: " << strategy2_move << endl;
            player_inp.push_back(strategy1_move);
            player_inp.push_back(strategy2_move);
            point_table[0] += matrix[player_inp][0];
            point_table[1] += matrix[player_inp][1];
            point_table[2] += matrix[player_inp][2];
            cout << "You give " << matrix[player_inp][0] << " point" << endl;
            cout << "Second player give " << matrix[player_inp][1] << " point" << endl;
            cout << "Third player give " << matrix[player_inp][2] << " point" << endl;
            // save report about moves
            moves_vector.push_back(player_inp);
        }
        count++;
    }
    auto max_it = max_element(point_table.begin(), point_table.end());
    int max_index = distance(point_table.begin(), max_it);
    cout<<endl<<"---------------------------------------------------" <<endl;
    cout << "Winner is " << max_index + 1 << " player!!!" << endl;

};

void WithoutDetail::play(StrategyInterface *strategy1, StrategyInterface *strategy2, StrategyInterface *strategy3, int n, map<string, int[3]> &matrix)
{
    string moves;
    int count = 0;
    while (count < n)
    {

        // every strategy make its move
        char strategy1_move = strategy1->make_move(n, moves_vector, 1);
        char strategy2_move = strategy2->make_move(n, moves_vector, 2);
        char strategy3_move = strategy3->make_move(n, moves_vector, 3);
        // calculate point
        moves.push_back(strategy1_move);
        moves.push_back(strategy2_move);
        moves.push_back(strategy3_move);
        point_table[0] += matrix[moves][0];
        point_table[1] += matrix[moves][1];
        point_table[2] += matrix[moves][2];

        // save report about moves
        moves_vector.push_back(moves);
        moves = "";

        count++;
    }
}
void WithoutDetail::print_winner(){
    auto max_it = max_element(point_table.begin(), point_table.end());
    int max_index = distance(point_table.begin(), max_it);
    cout << "Winner is " << max_index + 1 << " player!!!" << endl;
}
void Tournament::print_winner(){
    string winner_name;
    int winner_points = 0;
    for (auto it = prisoners_score.begin(); it != prisoners_score.end();++it){
        if (it->second >= winner_points){
            winner_name = it->first;
            winner_points = it->second;
        }
    }
    cout << "Winner is: " << winner_name << endl;
    // auto max_it = max_element(prisoners_score.begin(), prisoners_score.end());
    // int max_index = distance(prisoners_score.begin(), max_it);
    // cout << "Winner is " << max_index + 1 << " player!!!" << endl;

}
vector<int> WithoutDetail::get_point_table(){
    return point_table;
}

void Tournament::play(StrategyFactory &factory, int n, map<string, int[3]>& matrix)
{
    for (auto fac_it = factory.get_map().begin(); fac_it != factory.get_map().end(); ++fac_it)
    {
        prisoners_map[fac_it->first] = fac_it->second(); // take create function out from the Strategy factory and create prisoners with strategy
        prisoners_score[fac_it->first] = 0;
    }
    for (auto pris1_it = prisoners_map.begin(); pris1_it != prisoners_map.end(); ++pris1_it)
    {
        for (auto pris2_it = next(pris1_it, 1); pris2_it != prisoners_map.end(); ++pris2_it)
        {
            for (auto pris3_it = next(pris2_it, 1); pris3_it != prisoners_map.end(); ++pris3_it)
        {
            WithoutDetail game;
            game.play(pris1_it->second, pris2_it->second,pris3_it->second,n, matrix);
            prisoners_score[pris1_it->first] += game.get_point_table()[0];
            prisoners_score[pris2_it->first] += game.get_point_table()[1];
            prisoners_score[pris3_it->first] += game.get_point_table()[2];
            
        }
        }
    }
    cout << "competition finished the winner is ..." << endl;
    //вывод максимального элемента
}
