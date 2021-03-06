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
static	char	Sccs_id[] = "@(#)%Portal Version: fm_inv_pol_select.c:BillingVelocityInt:2:2006-Sep-05 04:27:10 %";
#endif

/*******************************************************************
 * Contains the AC_OP_TREINAMENTO_INSERT_UPDATE operation. 
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
op_ac_treinamento_insert_update_select(
	cm_nap_connection_t	*connp,
	int32			opcode,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**o_flistpp,
	pin_errbuf_t		*ebufp);

static void
fm_ac_treinamento_insert_update(
	pcm_context_t		*ctxp,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**ret_flistpp,
	pin_errbuf_t		*ebufp);

/*******************************************************************
 * Main routine for the PCM_OP_INV_POL_SELECT operation.
 *******************************************************************/
void
op_ac_treinamento_insert_update(
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
	if (opcode != AC_OP_TREINAMENTO_INSERT_UPDATE) {
		pin_set_err(ebufp, PIN_ERRLOC_FM,
			PIN_ERRCLASS_SYSTEM_DETERMINATE,
			PIN_ERR_BAD_OPCODE, 0, 0, opcode);
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_insert_update opcode error", ebufp);
		return;
	}

	/***********************************************************
	 * Debug: What we got.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_ac_treinamento_insert_update input flist", i_flistp);

	/***********************************************************
	 * Implementation
	 ***********************************************************/
	fm_ac_treinamento_insert_update(ctxp, flags, i_flistp, &r_flistp, ebufp);

	/***********************************************************
	 * Results.
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {

		/***************************************************
		 * Log errors
		 ***************************************************/
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_insert_update error", ebufp);

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
			"op_ac_treinamento_insert_update return flist", r_flistp);

	}

	return;
}

/*******************************************************************
 * fm_ac_treinamento_insert_update():
 * 
 * By default PIN_FLD_BOOLEAN in output flist is FALSE.If this flag is 
 * changed to 'true' then invoicing program shall assume that the 
 * out-of-box item and event processing is replaced by the customized 
 * code in the policy and skip the out-of-box processing.Hence if you 
 * change the  value to true ,then you have to write the code to select 
 * the items and events.
 *******************************************************************/
static void
fm_ac_treinamento_insert_update(
	pcm_context_t		*ctxp,
	int32				flags,
	pin_flist_t			*i_flistp,
	pin_flist_t			**ret_flistpp,
	pin_errbuf_t		*ebufp)
{
	pin_flist_t			*r_flistp = NULL;
	pin_flist_t			*tmp_flist_in = NULL;
	pin_flist_t			*tmp_flist_out = NULL;

	int					*reason = NULL;
	

	if (PIN_ERR_IS_ERR(ebufp)) {
		return;
	}
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	 * Prepare the return flist.
	 ***********************************************************/
	*ret_flistpp = (pin_flist_t *)NULL;

	/***********************************************************
	 * Empty policy
	 ***********************************************************/

	reason = PIN_FLIST_FLD_GET(i_flistp, PIN_FLD_REASON, 0, ebufp);
	if (reason != NULL)
	{
		if (*reason == 0)
		{
			tmp_flist_in = PIN_FLIST_COPY(i_flistp, ebufp);
			PIN_FLIST_FLD_DROP(tmp_flist_in, PIN_FLD_REASON, ebufp);
			
			PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_insert_update: insert flist in", tmp_flist_in);
			PCM_OP(ctxp, PCM_OP_CREATE_OBJ, 0, tmp_flist_in, &tmp_flist_out, ebufp);
			PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_insert_update: insert flist out", tmp_flist_out);

			r_flistp = PIN_FLIST_COPY(tmp_flist_out, ebufp);
		}
	}
   
	/***********************************************************
	 * Error?
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, 
			"fm_ac_treinamento_insert_update: error", ebufp);
	}else {
		*ret_flistpp = r_flistp;
	}

	PIN_FLIST_DESTROY_EX(&tmp_flist_in, ebufp);
	PIN_FLIST_DESTROY_EX(&tmp_flist_out, ebufp);
	return;
}


