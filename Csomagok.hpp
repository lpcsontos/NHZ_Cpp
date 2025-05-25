#ifndef CSOMAGOK_HPP
#define CSOMAGOK_HPP

#include "memtrace.h"           
#include "string.h"
#include "Csomag.hpp"

class Csomagok{
	size_t csDb;
	size_t size;
	Csomag** csomagok;
public:
	Csomagok();
	~Csomagok();
	void Add(Csomag* Csom);
	size_t search_n(String csNev);
	bool in_n(String csNev);
	void List(std::ostream& os);
	void Delete();
	void Delete_cs(String csNev);
	size_t getSize() const;
	size_t getcsDb() const;
	void beolvas_file(std::istream& in);
	void beolvas_other(std::istream& in);
	Csomagok& operator=(const Csomagok& csom);
	Csomag* operator[](size_t index);
	const Csomag* operator[](size_t index)const;
};


#endif
