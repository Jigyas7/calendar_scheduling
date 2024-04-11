#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> 

struct Volunteer {
    std::string name;
    int choices[3];
};

void readVolunteers(std::vector<Volunteer>& volunteers) {
    std::ifstream inFile("volunteers.dat");
    Volunteer v;
    while (inFile >> v.name >> v.choices[0] >> v.choices[1] >> v.choices[2]) {
        volunteers.push_back(v);
    }
    inFile.close();
}

int evaluateAssignment(const std::vector<int>& months, const std::vector<Volunteer>& volunteers) {
    int score = 0;
    for (int i = 0; i < volunteers.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            if (months[i] == volunteers[i].choices[j]) {
                score += 3 - j; // 3 points for first choice, 2 for second, 1 for third
                break;
            }
        }
    }
    return score;
}

void findBestAssignment(const std::vector<Volunteer>& volunteers) {
    std::vector<int> months(12);
     std::iota(months.begin(), months.end(), 1); // Fill months with 1 to 12

    int maxScore = 0;
    std::vector<int> bestAssignment;

    do {
        int score = evaluateAssignment(months, volunteers);
        if (score > maxScore) {
            maxScore = score;
            bestAssignment = months;
            std::cout << "SCORE: " << maxScore << std::endl;
            for (int i = 0; i < bestAssignment.size(); ++i) {
                std::cout << bestAssignment[i] << " " << volunteers[i].name << std::endl;
            }
            std::cout << std::endl;
        }
    } while (std::next_permutation(months.begin(), months.end()));

    // Output the best assignment
    std::cout << "Best SCORE: " << maxScore << std::endl;
    for (int i = 0; i < bestAssignment.size(); ++i) {
        std::cout << "Month " << bestAssignment[i] << ": " << volunteers[i].name << std::endl;
    }
}

int main() {
    std::vector<Volunteer> volunteers;
    readVolunteers(volunteers);
    findBestAssignment(volunteers);
    return 0;
}