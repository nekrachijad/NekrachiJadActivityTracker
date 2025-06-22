//
// Created by jadne on 22/06/2025.
//

#ifndef ACTIVITY_H
#define ACTIVITY_H


#include "Date.h"
#include <iostream>
#include "Ora.h"

class Activity {
protected:
    std::string description;
    Ora inizio;
    Ora fine;
    Date data;

public:
    Activity(std::string description, Ora inizio, Ora fine, Date data);

    Activity()=default;

    std::string getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        this->description = description;
    }

    Ora getInizio() const {
        return inizio;
    }

    void setInizio(const Ora &inizio) {
        this->inizio = inizio;
    }

    Ora getFine() const {
        return fine;
    }

    void setFine(const Ora &fine) {
        if ((fine - inizio) < 0) {
            throw std::invalid_argument("L'ora di inizio non  può essere maggiore di quella di fine");
        }
        this->fine = fine;
    }

    Date getData() const {
        return data;
    }

    void setData(const Date &data) {
        this->data = data;
    }
};


#endif //ACTIVITY_H
