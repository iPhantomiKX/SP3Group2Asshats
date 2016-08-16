/******************************************************************************/
/*!
\file	CheckMemoryLeak.h
\author Foo Jing Ting
\par	email: 152856H\@mymail.nyp.edu.sg
\brief
Function that checks for memory leaks
*/
/******************************************************************************/
#ifndef CHECKMEMORYLEAK_H
#define CHECKMEMORYLEAK_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBGUG
    #ifndef DBG_NEW
        #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
        #define new DBG_NEW
    #endif
#endif  // _DEBUG

void CheckMemoryLeaks()
{
    _CrtDumpMemoryLeaks();
}

#endif