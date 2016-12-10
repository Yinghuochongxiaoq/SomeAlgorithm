#include "stdafx.h"
#include "VirtualClassNote.h"

typedef void(*Fun)(void);
void VirtualClassNote::VirtualMathRead()
{
	Base *d = new VirtualClassNote;
	Fun pFun = (Fun)*((int*)*(int*)(d)+0);
	printf("&(Base::f): 0x%x \n", (&Base::f));
	printf("&(Base::g):0x%x \n", (&Base::g));
	printf("&(VirtualClassNote::f): 0x%x \n", (&VirtualClassNote::f));
	printf("&(VirtualClassNote::g): 0x%x \n", (&VirtualClassNote::g));
	printf("pFun: 0x%x \n", pFun);
	pFun();
}
