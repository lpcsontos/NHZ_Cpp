#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"
#include "Combine.hpp"

///alap konstruktor
Combine::Combine(String nev, size_t sms, size_t perc, size_t gb, size_t ar_gb, size_t ar_sms, size_t ar_perc):Csomag(nev),freeGb(gb),freeSms(sms),freePerc(perc),arGb(ar_gb),arSms(ar_sms),arPerc(ar_perc){}

///másoló konstruktor
Combine::Combine(const Combine& comb):Csomag(comb.getNev()),freeGb(comb.getGb()),freeSms(comb.getSms()),freePerc(comb.getPerc()),arGb(comb.getArGb()),arSms(comb.getArSms()),arPerc(comb.getArPerc()){}

///visszaadja a csomaghoz tartozó ingyenes sms-ek darabszámát
size_t Combine::getSms() const{ 
	return freeSms;
}

///visszaadja a csomaghoz tartozó ingyenes perc-ek darabszámát
size_t Combine::getPerc() const{
	return freePerc;
}

///visszaadja a csomaghoz tartozó ingyenes gb-ok darabszámát
size_t Combine::getGb() const{
	return freeGb;
}

///clone függvény a deep copyhoz
Csomag* Combine::Clone() const{
	return new Combine(*this);
}

///kiíró függvény, mely kiírja a csomaghoz tartozó adatokat a megadott outputra
void Combine::show(std::ostream& os) const{
	os << "Csomagnev:"<< getNev() << " Ingyenes gb:"<< getGb() << " Ar:" << getArGb()  << " Ingyenes Sms db:" << getSms() << " Ar:" << getArSms() << " Ingyenes Perc db:" << getPerc() << " Ar:" << getArPerc() << "\n";
}

///visszaadja a csomaghoz tartozó gb-ok árát
size_t Combine::getArGb() const{
	return arGb;
}

///visszaadja a csomaghoz tartozó sms-ek árát
size_t Combine::getArSms() const{
	return arSms;
}

///visszaadja a csomaghoz tartozó percek árát
size_t Combine::getArPerc() const{
	return arPerc;
}
