#include "Egg.h"
#include "Basket.h"

int main() {
	Basket b("Stavri");

	b.addEgg(Egg("egg1", 4.5));
	b.addEgg(Egg("egg2", 3.2));
	b.addEgg(Egg("egg3", 5.0));

	b.serialize("basket.bin");

	Basket b2;
	b2.deserialize("basket.bin");

	b2.generateReport();

	return 0;
}