#include "SpielerMensch.h"


SpielerMensch::SpielerMensch(Zug* schachZug, Farbe spielFarbe){
	this->schachZug = schachZug;
	this->spielFarbe = spielFarbe;
}

void SpielerMensch::duBistDran() {
	schachZug->zugBeginnen();
}

FigurTyp SpielerMensch::tauscheBauern() {
	FigurTyp gewaehlt;
	new FigurenWechsel(gewaehlt);
	return gewaehlt;
}

void SpielerMensch::spielBeendet() {
	new SpielBeendet();
}

Farbe SpielerMensch::getSpielFarbe() {
	return spielFarbe;
}

SpielerMensch::~SpielerMensch() {
}
