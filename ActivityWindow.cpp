//
// Created by jadne on 26/06/2025.
//

#include "ActivityWindow.h"

#include "ActivityWindow.h"
#include <QApplication>
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QInputDialog>

ActivityWindow::ActivityWindow(QWidget *parent)
    : QWidget(parent) {

    setWindowTitle("ActivityTracker");
    resize(1200, 700);

    setupUI();
}

void ActivityWindow::setupUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout();

    QLabel *titleLabel = new QLabel("Benvenuto nel tuo Registro Attività!");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Seleziona un'opzione per continuare:");
    subtitle->setStyleSheet("font-size: 22px; font-weight: bold;");

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *buttonLayout = new QVBoxLayout();

    QPushButton *addButton = new QPushButton("Aggiungi una nuova attività");
    QPushButton *showButton = new QPushButton("Mostra attività per una data");
    QPushButton *removeButton = new QPushButton("Rimuovi un'attività");
    QPushButton *modifyButton = new QPushButton("Modifica un'attività");
    QPushButton *exitButton = new QPushButton("Esci");

    QList<QPushButton*> buttons = { addButton, showButton, removeButton, modifyButton, exitButton };
    for (auto btn : buttons) {
        btn->setStyleSheet("font-size: 16px;");
        buttonLayout->addWidget(btn);
    }

    actionLabel = new QLabel("Qui verrà mostrata l'azione selezionata.");
    actionLabel->setStyleSheet("font-size: 18px; color: #333; background-color: #f0f0f0; padding: 10px; border: 1px solid #ccc;");
    actionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    actionLabel->setWordWrap(true);

    // Connessioni
    connect(addButton, &QPushButton::clicked, this, &ActivityWindow::aggiungiAttivita);
    connect(showButton, &QPushButton::clicked, this, &ActivityWindow::mostraAttivitaPerData);
    connect(removeButton, &QPushButton::clicked, this, &ActivityWindow::rimuoviAttivita);
    connect(modifyButton, &QPushButton::clicked, this, &ActivityWindow::modificaAttivita);
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(subtitle);
    leftLayout->addWidget(line);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(actionLabel);

    setLayout(mainLayout);
}

