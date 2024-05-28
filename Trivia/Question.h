#pragma once
#include <iostream>
#include <vector>

class Question {
private:
    std::string m_question;
    std::vector<std::string> m_possibleAnswers;

public:
    Question(std::string question, std::vector<std::string> possibleAnswers) :
        m_question(question), m_possibleAnswers(possibleAnswers) {}

    std::string getQuestion() {
        return m_question;
    }

    std::vector<std::string> getPossibleAnswers() {
        return m_possibleAnswers;
    }

    //for now first answer is the right
    int getCorrectAnswerId() {
        return 0;
    }
};
