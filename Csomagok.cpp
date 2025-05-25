#include "Csomagok.hpp"
#include <iostream>
#include "memtrace.h"           
#include "string.h"
#include "Tel.hpp"
#include "Combine.hpp"
#include "NetCs.hpp"

///Csomagok konstruktor, alapból 10 elemre elegendő helyet állít be
Csomagok::Csomagok(){
	csDb = 0;
	size = 10;
	csomagok = new Csomag*[size];
}

///desktruktor, használja a Delete függvényt
Csomagok::~Csomagok(){
	Delete();
	delete[] csomagok;
}

///Add fv. egy csomagot add hozzá a tárolóhoz, ha nincs elég hely akkor növeli a tároló kapacitását
void Csomagok::Add(Csomag* Csom){
	if(csDb+1 == size){
		size += 10;
		Csomag** temp = new Csomag*[size];
		
		for(size_t i = 0; i < csDb; i++){
			temp[i] = csomagok[i];
		}
		
		delete[] csomagok;
		
		csomagok = temp;
	}
	csomagok[csDb++] = Csom;
}

///törli a tárolóban lévő összes elemet
void Csomagok::Delete(){
	for(size_t i = 0; i < csDb; i++){
		delete csomagok[i];
	}
	csDb = 0;
}

///visszaadja a tároló méretét
size_t Csomagok::getSize()const{
	return size;
}

///visszaadja jelenleg legnagyobb indexű elemnél 1-el nagyobb indexet
size_t Csomagok::getcsDb()const{
	return csDb;
}

///értékadó operátor
Csomagok& Csomagok::operator=(const Csomagok& csom){
	if(this != &csom){
		Delete();
		delete[] csomagok;
		size = csom.getSize();
		csDb = 0;
		csomagok = new Csomag*[size];
		for(size_t i = 0; i < csom.getcsDb(); i++){
			csomagok[csDb++] = csom[i]->Clone();
		}
	}
	return *this;
}

///indexelő operátor
Csomag* Csomagok::operator[](size_t index){
	if(index >= 0 && index < csDb){
		return csomagok[index];
	}
	throw std::out_of_range("tul indexeles hiba");
}

///const verziója az indexelés operátorának
const Csomag* Csomagok::operator[](size_t index)const{	
	if(index >= 0 && index < csDb){
		return csomagok[index];
	}
	throw std::out_of_range("tul indexeles hiba");
}

///kiírja a megadott outputra az eltárolt objektumok adatait
void Csomagok::List(std::ostream& os){
	for(size_t i = 0; i < csDb; i++){
		csomagok[i]->show(os);
	}
}

///visszadja hogy benne van-e az adott nevű objektum a tárolt objektumok között
bool Csomagok::in_n(String csNev){
	for(size_t i = 0; i < csDb; i++){
		if(csNev == csomagok[i]->getNev()) return true;
	}
	return false;
}

///adott nevű objektum törlése a tárolt objektumok közül ha benne van a tárolóban
void Csomagok::Delete_cs(String csNev){
	if(in_n(csNev)){
		size_t ind = search_n(csNev);
		delete csomagok[ind];
		for(size_t i = ind; i+1 < csDb; i++){
			csomagok[i] = csomagok[i+1];
		}
		csDb--;
	}
}

///visszaadja az adott nevű objektum indexét a tárolóban ha benne van, egyébként a size_t -1 megfelelőjét adja vissza
size_t Csomagok::search_n(String csNev){
	for(size_t i = 0; i < csDb; i++){
		if(csomagok[i]->getNev() == csNev) return i;
	}
	return static_cast<size_t>(-1);
}

///adott inputról olvassa be az adatokat a megadott formátum szerint
void Csomagok::beolvas_other(std::istream& in){
	String nev, tipus;
	size_t dbperc, dbsms, dbgb, arsms, arperc, argb;

	std::cout << "\na beolvasas formatuma legyen a kovetkezo, a nevek _ legyenek elvalasztva: csomag_tipus(n = net, c = kombinalt, s = standard/csak sms es perc) csomag_nev ingyenes_sms_db ingyenes_perc_db ingyenes_gb_db sms_ar perc_ ar gb_ar\n";
	
	in >> tipus >> nev >> dbsms >> dbperc >>dbgb >> arsms >> arperc >> argb;
	if(in.fail()) std::cerr <<"rossz bemeneti ertek\n";
	if(in_n(nev)) std::cerr << "foglalt csomag nev\n";
	else{
		if(tipus == String("n") && !in.fail()) Add(new NetCs(nev, dbgb, argb));
		else if(tipus == String("c") && !in.fail())	Add(new Combine(nev, dbsms, dbperc, dbgb, argb, arsms, arperc));
		else if(tipus == String("s") && !in.fail()) Add(new Tel(nev, dbsms, dbperc, arsms, arperc));
		else std::cerr << "hibás bemeneti adatok\n";
	}

}

///adatok beolvasása főként fileból, de a megadott inputról megadott formátum szerint
void Csomagok::beolvas_file(std::istream& in){
	String nev, tipus;
	size_t dbperc, dbsms, dbgb, arsms, arperc, argb;

	while(in >> tipus >> nev >> dbsms >> dbperc >>dbgb >> arsms >> arperc >> argb){
		if(in.fail()) std::cerr <<"rossz bemeneti ertek\n";
		if(in_n(nev)) std::cerr << "foglalt csomag nev\n";
		else{
			if(tipus == String("n") && !in.fail()) Add(new NetCs(nev, dbgb, argb));
			else if(tipus == String("c") && !in.fail())	Add(new Combine(nev, dbsms, dbperc, dbgb, argb, arsms, arperc));
			else if(tipus == String("s") && !in.fail()) Add(new Tel(nev, dbsms, dbperc, arsms, arperc));
			else std::cerr << "hibás bemeneti adatok\n";
		}
		if(!in.eof() && in.fail()) std::cerr << "rossz bemeneti adatok";
	}


}
