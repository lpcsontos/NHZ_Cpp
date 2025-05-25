#include "memtrace.h"           
#include "string.h"
#include "Vevo.hpp"
#include "Szolgaltato.hpp"
#include <iostream>

///alap konstruktor, mely létrehozza a tárolót és felkészíti egy kezdeti 50 objektumra
Szolgaltato::Szolgaltato(){
	vevoDb = 0;
	size = 50;
	vevok = new Vevo*[size];
}

///másoló konstruktor
Szolgaltato::Szolgaltato(const Szolgaltato& szolg){
	size = szolg.getSize();
	vevoDb = szolg.getDb();
	vevok = new Vevo*[size];
	for(size_t i = 0; i < vevoDb; i++){
		vevok[i] = new Vevo(*szolg[i]);
	}
}

///visszaadja a tároló jelenlegi maximális méretét
size_t Szolgaltato::getSize() const{
	return size;
}

///visszaadja a tárolóban eltárolt objektumok számát
size_t Szolgaltato::getDb() const{
	return vevoDb;
}

///destruktor
Szolgaltato::~Szolgaltato(){
	Delete();
	delete[] vevok;
}

///kiírja a tárolóban eltárolt objektumok adatait
void Szolgaltato::List(std::ostream& os){
	for(size_t i = 0; i < vevoDb; i++){
		vevok[i]->show(os);
		os << '\n';
	}
}

///beolvassa az adott inputról a vevő objektum adatait
void Szolgaltato::beolvas_other(std::istream& in){
	String nev, csom;
	int szam;

	std::cout << "\na beolvasas formatuma legyen a kovetkezo, a nevek _ legyenek elvalasztva: vezeteknev_keresztnev telefonszam csomag_nev\n";
	
	in >> nev >> szam >> csom;
	if(in.fail()) std::cerr <<"rossz bemeneti ertek\n";
	if(szam > 999999999 || szam < 100000000) std::cerr << "Hibas bemenet\n";
	else if(!in_sz(szam) && !in.fail()) Add(new Vevo(nev, szam, csom));
	else std::cerr << "foglalt telefonszam\n";


}

///beolvassa egy adott vevőhöz tartozó havi adatokat adott inputról
void Szolgaltato::beolvasho_other(std::istream& in){
	size_t gb,sms,perc;
	int szam;
	std::cout << "\na beolvasasi formatum legyen: telefonszam hasznalt_perc sms internet(gb)\n";
	in >> szam >> perc >> sms >> gb;
	if(in.fail()) std::cerr << "rossz bemeneti ertek\n";
	if(szam > 999999999 || szam < 100000000) std::cerr << "rossz telefonszam\n";
	else if(in_sz(szam) && !in.fail()){
		size_t ind = search_sz(szam);
		vevok[ind]->setPerc(perc);
		vevok[ind]->setSms(sms);
		vevok[ind]->setGb(gb);
	}
	else std::cerr << "rossz telefonszam\n";
}

/// főként fileból, de adott inputról olvassa be adott vevők havi adatait
void Szolgaltato::beolvasho_file(std::istream& in){
	size_t gb,sms,perc;
	int szam;
	while(in >> szam >> perc >> sms >> gb){
	if(in.fail()) std::cerr << "rossz bemeneti ertek\n";
		if(szam < 100000000 || szam > 999999999) std::cerr << "rossz telefonszam\n";
		else if(in_sz(szam) && !in.fail()){
			size_t ind = search_sz(szam);
			vevok[ind]->setPerc(perc);
			vevok[ind]->setSms(sms);
			vevok[ind]->setGb(gb);
		}
		else std::cerr << "rossz telefonszam\n";
	}
	if(!in.eof() && in.fail()){
		std::cerr << "rossz bemeneti adatok\n";
	}
}

