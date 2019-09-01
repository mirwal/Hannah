#include "Hannah.h"


Hannah::Hannah()
{
}


Hannah::~Hannah()
{
}

void Hannah::AufgabeFertig()
{
	aufgabe = Null;
}

void Hannah::setAufgabe(int z)
{
	aufgabe = z;
}

int Hannah::getAufgabe()
{ 
	return (aufgabe);
}
Hannah H;