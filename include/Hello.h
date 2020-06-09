#ifndef __HELLO_H__
#define __HELLO_H__

#include <array>
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <random>

class RandomGenerator {
public:
    virtual ~RandomGenerator() = default;
    virtual int Generate();
};

class GuessNumberGame
{
    RandomGenerator &generator;
public:
    std::string Guess(const std::array<int, 4>& digits);
    std::array<int, 4> answer_;
    bool CheckInvalidInput(std::string input);
    std::string TransferInstruction(std::string result, std::vector<std::vector<int>> right_wrong_position);
    GuessNumberGame(RandomGenerator& generator);
    void GenerateNumbers();
    std::vector<std::vector<int>> GetRightAndWrongPosition(const std::array<int, 4>& digits);
    std::string PlayGames(std::string input);
    std::array<int, 4> InitializePlayerInput(std::string input);
};
#endif
