#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QTextEdit>
#include <QInputDialog>

#include "Date.h"
#include "Time.h"
#include "Activity.h"
#include "ActivityList.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Registro attività globale
    ActivityList activityList;

    QWidget window;
    window.setWindowTitle("ActivityTracker");
    window.resize(1200, 700);

    QHBoxLayout *mainLayout = new QHBoxLayout(&window);
    QVBoxLayout *leftLayout = new QVBoxLayout();

    QLabel *titleLabel = new QLabel("Benvenuto nel tuo Registro Attività!");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Seleziona un'opzione per continuare:");
    subtitle->setStyleSheet("font-size: 22px; font-weight: bold;");
    //subtitle->setAlignment(Qt::AlignCenter);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *buttonLayout = new QVBoxLayout();

    QLabel *actionLabel = new QLabel("Qui verrà mostrata l'azione selezionata.");
    actionLabel->setStyleSheet(
        "font-size: 18px; color: #333; background-color: #f0f0f0; padding: 10px; border: 1px solid #ccc;");
    actionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    actionLabel->setWordWrap(true);

    // Funzione per creare un bottone
    auto createButton = [&](const QString &text, std::function<void()> callback) {
        QPushButton *btn = new QPushButton(text);
        //btn->setMinimumHeight(40);
        //btn->setMaximumWidth(400);
        btn->setStyleSheet("font-size: 16px;");
        QObject::connect(btn, &QPushButton::clicked, callback);
        buttonLayout->addWidget(btn);
    };

    // === Aggiungi attività ===============================================================================
    createButton("Aggiungi una nuova attività", [&]() {
        QDialog dialog(&window);
        dialog.setWindowTitle("Aggiungi Attività");

        // Dimensione finestra circa 60% della finestra principale
        dialog.resize(window.width() * 0.6, window.height() * 0.6);

        QVBoxLayout *layout = new QVBoxLayout(&dialog);

        // Descrizione
        QLabel *descLabel = new QLabel("Descrizione:");
        QTextEdit *descEdit = new QTextEdit();
        descEdit->setMinimumHeight(100); // Più grande in altezza
        descEdit->setPlaceholderText("Inserisci qui la descrizione dettagliata...");

        // Data
        QLabel *dateLabel = new QLabel("Data:");
        QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
        dateEdit->setCalendarPopup(true);

        // Ora inizio
        QLabel *startLabel = new QLabel("Ora Inizio:");
        QTimeEdit *startTimeEdit = new QTimeEdit(QTime::currentTime());

        // Ora fine
        QLabel *endLabel = new QLabel("Ora Fine:");
        QTimeEdit *endTimeEdit = new QTimeEdit(QTime::currentTime().addSecs(3600)); // Default +1 ora

        // Pulsanti
        QPushButton *okButton = new QPushButton("Aggiungi");
        QPushButton *cancelButton = new QPushButton("Annulla");

        // Layout componenti
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

        QObject::connect(okButton, &QPushButton::clicked, [&]() {
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

        QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

        dialog.exec();
    });


    // === Mostra attività per una data =====================================================================
    createButton("Mostra attività per una data", [&]() {
        QDialog dialog(&window);
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

        QObject::connect(okButton, &QPushButton::clicked, [&]() {
            QDate qdate = dateEdit->date();
            Date d(qdate.day(), qdate.month(), qdate.year());
            auto activities = activityList.getActivitiesByDate(d);

            if (activities.empty()) {
                actionLabel->setText("Nessuna attività trovata per questa data.");
            } else {
                QString msg = "Attività per " + QString::number(qdate.day()) + "/" +
                              QString::number(qdate.month()) + "/" +
                              QString::number(qdate.year()) + ":\n";

                for (const auto &act: activities) {
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

        QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

        dialog.exec();
    });



    // === Rimuovi un'attività ========================================================================
    createButton("Rimuovi un'attività", [&]() {
    if (activityList.getAllActivities().empty()) {
        actionLabel->setText("Non ci sono attività da rimuovere.");
        return;
    }

    QStringList items;
    for (size_t i = 0; i < activityList.getAllActivities().size(); ++i) {
        const Activity& act = activityList.getAllActivities()[i];
        QString desc = QString::fromStdString(act.getDescription()) + " [" +
                       QString::number(act.getData().getDay()) + "/" +
                       QString::number(act.getData().getMonth()) + "/" +
                       QString::number(act.getData().getMonth()) + " " +
                       QString::number(act.getStart().getHours()) + ":" +
                       QString::number(act.getStart().getMinutes()).rightJustified(2, '0') + " - " +
                       QString::number(act.getEnd().getHours()) + ":" +
                       QString::number(act.getEnd().getMinutes()).rightJustified(2, '0') + "]";
        items << desc;
    }

    bool ok;
    QString selected = QInputDialog::getItem(&window, "Rimuovi Attività",
                                             "Seleziona attività da rimuovere:", items, 0, false, &ok);

    if (ok && !selected.isEmpty()) {
        int index = items.indexOf(selected);
        activityList.removeActivity(index);
        actionLabel->setText("Attività rimossa con successo.");
    }
});

    // === Rimuovi un'attività ===========================================================================


    createButton("Modifica un'attività", [&]() {
    if (activityList.getAllActivities().empty()) {
        actionLabel->setText("Non ci sono attività da modificare.");
        return;
    }

    QStringList items;
    for (size_t i = 0; i < activityList.getAllActivities().size(); ++i) {
        const Activity& act = activityList.getAllActivities()[i];
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
    QString selected = QInputDialog::getItem(&window, "Modifica Attività",
                                             "Seleziona attività da modificare:", items, 0, false, &ok);

    if (ok && !selected.isEmpty()) {
        int index = items.indexOf(selected);
        const Activity& oldActivity = activityList.getAllActivities()[index];

        QDialog dialog(&window);
        dialog.setWindowTitle("Modifica Attività");

        QVBoxLayout* layout = new QVBoxLayout(&dialog);

        QLabel* descLabel = new QLabel("Descrizione:");
        QLineEdit* descEdit = new QLineEdit(QString::fromStdString(oldActivity.getDescription()));

        QLabel* dateLabel = new QLabel("Data:");
        QDateEdit* dateEdit = new QDateEdit(QDate(oldActivity.getData().getYear(),
                                                   oldActivity.getData().getMonth(),
                                                   oldActivity.getData().getDay()));
        dateEdit->setCalendarPopup(true);

        QLabel* startLabel = new QLabel("Ora Inizio:");
        QTimeEdit* startTimeEdit = new QTimeEdit(QTime(oldActivity.getStart().getHours(),
                                                        oldActivity.getStart().getMinutes()));

        QLabel* endLabel = new QLabel("Ora Fine:");
        QTimeEdit* endTimeEdit = new QTimeEdit(QTime(oldActivity.getEnd().getHours(),
                                                     oldActivity.getEnd().getMinutes()));

        QPushButton* okButton = new QPushButton("Salva");
        QPushButton* cancelButton = new QPushButton("Annulla");

        layout->addWidget(descLabel);
        layout->addWidget(descEdit);
        layout->addWidget(dateLabel);
        layout->addWidget(dateEdit);
        layout->addWidget(startLabel);
        layout->addWidget(startTimeEdit);
        layout->addWidget(endLabel);
        layout->addWidget(endTimeEdit);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addLayout(buttonLayout);

        QObject::connect(okButton, &QPushButton::clicked, [&]() {
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
            } catch (std::invalid_argument& e) {
                actionLabel->setText("Errore: " + QString::fromStdString(e.what()));
            }
        });

        QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

        dialog.exec();
    }
});


    createButton("Esci", [&]() {
        app.quit();
    });

    // Assembla UI
    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(subtitle);
    leftLayout->addWidget(line);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(actionLabel);

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}
