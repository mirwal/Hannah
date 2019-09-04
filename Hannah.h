// #pragma once
#ifndef _HANNAH_H_
#define _HANNAH_H_

#define	Null			0
#define	Laufen			1
#define	Tanzen			2
#define	Springen		3
#define	StartPosi		4
#define	Schlapp			5
#define	Frost			6

class Hannah
{
public:
	Hannah();
	~Hannah();
	void AufgabeFertig();
	void setAufgabe(int z);
	int getAufgabe();
private:
	int aufgabe;
}; extern Hannah H;
#endif	//_HANNAH_H_