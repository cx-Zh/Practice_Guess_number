#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Hello.h"

using ::testing::Eq;
using ::testing::Return;

class MockRandomGenerator: public RandomGenerator {
public:
    MOCK_METHOD0(Generate, int());
};

TEST(lib, Case1)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    game.answer_ = {1, 2, 3, 4};

    auto result = game.Guess({1, 2, 3, 4});
    std::string expect = "4A0B";

    EXPECT_THAT(result, Eq(expect));
}

TEST(lib, Case2)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    game.answer_ = {1, 2, 3, 4};

    auto result = game.Guess({0,3,2,4});
    std::string expect = "1A2B";

    EXPECT_THAT(result, Eq(expect));
}

TEST(CheckInvalidInput, should_return_false_with_invalid_input1)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    bool result = game.CheckInvalidInput("1 2 3");
    bool expect = false;

    EXPECT_THAT(result, Eq(expect));
}

TEST(CheckInvalidInput, should_return_false_with_invalid_input2)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    bool result = game.CheckInvalidInput("1 1 2 3");
    bool expect = false;

    EXPECT_THAT(result, Eq(expect));
}

TEST(CheckInvalidInput, should_return_false_with_invalid_input3)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    bool result = game.CheckInvalidInput("1 1 2 10");
    bool expect = false;

    EXPECT_THAT(result, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result1)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{4}, {2,3}};
    std::string instruction = game.TransferInstruction("1A2B", right_wrong_position);
    std::string expect = "4 correct, 2 and 3 wrong position";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result1_1)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{1,2,3}};
    std::string instruction = game.TransferInstruction("3A0B", right_wrong_position);
    std::string expect = "1, 2 and 3 correct";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result2)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{1,2,3,4}, {}};
    std::string instruction = game.TransferInstruction("4A0B", right_wrong_position);
    std::string expect = "win, all correct";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result3)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{},{}};
    std::string instruction = game.TransferInstruction("0A0B", right_wrong_position);
    std::string expect = "all wrong";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result4)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{1}, {}};
    std::string instruction = game.TransferInstruction("1A0B", right_wrong_position);
    std::string expect = "1 correct";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(TransferInstruction, should_return_instruction_with_result5)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);
    std::vector<std::vector<int>> right_wrong_position = {{},{1,2,3,4}};
    std::string instruction = game.TransferInstruction("0A4B", right_wrong_position);
    std::string expect = "4 numbers position wrong";

    EXPECT_THAT(instruction, Eq(expect));
}

TEST(lib2, Case2)
{
    MockRandomGenerator mockRandomGenerator;
    GuessNumberGame game(mockRandomGenerator);
    EXPECT_CALL(mockRandomGenerator, Generate())
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(3))
        .WillOnce(Return(4));

    game.GenerateNumbers();

    std::array<int, 4> expect{1, 2, 3, 4};
    EXPECT_THAT(game.answer_, Eq(expect));
}

TEST(lib2, Case3)
{
    MockRandomGenerator mockRandomGenerator;
    GuessNumberGame game(mockRandomGenerator);
    EXPECT_CALL(mockRandomGenerator, Generate())
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(2))
        .WillOnce(Return(3))
        .WillOnce(Return(4));

    game.GenerateNumbers();

    std::array<int, 4> expect{1, 2, 3, 4};
    EXPECT_THAT(game.answer_, Eq(expect));
}

TEST(lib2, Case4)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    game.GenerateNumbers();

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            EXPECT_THAT(game.answer_[i], testing::Ne(game.answer_[j]));
        }
    }
}

TEST(GetWrongPosition, should_get_right_and_wrong_position_with_input)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    game.answer_ = {1, 2, 3, 4};

    auto result = game.GetRightAndWrongPosition({0, 3, 2, 4});
    std::vector<std::vector<int>> expect = {{4}, {2,3}};

    EXPECT_THAT(result, Eq(expect));
}

TEST(InitializePlayerInput, should_get_array_with_player_input)
{
    RandomGenerator generator;
    GuessNumberGame game(generator);

    std::string input = "1 2 3  9";
    auto result = game.InitializePlayerInput(input);

    std::array<int, 4> expect = {1,2,3,9};
    EXPECT_THAT(result, Eq(expect));
}

//TODO: When answer is random, cannot have a fixed expected result.
//TEST(PlayGames, should_return_all_result)
//{
//    RandomGenerator generator;
//    GuessNumberGame game(generator);
//
//    std::string result = game.PlayGames("4 3 2 1");
//    std::string expect = "0A1B 3 wrong position";
//
//    EXPECT_THAT(result, Eq(expect));
//}