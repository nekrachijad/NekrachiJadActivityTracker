#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

#include "Date.h"

int main(int argc, char *argv[]) {
    Date *d=new Date(5,5,2005);
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("ToDo List - Registro attività");
    window.resize(1200, 700);

    // Layout principale orizzontale
    QHBoxLayout *mainLayout = new QHBoxLayout(&window);

    // Colonna sinistra (titolo + pulsanti)
    QVBoxLayout *leftLayout = new QVBoxLayout();

    // Titolo
    QLabel *titleLabel = new QLabel("Benvenuto nel tuo Registro Attività!");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Sottotitolo
    QLabel *subtitle = new QLabel("Seleziona un'opzione per continuare:");
    subtitle->setStyleSheet("font-size: 22px; font-weight: bold;");
    subtitle->setAlignment(Qt::AlignCenter);

    // Separatore
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    // Layout dei bottoni
    QVBoxLayout *buttonLayout = new QVBoxLayout();

    // Etichetta a destra per mostrare l'azione selezionata
    QLabel *actionLabel = new QLabel("Qui verrà mostrata l'azione selezionata.");
    actionLabel->setStyleSheet("font-size: 18px; color: #333; background-color: #f0f0f0; padding: 10px; border: 1px solid #ccc;");
    actionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    actionLabel->setWordWrap(true);

    // Funzione per creare un bottone standard
    auto createButton = [&](const QString &text, const QString &message) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(40);
        btn->setMaximumWidth(400);
        btn->setStyleSheet("font-size: 16px;");
        QObject::connect(btn, &QPushButton::clicked, [=]() {
            actionLabel->setText(message);
        });
        buttonLayout->addWidget(btn);
    };

    // Pulsanti con azioni
    createButton("Crea una nuova lista attività", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Aggiungi una nuova attività", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Rimuovi un'attività", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Modifica un'attività", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Segna attività completata", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Mostra attività non completate", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Mostra tutte le attività", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Salva su file", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Carica da file", QString::fromStdString(std::to_string(d->getDay())));
    createButton("Esci", "Chiusura dell'applicazione.");

    // Assembla la parte sinistra
    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(subtitle);
    leftLayout->addWidget(line);
    leftLayout->addLayout(buttonLayout);

    // Aggiungi le due colonne al layout principale
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(actionLabel);

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}



