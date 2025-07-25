//
// Created by jadne on 22/06/2025.
//

#include "Activity.h"
int Activity::nextId = 1;

Activity::Activity(std::string description, Time inizio, Time fine, Date data)
    : id(nextId++),description(description), start(inizio), end(fine), data(data) {
    if ((fine - inizio) < 0) {
        throw std::invalid_argument("L'ora di inizio non può essere maggiore di quella di fine");
    }
    if (description.empty()) {
        throw std::invalid_argument("La descrizione non può essere vuota");
    }
}

void Activity::setEnd(const Time &fine) {
    if ((fine - start) < 0) {
        throw std::invalid_argument("L'ora di inizio non  può essere maggiore di quella di fine");
    }
    this->end = fine;
}

