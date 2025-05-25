#include "test.hpp"
#include "gtest_lite.h"
#include "Tel.hpp"
#include "NetCs.hpp"
#include "Csomagok.hpp"
#include "Csomag.hpp"
#include "Combine.hpp"
#include "Vevo.hpp"
#include "Szolgaltato.hpp"
#include "string.h"
#include "memtrace.h"

void test_run() {
	    TEST(String, construct) {
      String ures;
      ures.printDbg("Ures sztring: ");   // debug kiíratás
      if (ures.size() != 0)
        FAIL() << "Baj van a string hosszaval" << std::endl;
    } ENDM

    TEST(String, emptyStr) {
      String ures;
      EXPECT_EQ((size_t)0, ures.size()) << "Baj van a string hosszaval" << std::endl;

      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << std::endl;
    } ENDM
 
	 TEST(String, fromChr) {
      char ch = 'a';
      String a(ch);
      EXPECT_EQ((size_t)1, a.size()) << "Baj van a string hosszaval" << std::endl;
      EXPECT_STREQ("a", a.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << std::endl;

      String b('a');    // konstansból is megy?
      EXPECT_STREQ("a", b.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << std::endl;
    } ENDM

    TEST(String, FromCstr) {
      const char *hello = "Hello sztring";
      String a(hello);
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van a string hosszaval" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "C-sztringbol string letrehozasa nem sikerult!" << std::endl;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      char cpp[] = { 'C', '+', '+', '\0' };
      String b(cpp);
      cpp[0] = 'X';
      EXPECT_STRNE(cpp, b.c_str()) << "FromCstr: le kellett volna masolni a karaktertombot!" << std::endl;
    } ENDM

    TEST(String, ctor) {
      const char *hello = "Hello sztring";
      String a(hello);
      String b = a;
      EXPECT_EQ(strlen(hello), b.size()) << "Baj van a string hosszaval!" << std::endl;
      EXPECT_STREQ(hello, b.c_str()) << "Baj van a masolo konstruktorral!" << std::endl;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
         FAIL()  << "!** ctor: nem elegendo a pointereket lemasolni!" << std::endl;

      EXPECT_STREQ(hello, a.c_str()) << "Masolo kontsr. elromlott a forras!" << std::endl;
      EXPECT_EQ(strlen(hello), a.size()) << "Masolo konstr. alatt elromlott a forras hossza!" << std::endl;

      const String c = a;
      String d = c;     // konstansból is megy?
      EXPECT_STREQ(hello, d.c_str()) << "Baj van a masolo konstruktorral" << std::endl;
    } ENDM

    TEST(String, ctor_nullptr) {
      String d0;
      String ures = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, ures.size()) << "Baj van a string hosszaval" << std::endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << std::endl;
    } ENDM

    TEST(String, opAssign) {
      const char *hello = "Hello sztring";
      String a(hello);
      String b("Duma1"), c("Duma2");
      EXPECT_STRNE(a.c_str(), b.c_str());
      a = a;
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van az ertekadassal: a = a hossz" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "Baj van az ertekadassal: a = a" << std::endl;
      c = b = a;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
         FAIL()  << "!** op=: nem elegendo a pointereket lemasolni!" << std::endl;

      EXPECT_EQ(strlen(hello), a.size()) << "Ertekedasnal elromlott a forras hossza!" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "Ertekadasnal elromlott a forras!" << std::endl;
      EXPECT_EQ(strlen(hello), b.size()) << "Ertekedas: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(hello, b.c_str()) << "Ertekadas nem sikerult!" << std::endl;
      EXPECT_EQ(strlen(hello), c.size()) << "Ertekedas: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(hello, c.c_str()) << "Ertekadas nem sikerult!" << std::endl;

      const String d("Konst.");
      c = d;        // konstansból is megy?
      EXPECT_EQ(c.size(), c.size()) << "Ertekedas konstansbol: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(d.c_str(), c.c_str()) << "Ertekadas konstansbol nem sikerult!" << std::endl;
    } ENDM

    TEST(String, opAssign_nullptr) {
      String d0;
      String c = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, c.size()) << "Baj van a string hosszaval" << std::endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", c.c_str()) << "Nem ures sztring jott letre" << std::endl;

    } ENDM

    TEST(String, strPlusStr) {
      String a("Hello ");
      String b("sztring");
      String c;
      c = a + b;
      EXPECT_STREQ("Hello sztring", c.c_str()) << "Nem sikerult a + String muvelet!" << std::endl;
      EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;
      EXPECT_STREQ("sztring", b.c_str()) << "A + muvelet elrontja a jobb oldalt?" << std::endl;
      const String a1 = a, b1 = b;

      String c1;
      c1 = a1 + b1;          // konstansból is megy?
      EXPECT_STREQ("Hello sztring", c1.c_str()) << "Nem sikerult a + String muvelet!" << std::endl;
    } ENDM

    TEST(String, strPlusChr) {
      String a("Hello ");
      String b;
      b = a + 'B';
      EXPECT_STREQ("Hello B", b.c_str()) << "Nem sikerult a + char muvelet!" << std::endl;
      EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;

      const String a1 = a;
      String b1;
      b1 = a1 + 'B';          // konstansból is megy?
      EXPECT_STREQ("Hello B", b1.c_str()) << "Nem sikerult a + char muvelet!" << std::endl;
      EXPECT_STREQ("Hello ", a1.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;

    } ENDM

    TEST(String, chrPlusStr) {
      String a("ello");
      String b;
      char h = 'H';
      b = h + a;
      EXPECT_STREQ("Hello", b.c_str()) << "Nem sikerult char + Str muvelet!" << std::endl;
      EXPECT_STREQ("ello", a.c_str()) << "A + muvelet elrontja a jobb oldalt?" << std::endl;

      String b1;
      b1 = 'H' + a;  // konstanssal is megy?
      EXPECT_STREQ("Hello", b.c_str()) << "Nem sikerult char + Str muvelet!" << std::endl;
    } ENDM

    TEST(String, index) {
      String a("Hello 678");
      EXPECT_NO_THROW(a[0]);
      EXPECT_NO_THROW(a[7]);
      EXPECT_NO_THROW(a[8]);
      EXPECT_THROW(a[9], const char *);
      EXPECT_THROW(a[-1], const char *);
      EXPECT_EQ('7', a[7]);
      a[7] = '.';
      EXPECT_EQ('.', a[7]);
    } ENDM

    TEST(String, insert) {
      String a("Hello sztring");
      std::stringstream ss;
      ss << a;
      EXPECT_STREQ("Hello sztring", ss.str().c_str());
    } ENDM

    TEST(String, extract) {
      String a("Hello   sztring \n Lajos12");
      std::stringstream ss;
      ss << a;
      String in1, in2, in3;
      ss >> in1 >> in2;         // fűzhetőnek kell lenni
      while (ss >> in3);        // csak kicsit gonosz a teszt !
      EXPECT_STREQ("Hello", in1.c_str());
      EXPECT_STREQ("sztring", in2.c_str());
      EXPECT_STREQ("Lajos12", in3.c_str());
    } ENDM

	 TEST(String, osszehasonlitas){
		String a("hello");
		String b = "a";
		String c = "a";
		EXPECT_FALSE(a == b);
		EXPECT_TRUE(b == c);
	 }END

    TEST(Csomag, Combine_mukodes) {
        Combine c1("t", 1, 2, 3, 4, 5, 6);
		  EXPECT_EQ(3u, c1.getGb());
		  EXPECT_EQ(1u, c1.getSms());
		  EXPECT_EQ(2u, c1.getPerc());
		  EXPECT_EQ(4u, c1.getArGb());
		  EXPECT_EQ(5u, c1.getArSms());
		  EXPECT_EQ(6u, c1.getArPerc());
		  String s = "t";
		  EXPECT_EQ(s, c1.getNev());
		  c1.show(std::cout);
    } END

	 TEST(Csomag, NetCs_mukodes){
		NetCs c1("t", 1, 2);
		  EXPECT_EQ(1u, c1.getGb());
		  EXPECT_EQ(0u, c1.getSms());
		  EXPECT_EQ(0u, c1.getPerc());
		  EXPECT_EQ(2u, c1.getArGb());
		  EXPECT_EQ(0u, c1.getArSms());
		  EXPECT_EQ(0u, c1.getArPerc());
		  String s = "t";
		  EXPECT_EQ(s, c1.getNev());
		c1.show(std::cout);
	 }END
	
	 TEST(Csomag, Tel_mukodes){
		Tel c1("t", 1, 2, 3, 4);
		  EXPECT_EQ(0u, c1.getGb());
		  EXPECT_EQ(1u, c1.getSms());
		  EXPECT_EQ(2u, c1.getPerc());
		  EXPECT_EQ(0u, c1.getArGb());
		  EXPECT_EQ(3u, c1.getArSms());
		  EXPECT_EQ(4u, c1.getArPerc());
		  String s = "t";
		  EXPECT_EQ(s, c1.getNev());
		c1.show(std::cout);
	 }END

	 TEST(Csomagok, konstruktor){
		EXPECT_NO_THROW(Csomagok cs);
		Csomagok cs;
		EXPECT_EQ(10u, cs.getSize());
		cs.Add(new NetCs("t",1,2));
		String s = "t";
		EXPECT_EQ(s,cs[0]->getNev());
		EXPECT_EQ(1u, cs[0]->getGb());
		EXPECT_EQ(1u, cs.getcsDb());
		EXPECT_EQ(10u, cs.getSize());
		cs[0]->show(std::cout);
	 }END

TEST(Csomagok, Add_mukodes){
		Csomagok cs;
		cs.Add(new NetCs("t", 1, 2));
		cs.Add(new NetCs("t1", 1, 2));
		cs.Add(new NetCs("t3", 1, 2));
		cs.Add(new NetCs("t4", 1, 2));
		cs.Add(new NetCs("t5", 1, 2));
		cs.Add(new NetCs("t6", 1, 2));
		cs.Add(new NetCs("t7", 1, 2));
		cs.Add(new NetCs("t8", 1, 2));
		cs.Add(new NetCs("tb", 1, 2));
		cs.Add(new NetCs("ta", 1, 2));
		EXPECT_NO_THROW(cs.Add(new NetCs("t9", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t10", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t11", 1, 2)));
		EXPECT_EQ(13u, cs.getcsDb());
		EXPECT_NO_THROW(cs.Add(new NetCs("t12", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t13", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t14", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t15", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t16", 1, 2)));
		String s = "t11";
		EXPECT_EQ(s, cs[12]->getNev());
		EXPECT_EQ(1u, cs[0]->getGb());
		EXPECT_EQ(20u, cs.getSize());
		EXPECT_EQ(18u, cs.getcsDb());
		cs.List(std::cout);
	 }END

	 TEST(Csomagok, index_mukodes){
		Csomagok cs;
		cs.Add(new NetCs("t",1,2));
		EXPECT_EQ(1u, cs[0]->getGb());
		EXPECT_THROW(cs[4], std::out_of_range&);
	 }END

	 TEST(Csomagok, ertekadas){
		Csomagok cs;
		cs.List(std::cout);
		Csomagok cs2;
		cs.Add(new NetCs("t", 1, 2));
		cs.Add(new NetCs("t1", 1, 2));
		cs.Add(new NetCs("t3", 1, 2));
		cs.Add(new NetCs("t4", 1, 2));
		cs.Add(new NetCs("t5", 1, 2));
		cs.Add(new NetCs("t6", 1, 2));
		cs.Add(new NetCs("t7", 1, 2));
		cs.Add(new NetCs("t8", 1, 2));
		cs.Add(new NetCs("tb", 1, 2));
		cs.Add(new NetCs("ta", 1, 2));
		EXPECT_NO_THROW(cs.Add(new NetCs("t9", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t10", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t11", 1, 2)));
		EXPECT_EQ(13u, cs.getcsDb());
		EXPECT_NO_THROW(cs.Add(new NetCs("t12", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t13", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t14", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t15", 1, 2)));
		EXPECT_NO_THROW(cs.Add(new NetCs("t16", 1, 2)));
		cs2 = cs;
		cs.Delete();
		String s = "t6";
		EXPECT_EQ(s, cs2[5]->getNev());
		EXPECT_EQ(1u, cs2[0]->getGb());
		EXPECT_EQ(20u, cs2.getSize());
		EXPECT_EQ(18u, cs2.getcsDb());
		cs2.List(std::cout);
	 }END

	 TEST(Csomagok, kereses){
		Csomagok cs;
		cs.Add(new NetCs("t", 1, 2));
		cs.Add(new NetCs("t1", 1, 2));
		if(EXPECT_TRUE(cs.in_n("t1"))){
			EXPECT_EQ(1u, cs.search_n("t1"));
		}
		EXPECT_EQ(static_cast<size_t>(-1), cs.search_n("k"));
		EXPECT_FALSE(cs.in_n("k"));
	 }END

	 TEST(Csomagok, delete){
		Csomagok cs;
		cs.Add(new NetCs("t", 1, 2));
		cs.Delete_cs("t");
		cs.List(std::cout);
	 }END

	 TEST(Csomagok, beolvasas){
		Csomagok cs;
		std::ifstream file("csomag.txt");
		cs.beolvas_file(file);
		cs.List(std::cout);
	 }END

	 TEST(Vevo, minden){
		Vevo s("t", 12, "cs", 1, 2, 3);
		Vevo s2("t2", 13, "cs2");
		EXPECT_EQ(12,s.getNumb());
		String st = "cs";
		EXPECT_EQ(st,s.getPack());
		EXPECT_EQ(1,s.getPerc());
		EXPECT_EQ(2,s.getSms());
		EXPECT_EQ(3,s.getGb());
		s2.setPerc(5);
		s2.setGb(5);
		s2.setSms(5);
		EXPECT_EQ(5,s2.getPerc());
		EXPECT_EQ(5,s2.getGb());
		EXPECT_EQ(5,s2.getSms());
	 }END

	 TEST(Szolgaltato, minden){
		Szolgaltato sz;
		sz.Add(new Vevo("t",1,"cs", 1, 1, 1));
		Csomagok cs;
		cs.Add(new Combine("cs", 0, 1, 0, 2, 2, 2));
		sz.List_ar(std::cout, cs);
		EXPECT_EQ(4u,sz.calc(cs,0, 0));
		EXPECT_EQ(50,sz.getSize());
		EXPECT_EQ(1u, sz.getDb());
		EXPECT_EQ(0,sz.search_sz(1));
		EXPECT_TRUE(sz.in_sz(1));
		EXPECT_FALSE(sz.in_sz(2));
		sz.List(std::cout);
		sz.Delete_v(1);
		sz.List(std::cout);
		sz.Add(new Vevo("t",1,"cs"));
		sz.Add(new Vevo("t2", 12, "cs2", 1, 2, 3));
		sz.List(std::cout);
	 }END

	TEST(Szolgaltato, megtobb){
		Szolgaltato sz;
		std::ifstream file1("ho.txt");
		sz.beolvasho_file(file1);
		file1.close();
		std::ifstream file2("vevo.txt");
		sz.beolvas_file(file2);
		sz.List(std::cout);
		file2.close();
	}END

}
