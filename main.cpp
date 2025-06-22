#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

#include "Date.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crea oggetto data
    Date *d = new Date(5, 5, 2005);
    std::string DataProva = "Data: " + std::to_string(d->getDay())  + "/" + std::to_string(d->getMonth()) + "/" + std::to_string(d->getYear());

    // Finestra principale
    QWidget window;
    window.setWindowTitle("Esempio con Data e Bottone");
    window.resize(400, 200); // abbastanza grande

    // Layout verticale
    QVBoxLayout *layout = new QVBoxLayout();

    // Etichetta con la data
    QLabel *label = new QLabel(QString::fromStdString(DataProva));
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 18px;");

    // Bottone
    QPushButton *button = new QPushButton("Cliccami");
    button->setMinimumHeight(50);
    button->setStyleSheet("font-size: 16px;");

    // Aggiungi widget al layout
    layout->addWidget(label);
    layout->addWidget(button);

    // Imposta layout nella finestra
    window.setLayout(layout);
    window.show();

    return app.exec();
}
