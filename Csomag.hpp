#ifndef CSOMAG_HPP
#define CSOMAG_HPP

#include "memtrace.h"           
#include "string.h"

class Csomag{
	String Nev;
public:
	Csomag(){}
	Csomag(const String& nev):Nev(nev){}
	virtual ~Csomag(){}
	virtual size_t getSms() const{ return 0;}
	virtual size_t getPerc() const{ return 0;}
	virtual size_t getGb() const{ return 0;}
	virtual size_t getArGb() const{ return 0;}
	virtual size_t getArSms() const{ return 0;}
	virtual size_t getArPerc() const{ return 0;}
	virtual Csomag* Clone() const = 0;
	virtual void show(std::ostream& os) const = 0;
	String getNev() const{
		return Nev;
	}
};


#endif
