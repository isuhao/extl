/* ///////////////////////////////////////////////////////////////////////
 * File:		user.h		
 *
 * Created:		08.02.02					
 * Updated:		08.04.14	
 *
 * Brief: user config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_USER_H
#define EXTL_CONFIG_USER_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#ifdef EXTL_DEBUG
#	include "debug.h"
#else
#	include "release.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_USER_H */
/* //////////////////////////////////////////////////////////////////// */
