#include <gtest/gtest.h>
#include "strategy.h"
#include "simulation.h"
#include "mode.h"

TEST(prisonersDilemma, simpleTest1)
{
    Simulator sim;
    // подмена потока ввода
    std::string input = "quit";
    std::istringstream input_stream(input);
    std::streambuf *original_cin = std::cin.rdbuf(input_stream.rdbuf());

    // подмена потока вывода
    std::ostringstream output_stream;
    std::streambuf *original_cout = std::cout.rdbuf(output_stream.rdbuf());

    sim.simulation();

    // восcтановление стандартного вывода
    std::cout.rdbuf(original_cout);

    // восстановление стандартного ввода
    std::cin.rdbuf(original_cin);

    EXPECT_EQ("menu\nchoose mode:\n1 = DetailedCompetition\n2  = WithoutDetail\n3 = Tournament\ngame is over\n", output_stream.str());
}
TEST(prisonersDilemma, simpleTest2)
{
    Simulator sim;
    // подмена потока ввода
    std::string input = "3 quit";
    std::istringstream input_stream(input);
    std::streambuf *original_cin = std::cin.rdbuf(input_stream.rdbuf());

    // подмена потока вывода
    std::ostringstream output_stream;
    std::streambuf *original_cout = std::cout.rdbuf(output_stream.rdbuf());

    sim.simulation();

    // восcтановление стандартного вывода
    std::cout.rdbuf(original_cout);

    // восстановление стандартного ввода
    std::cin.rdbuf(original_cin);
}