void ActivityWindow::aggiungiAttivita() {
    QDialog dialog(this);
    dialog.setWindowTitle("Aggiungi Attività");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *descLabel = new QLabel("Descrizione:");
    QTextEdit *descEdit = new QTextEdit();
    descEdit->setMinimumHeight(100);
    descEdit->setPlaceholderText("Inserisci qui la descrizione dettagliata...");

    QLabel *dateLabel = new QLabel("Data:");
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    QLabel *startLabel = new QLabel("Ora Inizio:");
    QTimeEdit *startTimeEdit = new QTimeEdit(QTime::currentTime());

    QLabel *endLabel = new QLabel("Ora Fine:");
    QTimeEdit *endTimeEdit = new QTimeEdit(QTime::currentTime().addSecs(3600));

    QPushButton *okButton = new QPushButton("Aggiungi");
    QPushButton *cancelButton = new QPushButton("Annulla");

    layout->addWidget(descLabel);
    layout->addWidget(descEdit);
    layout->addWidget(dateLabel);
    layout->addWidget(dateEdit);
    layout->addWidget(startLabel);
    layout->addWidget(startTimeEdit);
    layout->addWidget(endLabel);
    layout->addWidget(endTimeEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, [&]() {
        QString desc = descEdit->toPlainText();
        QDate qdate = dateEdit->date();
        QTime qstart = startTimeEdit->time();
        QTime qend = endTimeEdit->time();

        try {
            Activity nuova(desc.toStdString(),
                           Time(qstart.hour(), qstart.minute()),
                           Time(qend.hour(), qend.minute()),
                           Date(qdate.day(), qdate.month(), qdate.year()));

            activityList.addActivity(nuova);
            actionLabel->setText("Attività aggiunta con successo.");
            dialog.accept();
        } catch (std::invalid_argument &e) {
            actionLabel->setText("Errore: " + QString::fromStdString(e.what()));
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void ActivityWindow::mostraAttivitaPerData() {
    QDialog dialog(this);
    dialog.setWindowTitle("Mostra Attività");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *dateLabel = new QLabel("Seleziona la data:");
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    QPushButton *okButton = new QPushButton("Mostra");
    QPushButton *cancelButton = new QPushButton("Annulla");

    layout->addWidget(dateLabel);
    layout->addWidget(dateEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, [&]() {
        QDate qdate = dateEdit->date();
        Date d(qdate.day(), qdate.month(), qdate.year());
        auto activities = activityList.getActivitiesByDate(d);

        if (activities.empty()) {
            actionLabel->setText("Nessuna attività trovata per questa data.");
        } else {
            QString msg = "Attività per " + QString::number(qdate.day()) + "/" +
                          QString::number(qdate.month()) + "/" +
                          QString::number(qdate.year()) + ":\n";

            for (const auto &act : activities) {
                msg += "- " + QString::fromStdString(act.getDescription()) + " [" +
                       QString::number(act.getStart().getHours()) + ":" +
                       QString::number(act.getStart().getMinutes()).rightJustified(2, '0') + " - " +
                       QString::number(act.getEnd().getHours()) + ":" +
                       QString::number(act.getEnd().getMinutes()).rightJustified(2, '0') + "]\n";
            }
            actionLabel->setText(msg);
        }
        dialog.accept();
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void ActivityWindow::rimuoviAttivita() {
    if (activityList.getAllActivities().empty()) {
        actionLabel->setText("Non ci sono attività da rimuovere.");
        return;
    }

    bool ok;
    QString descToRemove = QInputDialog::getText(this, "Rimuovi Attività",
                                                 "Inserisci la descrizione esatta dell'attività da rimuovere:",
                                                 QLineEdit::Normal, "", &ok);

    if (ok && !descToRemove.isEmpty()) {
        activityList.removeActivity(descToRemove.toStdString());
        actionLabel->setText("Se l'attività esisteva, è stata rimossa.");
    }
}

void ActivityWindow::modificaAttivita() {
    auto allActivities = activityList.getAllActivities();
    if (allActivities.empty()) {
        actionLabel->setText("Non ci sono attività da modificare.");
        return;
    }

    QStringList items;
    for (const auto &act : allActivities) {
        QString desc = QString::fromStdString(act.getDescription()) + " [" +
                       QString::number(act.getData().getDay()) + "/" +
                       QString::number(act.getData().getMonth()) + "/" +
                       QString::number(act.getData().getYear()) + " " +
                       QString::number(act.getStart().getHours()) + ":" +
                       QString::number(act.getStart().getMinutes()).rightJustified(2, '0') + " - " +
                       QString::number(act.getEnd().getHours()) + ":" +
                       QString::number(act.getEnd().getMinutes()).rightJustified(2, '0') + "]";

        items << desc;
    }

    bool ok;
    QString selected = QInputDialog::getItem(this, "Modifica Attività",
                                             "Seleziona attività da modificare:", items, 0, false, &ok);

    if (ok && !selected.isEmpty()) {
        int index = items.indexOf(selected);
        const Activity &oldActivity = allActivities[index];

        QDialog dialog(this);
        dialog.setWindowTitle("Modifica Attività");

        QVBoxLayout *layout = new QVBoxLayout(&dialog);

        QLabel *descLabel = new QLabel("Descrizione:");
        QLineEdit *descEdit = new QLineEdit(QString::fromStdString(oldActivity.getDescription()));

        QLabel *dateLabel = new QLabel("Data:");
        QDateEdit *dateEdit = new QDateEdit(QDate(oldActivity.getData().getYear(),
                                                  oldActivity.getData().getMonth(),
                                                  oldActivity.getData().getDay()));
        dateEdit->setCalendarPopup(true);

        QLabel *startLabel = new QLabel("Ora Inizio:");
        QTimeEdit *startTimeEdit = new QTimeEdit(QTime(oldActivity.getStart().getHours(),
                                                       oldActivity.getStart().getMinutes()));

        QLabel *endLabel = new QLabel("Ora Fine:");
        QTimeEdit *endTimeEdit = new QTimeEdit(QTime(oldActivity.getEnd().getHours(),
                                                     oldActivity.getEnd().getMinutes()));

        QPushButton *okButton = new QPushButton("Salva");
        QPushButton *cancelButton = new QPushButton("Annulla");

        layout->addWidget(descLabel);
        layout->addWidget(descEdit);
        layout->addWidget(dateLabel);
        layout->addWidget(dateEdit);
        layout->addWidget(startLabel);
        layout->addWidget(startTimeEdit);
        layout->addWidget(endLabel);
        layout->addWidget(endTimeEdit);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addLayout(buttonLayout);

        connect(okButton, &QPushButton::clicked, [&]() {
            QString desc = descEdit->text();
            QDate qdate = dateEdit->date();
            QTime qstart = startTimeEdit->time();
            QTime qend = endTimeEdit->time();

            try {
                Activity nuova(desc.toStdString(),
                               Time(qstart.hour(), qstart.minute()),
                               Time(qend.hour(), qend.minute()),
                               Date(qdate.day(), qdate.month(), qdate.year()));

                activityList.modifyActivity(index, nuova);
                actionLabel->setText("Attività modificata con successo.");
                dialog.accept();
            } catch (std::invalid_argument &e) {
                actionLabel->setText("Errore: " + QString::fromStdString(e.what()));
            }
        });

        connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

        dialog.exec();
    }
}
