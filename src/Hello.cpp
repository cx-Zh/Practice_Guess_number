#include "Hello.h"

std::string GuessNumberGame::Guess(const std::array<int, 4>& digits)
{
    int A = 0;
    int B = 0;
    std::string result = "";
//    std::vector<int> wrong_position;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(digits[i] == this->answer_[j]){
                if(i == j){
                    A += 1;
                }
                else{
                    B += 1;
                }
            }
        }
    }
    result += std::to_string(A) + "A" + std::to_string(B) + "B";

    return result;
}

std::vector<std::vector<int>> GuessNumberGame::GetRightAndWrongPosition(const std::array<int, 4>& digits){
    std::vector<std::vector<int>> right_wrong_position = {{},{}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(digits[i] == this->answer_[j]){
                if(i == j){
                    right_wrong_position[0].push_back(digits[i]);
                }
                else{
                    right_wrong_position[1].push_back(digits[i]);
                }
            }
        }
    }
//    for(auto & iter : right_wrong_position[0]){
//        std::cout<<iter<<std::endl;
//    }
//    for(auto & iter : right_wrong_position[1]){
//        std::cout<<iter<<std::endl;
//    }
    std::sort(right_wrong_position[0].begin(), right_wrong_position[0].end());
    std::sort(right_wrong_position[1].begin(), right_wrong_position[1].end());
    return right_wrong_position;
}

bool GuessNumberGame::CheckInvalidInput(std::string input){
    std::stringstream ss(input);
    std::vector<int> input_v;
    std::set<int> check_list = {1,2,3,4,5,6,7,8,9,0};
    int x;
    while(ss >> x){
        input_v.push_back(x);
    }

    if(input_v.size()!=4){
        return false;
    }
    for(auto & iter: input_v){
        if(check_list.find(iter)!=check_list.end()){
            check_list.erase(iter);
        }
        else{
            return false;
        }
    }

    return true;
}

std::string GuessNumberGame::TransferInstruction(std::string result, std::vector<std::vector<int>> right_wrong_position) {
    std::string instruction = "";
    int A = (int)result[0] - (int)'0';
    int B = (int)result[2] - (int)'0';

    if(A != 0){
        switch(A){
        case 1:
            instruction += std::to_string(right_wrong_position[0][0]) + " correct";
            break;
        case 2:
            instruction += std::to_string(right_wrong_position[0][0]) + " and " +
                           std::to_string(right_wrong_position[0][1]) + " correct";
            break;
        case 3:
            instruction += std::to_string(right_wrong_position[0][0]) + ", " +
                           std::to_string(right_wrong_position[0][1]) + " and " +
                           std::to_string(right_wrong_position[0][2]) + " correct";
            break;
        case 4:
            instruction += "win, all correct";
            break;
        }
    }
    if(B != 0){
        if(A != 0){
            instruction += ", ";
        }

        switch(B){
        case 1:
            instruction += std::to_string(right_wrong_position[1][0]) + " wrong position";
            break;
        case 2:
            instruction += std::to_string(right_wrong_position[1][0]) + " and " +
                           std::to_string(right_wrong_position[1][1]) + " wrong position";
            break;
        case 3:
            instruction += std::to_string(right_wrong_position[1][0]) + ", " +
                           std::to_string(right_wrong_position[1][1]) + " and " +
                           std::to_string(right_wrong_position[1][2]) + " wrong position";
            break;
        case 4:
            instruction += "4 numbers position wrong";
            break;
        }
    }

    if (instruction == ""){
        instruction = "all wrong";
    }
    return instruction;
}

std::string GuessNumberGame::PlayGames(std::string input) {
    this->GenerateNumbers();
    if(!CheckInvalidInput(input)){
        return "Wrong Input，Input again";
    }
    auto player_input = InitializePlayerInput(input);
    std::string result = Guess(player_input);
    std::vector<std::vector<int>> right_wrong_position = GetRightAndWrongPosition(player_input);
    std::string instruction = TransferInstruction(result, right_wrong_position);

    return result + " " + instruction;
}

std::array<int, 4> GuessNumberGame::InitializePlayerInput(std::string input){
    std::array<int, 4> player_input = {};
    std::stringstream ss(input);
    int x;
    int i = 0;
    while(ss >> x){
        player_input[i] = x;
        i++;
    }
    return player_input;
}

GuessNumberGame::GuessNumberGame(RandomGenerator& generator) : generator(generator), answer_({0, 0, 0, 0})
{
}
void GuessNumberGame::GenerateNumbers()
{
    std::set<int> check_list = {1,2,3,4,5,6,7,8,9,0};
    int i = 0;
    while(check_list.size() != 6){
        int generate_num = this->generator.Generate();
        if(check_list.find(generate_num)!=check_list.end()){
            check_list.erase(generate_num);
            this->answer_[i] = generate_num;
            i++;
        }
    }
//    std::cout<<this->answer_[0]<<std::endl;
}

int RandomGenerator::Generate()
{
    std::uniform_int_distribution<> u(0, 9);
    std::random_device r;
    std::default_random_engine engine(r());
    return u(engine);
}