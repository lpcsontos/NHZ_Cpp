#ifndef NETCS_HPP
#define NETCS_HPP

#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"

class NetCs : public Csomag{
	size_t freeGb;
	size_t arGb;
public:
	NetCs(String nev, size_t gb, size_t ar_gb);
	NetCs(const NetCs& net);
	~NetCs(){}
	size_t getGb() const;
	size_t getSms() const;
	size_t getPerc() const;
	Csomag* Clone() const override;
	void show(std::ostream& os) const override;
	size_t getArSms() const;
	size_t getArPerc() const;
	size_t getArGb() const;
};

#endif
