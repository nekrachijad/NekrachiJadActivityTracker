//
// Created by jadne on 26/06/2025.
//


#ifndef ACTIVITYWINDOW_H
#define ACTIVITYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include "ActivityList.h"

class ActivityWindow : public QWidget {
    Q_OBJECT

public:
    ActivityWindow(QWidget *parent = nullptr);

private:
    ActivityList activityList;
    QLabel *actionLabel;

    void setupUI();
    void connectButtons();

    void aggiungiAttivita();
    void mostraAttivitaPerData();
    void rimuoviAttivita();
    void modificaAttivita();
};

#endif // ACTIVITYWINDOW_H


