#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"
#include "NetCs.hpp"

///alap konstruktor
NetCs::NetCs(String nev, size_t gb, size_t ar_gb):Csomag(nev),freeGb(gb),arGb(ar_gb){}
	
///másoló konstruktor
NetCs::NetCs(const NetCs& net):Csomag(net.getNev()),freeGb(net.getGb()),arGb(net.getArGb()){}

///visszaadja a csomaghoz tartozó ingyenes sms-ek darabszámát
size_t NetCs::getSms() const{ 
	return 0;
}

///visszaadja a csomaghoz tartozó ingyenes percek darabszámát
size_t NetCs::getPerc() const{
	return 0;
}

///visszaadja a csomaghoz tartozó ingyenes gb-ok darabszámát
size_t NetCs::getGb() const{
	return freeGb;
}

///clone függvény a másoláskor deep copy-hoz
Csomag* NetCs::Clone() const{
	return new NetCs(*this);
}

///kiírja a csomag adatait a megadott outputra
void NetCs::show(std::ostream& os) const{
	os << "Csomagnev:"<< getNev() << " Ingyenes gb:"<< getGb() << " Ar:" << getArGb()  << " Ingyenes Sms db:" << getSms() << " Ar:" << getArSms() << " Ingyenes Perc db:" << getPerc() << " Ar:" << getArPerc() << "\n";
}

///visszaadja a csomaghoz tartozó gb-ok árát
size_t NetCs::getArGb() const{
	return arGb;
}

///visszaadja a csomaghoz tartozó sms-ek árát
size_t NetCs::getArSms() const{
	return 0;
}

///visszaadja a csomaghoz tartozó percek árát
size_t NetCs::getArPerc() const{
	return 0;
}
