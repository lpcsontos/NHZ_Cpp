#ifndef SZOLGALTATO_HPP
#define SZOLGALTATO_HPP

#include "memtrace.h"           
#include "string.h"
#include "Vevo.hpp"
#include "Csomagok.hpp"

class Szolgaltato{
	Vevo** vevok;
	size_t vevoDb;
	size_t size;
public:
	Szolgaltato();
	Szolgaltato(const Szolgaltato& szolg);
	~Szolgaltato();
	void Add(Vevo* vevo);
	void List(std::ostream& os);
	void Delete();
	void Delete_v(int szam);
	size_t calc(Csomagok& csomag, size_t i, size_t ind);
	size_t getSize() const;
	size_t getDb() const;
	size_t search_sz(int szam);
	bool in_sz(int szam);
	void beolvas_file(std::istream& in);
	void beolvas_other(std::istream& in);
	void beolvasho_other(std::istream& in);
	void beolvasho_file(std::istream& in);
	void List_ar(std::ostream& os, Csomagok& csomag);
	Szolgaltato& operator=(const Szolgaltato& szolg);
	Vevo* operator[](size_t index);
	const Vevo* operator[](size_t index)const;
};

#endif
