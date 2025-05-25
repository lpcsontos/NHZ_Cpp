#ifndef TEL_HPP
#define TEL_HPP

#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"

class Tel: public Csomag{
	size_t freeSms;
	size_t freePerc;
	size_t arSms;
	size_t arPerc;
public:
	Tel(String nev, size_t sms, size_t perc, size_t ar_sms, size_t ar_perc);
	Tel(const Tel& tel);
	~Tel(){}
	size_t getSms() const;
	size_t getPerc() const;
	size_t getGb() const;
	Csomag* Clone() const override;
	void show(std::ostream& os) const override;
	size_t getArGb() const;
	size_t getArSms() const;
	size_t getArPerc() const;
};


#endif
