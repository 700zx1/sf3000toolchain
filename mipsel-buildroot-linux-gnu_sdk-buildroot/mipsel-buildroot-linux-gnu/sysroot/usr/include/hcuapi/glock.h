#ifndef _HCUAPI_GLOCK_H_
#define _HCUAPI_GLOCK_H_

#include <hcuapi/iocbase.h>

#define GLOCKIOC_SET_LOCKTIMEOUT		_IO (SCI_IOCBASE, 0) // Param: timeout
#define GLOCKIOC_SET_LOCK			_IO (SCI_IOCBASE, 1)
#define GLOCKIOC_SET_UNLOCK			_IO (SCI_IOCBASE, 2)
#define GLOCKIOC_SET_TRYLOCK			_IO (SCI_IOCBASE, 3)

#endif	/* _HCUAPI_GLOCK_H_ */
