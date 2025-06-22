//
// Created by jadne on 22/06/2025.
//

#ifndef ORA_H
#define ORA_H


#include <iostream>
#include <stdexcept>

class Ora {
protected:
    int ore;
    int minuti;

public:
    Ora(int h = 0, int m = 0);

    int getOre() const {
        return ore;
    }

    void setOre(int ore) {
        this->ore = ore;
    }

    int getMinuti() const {
        return minuti;
    }

    void setMinuti(int minuti) {
        this->minuti = minuti;
    }

    int inMinuti() const;

    bool operator<(const Ora &other) const;

    bool operator>=(const Ora &other) const;
    int operator-(const Ora& altra) const;
};

#endif //ORA_H
