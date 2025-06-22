//
// Created by jadne on 22/06/2025.
//

#include "Ora.h"

Ora::Ora(int h, int m) {
    if (h < 0 || h > 23 || m < 0 || m > 59)
        throw std::invalid_argument("Ora non valida");

    ore = h;
    minuti = m;
}

int Ora::inMinuti() const {
    return ore * 60 + minuti;
}

bool Ora::operator<(const Ora &other) const {
    return inMinuti() < other.inMinuti();
}

bool Ora::operator>=(const Ora &other) const {
    return inMinuti() >= other.inMinuti();
}

inline int Ora::operator-(const Ora &altra) const {
    return this->inMinuti() - altra.inMinuti();
}
