#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"
#include "Tel.hpp"

///alap konstruktor
Tel::Tel(String nev, size_t sms, size_t perc, size_t ar_sms, size_t ar_perc):Csomag(nev),freeSms(sms),freePerc(perc),arSms(ar_sms),arPerc(ar_perc){}

///másoló konstruktor
Tel::Tel(const Tel& tel):Csomag(tel.getNev()),freeSms(tel.getSms()),freePerc(tel.getPerc()),arSms(tel.getArSms()),arPerc(tel.getArPerc()){}

///visszaadja a csomaghoz tartozó ingyenes sms-ek darabszámát
size_t Tel::getSms() const{ 
	return freeSms;
}

///visszaadja a csomaghoz tartozó ingyenes percek darabszámát
size_t Tel::getPerc() const{
	return freePerc;
}

///visszaadja a csomaghoz tartozó ingyenes gb-ok darabszámát
size_t Tel::getGb() const{
	return 0;
}

///clone függvény a másoláskor deep copy-hoz
Csomag* Tel::Clone() const{
	return new Tel(*this);
}

///kiíró függvény amely a megadott outputra írja ki a csomag adatait
void Tel::show(std::ostream& os) const{
	os << "Csomagnev:"<< getNev() << " Ingyenes gb:"<< getGb() << " Ar:" << getArGb()  << " Ingyenes Sms db:" << getSms() << " Ar:" << getArSms() << " Ingyenes Perc db:" << getPerc() << " Ar:" << getArPerc() << "\n";
}

///visszaadja a csomaghoz tartozó gb-ok árát
size_t Tel::getArGb() const{
	return 0;
}

///visszaadja a csomaghoz tartozó sms-ek árát
size_t Tel::getArSms() const{
	return arSms;
}

///visszaadja a csomaghoz tartozó percek árát
size_t Tel::getArPerc() const{
	return arPerc;
}
