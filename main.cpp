#include <iostream>
#include <fstream>
#include "Csomagok.hpp"
#include "Szolgaltato.hpp"
#include "test.hpp"

int main(){
	test_run();
	Szolgaltato sz;
	Csomagok cs;
	int be;
	bool run = true;

	while(run){
		std::cout << "\n1. Csomag adatai beolvasás konzolrol\n"
			<< "2. Csomag adatai beolvasas filebol(csomag.txt)\n"
			<< "3. Csomag nev szerint torles\n"
			<< "4. Csomagok kiirasa\n"
			<< "5. Vevo felvetele konzolrol\n"
			<< "6. Vevo felvetele filebol(vevo.txt)\n"
			<< "7. Vevok kiirasa\n"
			<< "8. Vevo torlese\n"
			<< "9. Vevo havi adat felvetele konzolrol\n"
			<< "10. Vevo havi adat felvetele fajlbol(ho.txt)\n"
			<< "11. Vevok fizetendo osszegenek kiirasa\n"
			<< "12. kilepes\n";

		std::cin >> be;
		
		if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\nHibas bemenet, szamot irj be!\n";
        continue;
    	}
		switch(be){
			case 1:{
				cs.beolvas_other(std::cin);
				break;
					 }
			case 2:{
				std::ifstream file1("csomag.txt");
				if(!file1) std::cout << "\na file nem megnyithato\n";
				else {
					cs.beolvas_file(file1);
					file1.close();
				}
				break;
				}
			case 3:{
				String nev = "";
				std::cout << "\n adj meg egy nevet amit torolni akarsz, csomag_nev formatumban\n";
				std::cin >> nev;
				cs.Delete_cs(nev);
				break;}
			case 4:{
				cs.List(std::cout);
				break;}
			case 5:{
				sz.beolvas_other(std::cin);
				break;}
			case 6:{
				std::ifstream file2("vevo.txt");
				if(!file2)std::cout << "\na file nem megnyithato\n";
				else {
					sz.beolvas_file(file2);
					file2.close();
				}
				break;}
			case 7:{
				sz.List(std::cout);
				break;}
			case 8:{
				std::cout << "\nadja meg a vevo telefonszamat hogy torolhessuk a rendszerbol\n";
				int szam = 0;
				std::cin >> szam;
				if(szam > 0) sz.Delete_v(szam);
				else std::cout << "hibas adat volt megadva\n";
				break;}
			case 9:{
				sz.beolvasho_other(std::cin);
				break;}
			case 10:{
				std::ifstream file3("ho.txt");
				if(!file3) std::cout<< "\na file nem megnyithato\n";
				else {
					sz.beolvasho_file(file3);
					file3.close();
				}
				break;}
			case 11:{
				sz.List_ar(std::cout, cs);
				break;}
			case 12:{
				run = false;
				break;}
			default:{
				std::cout << "nincs ilyen menupont\n";
				break;
			}
		}
	}
}
