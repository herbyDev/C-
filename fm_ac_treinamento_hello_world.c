/*******************************************************************
 *
 *      Copyright (c) 2006 Oracle. All rights reserved.
 *
 *      This material is the confidential property of Oracle Corporation
 *      or its licensors and may be used, reproduced, stored or transmitted
 *      only in accordance with a valid Oracle license or sublicense agreement.
 *
 *******************************************************************/

#ifndef lint
static	char	Sccs_id[] = "@(#)%Portal Version: fm_ac_treinamento_hello_world.c:BillingVelocityInt:2:2006-Sep-05 04:27:10 %";
#endif

/*******************************************************************
 * Contains the PCM_OP_AC_TREINAMENTO_HELLO_WORLD operation. 
 *******************************************************************/


#include <stdio.h> 
#include <string.h> 
 
#include "pcm.h"
#include "ops/inv.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "ac_ops.h"


/*******************************************************************
 * Routines contained within.
 *******************************************************************/
EXPORT_OP void
op_ac_treinamento_hello_world(
	cm_nap_connection_t	*connp,
	int32			opcode,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**o_flistpp,
	pin_errbuf_t		*ebufp);

static void
fm_ac_treinamento_hello_world(
	pcm_context_t		*ctxp,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**ret_flistpp,
	pin_errbuf_t		*ebufp);

/*******************************************************************
 * Main routine for the PCM_OP_AC_TREINAMENTO_HELLO_WORLD operation.
 *******************************************************************/
void
op_ac_treinamento_hello_world(
	cm_nap_connection_t	*connp,
	int32			opcode,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**o_flistpp,
	pin_errbuf_t		*ebufp)
{
	pcm_context_t		*ctxp = connp->dm_ctx;
	pin_flist_t		*r_flistp = NULL;


	if (PIN_ERR_IS_ERR(ebufp)) {
		return;
	}
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	 * Invalid call
	 ***********************************************************/
	if (opcode != AC_OP_TREINAMENTO_HELLO_WORLD) {
		pin_set_err(ebufp, PIN_ERRLOC_FM,
			PIN_ERRCLASS_SYSTEM_DETERMINATE,
			PIN_ERR_BAD_OPCODE, 0, 0, opcode);
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_hello_world opcode error", ebufp);
		return;
	}

	/***********************************************************
	 * Debug: What we got.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_ac_treinamento_hello_world input flist", i_flistp);

	/***********************************************************
	 * Implementation
	 ***********************************************************/
	fm_ac_treinamento_hello_world(ctxp, flags, i_flistp, &r_flistp, ebufp);

	/***********************************************************
	 * Results.
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {

		/***************************************************
		 * Log errors
		 ***************************************************/
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_hello_world error", ebufp);

		PIN_FLIST_DESTROY_EX(&r_flistp, NULL);

		*o_flistpp = NULL;

	} else {

		/***************************************************
		 * Succesful completion
		 ***************************************************/
		*o_flistpp = r_flistp;

		/***************************************************
		 * Return flist log
		 ***************************************************/
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
			"op_ac_treinamento_hello_world return flist", r_flistp);

	}

	return;
}

/*******************************************************************
 * fm_ac_treinamento_hello_world():
 * 
 * By default PIN_FLD_BOOLEAN in output flist is FALSE.If this flag is 
 * changed to 'true' then invoicing program shall assume that the 
 * out-of-box item and event processing is replaced by the customized 
 * code in the policy and skip the out-of-box processing.Hence if you 
 * change the  value to true ,then you have to write the code to select 
 * the items and events.
 *******************************************************************/
static void
fm_ac_treinamento_hello_world(
	pcm_context_t		*ctxp,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**ret_flistpp,
	pin_errbuf_t		*ebufp)
{
	pin_flist_t		*r_flistp = NULL;
	
	char *text = "Hello World";
	/*char *name = "Luan Lima";*/

	if (PIN_ERR_IS_ERR(ebufp)) {
		return;
	}
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	 * Prepare the return flist.
	 ***********************************************************/
	*ret_flistpp = (pin_flist_t *)NULL;

	r_flistp = PIN_FLIST_COPY(i_flistp, ebufp);

	/***********************************************************
	 * Empty policy
	 ***********************************************************/
	PIN_FLIST_FLD_SET(r_flistp, PIN_FLD_STATUS_MSG, text, ebufp);
	
	/*PIN_FLIST_FLD_SET(r_flistp, PIN_FLD_NAME, name, ebufp);*/
	/***********************************************************
	 * Error?
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, 
			"fm_ac_treinamento_hello_world: error", ebufp);
	}else {
		*ret_flistpp = r_flistp;
	}

	return;
}