///fileból főként de adott inputról olvassa be a vevők adatait
void Szolgaltato::beolvas_file(std::istream& in){
	String nev, csom;
	int szam;
	
	while(in >> nev >> szam >> csom){
		if(szam < 100000000 || szam > 999999999) std::cerr << "Hibas bemenet\n";
		else if(!in_sz(szam) && !in.fail()) Add(new Vevo(nev, szam, csom));
		else std::cerr << "foglalt telefonszam\n";
	}

	if(!in.eof() && in.fail()){
		std::cerr << "rossz bemeneti adatok\n";
	}
}

///kiírja a kiszamítható havi költséggel rendelkező vevők havi költségét
void Szolgaltato::List_ar(std::ostream& os, Csomagok& csomag){
	if(csomag.getcsDb() > 0)for(size_t i = 0; i < vevoDb; i++){
		if(csomag.in_n(vevok[i]->getPack())){
			vevok[i]->show(os);
			size_t ind = csomag.search_n(vevok[i]->getPack());
			os << " befizetendo:" << calc(csomag, i, ind) <<"\n";
		}
	}
}

///segédfüggvény a havi költség kiszámításra
size_t Szolgaltato::calc(Csomagok& csomag, size_t i, size_t ind){
	int dbp = vevok[i]->getPerc() - csomag[ind]->getPerc();
	int dbsms = vevok[i]->getSms() - csomag[ind]->getSms();
	int dbgb = vevok[i]->getGb() - csomag[ind]->getGb();

	if(dbp < 0) dbp = 0;
	if(dbsms < 0) dbsms = 0;
	if(dbgb < 0) dbgb = 0;

	return (dbp*csomag[ind]->getArPerc() + dbsms*csomag[ind]->getArSms() + dbgb*csomag[ind]->getArGb());

}

///tároló adatainak törlése
void Szolgaltato::Delete(){
	for(size_t i = 0; i < vevoDb; i++){
		delete vevok[i];
	}
}

///tárolóhoz új objektum hozzáadása
void Szolgaltato::Add(Vevo* vevo){
	if(vevoDb + 1 == size){
		size += 50;
		Vevo** temp = new Vevo*[size];

		for(size_t i = 0; i < vevoDb; i++){
			temp[i] = vevok[i];
		}

		delete[] vevok;
		vevok = temp;
	}
	vevok[vevoDb++] = vevo;
}

///tároló indexel való hozzáférése
Vevo* Szolgaltato::operator[](size_t index){
	if(index >= 0 && index < vevoDb){
		return vevok[index];
	}
	throw std::out_of_range("tul indexeles hiba");
}

///tároló indexel való hozzáférése constans visszatérési értékkel
const Vevo* Szolgaltato::operator[](size_t index)const{
	if(index >= 0 && index < vevoDb){
		return vevok[index];
	}
	throw std::out_of_range("tul indexeles hiba");
}

///visszaadja adott telefonszámmal rendelkező vevő benne van-e a tárolóban
bool Szolgaltato::in_sz(int szam){
	for(size_t i = 0; i < vevoDb; i++){
		if(vevok[i]->getNumb() == szam) return true;
	}
	return false;
}

///visszaadja adott telefonszámmal rendelkező vevő tárolóban lévő indexét ha van, egyébként a size_t -1 megfelelőjét
size_t Szolgaltato::search_sz(int szam){
	for(size_t i = 0; i < vevoDb; i++){
		if(vevok[i]->getNumb() == szam) return i;
	}
	return static_cast<size_t>(-1);
}

///adott telefonszámmal rendelkező vevő törlése a tárolóbol
void Szolgaltato::Delete_v(int szam){
	if(in_sz(szam)){
		size_t ind = search_sz(szam);
		delete vevok[ind];
		for(size_t i = ind; i +1 < vevoDb; i++){
			vevok[i] = vevok[i+1];
		}
		vevoDb--;
	}

}

///értékadó operátor
Szolgaltato& Szolgaltato::operator=(const Szolgaltato& szolg){
	if(this != &szolg){
		Delete();
		delete[]vevok;
		size = szolg.getSize();
		vevoDb = 0;
		vevok = new Vevo*[size];

		for(size_t i = 0; i < szolg.getDb(); i++){
			vevok[vevoDb++] = new Vevo(*szolg[i]);
		}
	}
	return *this;
}
