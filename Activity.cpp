//
// Created by jadne on 22/06/2025.
//

#include "Activity.h"

Activity::Activity(std::string description, Ora inizio, Ora fine, Date data)
        : description(std::move(description)), inizio(inizio), fine(fine), data(data) {
    if ((fine - inizio) < 0) {
        throw std::invalid_argument("L'ora di inizio non può essere maggiore di quella di fine");
    }
}

