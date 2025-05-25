#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"
#include "Csomagok.hpp"
#include "Vevo.hpp"
#include <iostream>

///konstruktor ha minden adattag megvan
Vevo::Vevo(String nev, int szam, String csom, size_t perc, size_t sms, size_t gb) : Nev(nev), Szam(szam), Csom(csom), hoPerc(perc), hoSms(sms), hoGb(gb) {}

///konstruktor hiányos adatoknál
Vevo::Vevo(String nev, int szam, String csom) : Nev(nev), Szam(szam), Csom(csom), hoPerc(0), hoSms(0), hoGb(0) {}

///másoló konstruktor
Vevo::Vevo(const Vevo& cp){
	Nev = cp.Nev;
	Szam = cp.Szam;
	Csom = cp.Csom;
	hoPerc = cp.hoPerc;
	hoSms = cp.hoSms;
	hoGb = cp.hoGb;
}

///visszaadja a telefonszámot
int Vevo::getNumb() const{
	return Szam;
}

///visszaadja az objektumhoz tartozó csomag nevét
String Vevo::getPack() const{
	return Csom;
}

///visszaadja a havi perc mennyiséget
size_t Vevo::getPerc() const{
	return hoPerc;
}

///visszaadja a havi sms mennyiséget
size_t Vevo::getSms() const{
	return hoSms;
}

///visszaadja a havi gb mennyiséget
size_t Vevo::getGb() const{
	return hoGb;
}

///beállítja a havi perc mennyiséget
void Vevo::setPerc(size_t p){
	hoPerc = p;
}

///beállítja a havi sms mennyiséget
void Vevo::setSms(size_t sms){
	hoSms = sms;
}

///beállítja a havi gb mennyiséget
void Vevo::setGb(size_t gb){
	hoGb = gb;
}
	
///kiírja az objektum adataiból a nevet, csomag nevet és a telefonszámot
void Vevo::show(std::ostream& os)const{
	os << "Nev:"<< Nev << " csomag:" << Csom << " telefon szam:" << Szam;
}
