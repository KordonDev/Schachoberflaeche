#include "newgamebutton.h"

newGameButton::newGameButton(SchachLogik* logik, Zug* schachZug, OberflaecheInterface* oberlaeche, QObject *parent) :
    QObject(parent) {
		this->schachZug = schachZug;
		this->logik = logik;
		this->oberlaeche = oberlaeche;
}

void newGameButton::openNewGameWindow() {
    neuePartie = new QWidget;
	neuePartie->setWindowModality(Qt::ApplicationModal);
    neuePartie->setWindowTitle(QObject::tr("Neues Spiel"));

    QVBoxLayout* layout = new QVBoxLayout;

    QPushButton* einSpieler = new QPushButton("1 Spieler");
	QWidget::connect(einSpieler,SIGNAL(clicked()), this, SLOT(startePartieGegenComputer()));
    QPushButton* zweiSpieler = new QPushButton("2 Spieler");
	QWidget::connect(zweiSpieler,SIGNAL(clicked()), this, SLOT(startePartieMitZweiSpieler()));
    QPushButton* fensterSchliesen = new QPushButton("Abbrechen");
	QWidget::connect(fensterSchliesen,SIGNAL(clicked()), this, SLOT(schlieseFenster()));
    layout->addWidget(einSpieler);
    layout->addWidget(zweiSpieler);
	layout->addWidget(fensterSchliesen);

    neuePartie->setLayout(layout);
    neuePartie->show();
}

void newGameButton::startePartieGegenComputer() {
	SpielBeendet* spiel = new SpielBeendet();
}

void newGameButton::startePartieMitZweiSpieler() {
	SpielerBenachrichtigung* spielerEins = new SpielerMensch(schachZug);
	SpielerBenachrichtigung* spielerZwei = new SpielerMensch(schachZug);
	logik->registriereSpieler(WEISS,spielerEins);
	logik->registriereSpieler(SCHWARZ,spielerZwei);
	logik->starteSpiel();
	schlieseFenster();
	oberlaeche->oberflaecheAktualisieren();
}

void newGameButton::schlieseFenster() {
	neuePartie->close();
}