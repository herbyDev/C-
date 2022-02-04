/*******************************************************************
 *
* Copyright (c) 1999, 2014, Oracle and/or its affiliates. All rights reserved.
 *
 *      This material is the confidential property of Oracle Corporation
 *      or its licensors and may be used, reproduced, stored or transmitted
 *      only in accordance with a valid Oracle license or sublicense agreement.
 *
 *******************************************************************/

#ifndef lint
static  char    Sccs_id[] = "@(#)$Id: fm_ac_treinamento_config.c /cgbubrm_7.5.0.portalbase/1 2015/11/27 05:40:50 nishahan Exp $";
#endif

#include <stdio.h>	/* for FILE * in pcm.h */
#include "ops/inv.h"
#include "pcm.h"
#include "cm_fm.h"
#include "ac_ops.h"


#ifdef WIN32
__declspec(dllexport) void * fm_ac_treinamento_config_func();
#endif


/*******************************************************************
 *******************************************************************/
struct cm_fm_config fm_ac_treinamento_config[] = {
	/* opcode as a u_int, function name (as a string) */
	{ AC_OP_TREINAMENTO_HELLO_WORLD, "op_ac_treinamento_hello_world"},
	{ AC_OP_TREINAMENTO_INSERT_UPDATE, "op_ac_treinamento_insert_update"},
	{ 0,(char *)0 }
};

#ifdef WIN32
void *
fm_ac_treinamento_config_func()
{
	return ((void *) (fm_ac_treinamento_config));
}
#endif
