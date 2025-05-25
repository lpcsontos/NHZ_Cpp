#ifndef VEVO_HPP
#define VEVO_HPP

#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"
#include "Csomagok.hpp"

class Vevo{
	String Nev;
	int Szam;
	String Csom;
	size_t hoPerc;
	size_t hoSms;
	size_t hoGb;
public:
	Vevo(String nev, int szam, String csom, size_t perc, size_t sms, size_t gb);
	Vevo(String nev, int szam, String csom);
	Vevo(const Vevo& cp);
	virtual ~Vevo(){}

	int getNumb() const;
	String getPack()const;
	size_t getPerc() const;
	size_t getSms() const;
	size_t getGb() const;
	void setPerc(size_t p);
	void setSms(size_t sms);
	void setGb(size_t gb);
	
	void show(std::ostream& os)const;
};

#endif
