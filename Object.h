#pragma once

#include "point.h"
#include "Register.h"
#include <vector>

#include <Typelist.h>

class Mover
{
public:
	Mover(){};
	virtual ~Mover(){};
	virtual void MoverUpdate() = 0;
	void doit()
	{
		MoverUpdate();
	}

};

class Drawer
{
public:
	Drawer(){};
	virtual ~Drawer(){};
	virtual void DrawerUpdate() = 0;
	void doit()
	{
		DrawerUpdate();
	}
};

//class Object : public Registee<Mover> , public Registee<Drawer>
class Object 
	: public Loki::GenScatterHierarchy<TYPELIST_2(Mover,Drawer),Registee>
{
private:

public:
	//virtual void MoverUpdate() = 0;
	//virtual void DrawerUpdate() = 0;

};

