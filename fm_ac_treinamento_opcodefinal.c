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
static	char	Sccs_id[] = "@(#)%Portal Version: fm_ac_treinamento_view.c:BillingVelocityInt:2:2006-Sep-05 04:27:10 %";
#endif

/*******************************************************************
 * Contains the AC_OP_TREINAMENTO_OPCODE_FINAL operation. 
 *******************************************************************/


#include <stdio.h> 
#include <string.h> 
 
#include "pcm.h"
#include "ops/inv.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "ac_ops.h"
#include "ac_insert_update.h"


/*******************************************************************
 * Routines contained within.
 *******************************************************************/
EXPORT_OP void
op_ac_treinamento_opcode_final(
	cm_nap_connection_t	*connp,
	int32			opcode,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**o_flistpp,
	pin_errbuf_t		*ebufp);

static void
fm_ac_treinamento_opcode_final(
	pcm_context_t		*ctxp,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**ret_flistpp,
	pin_errbuf_t		*ebufp);

/*******************************************************************
 * Main routine for the AC_OP_TREINAMENTO_VIEW operation.
 *******************************************************************/
void
op_ac_treinamento_opcode_final(
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
	if (opcode != AC_OP_TREINAMENTO_OPCODE_FINAL) {
		pin_set_err(ebufp, PIN_ERRLOC_FM,
			PIN_ERRCLASS_SYSTEM_DETERMINATE,
			PIN_ERR_BAD_OPCODE, 0, 0, opcode);
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_opcode_final opcode error", ebufp);
		return;
	}

	/***********************************************************
	 * Debug: What we got.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_ac_treinamento_view input flist", i_flistp);

	/***********************************************************
	 * Implementation
	 ***********************************************************/
	fm_ac_treinamento_opcode_final(ctxp, flags, i_flistp, &r_flistp, ebufp);

	/***********************************************************
	 * Results.
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {

		/***************************************************
		 * Log errors
		 ***************************************************/
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_ac_treinamento_opcode_final error", ebufp);

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
			"op_ac_treinamento_opcode_final return flist", r_flistp);

	}

	return;
}

/*******************************************************************
 * fm_ac_treinamento_opcode_final():
 * 
 * By default PIN_FLD_BOOLEAN in output flist is FALSE.If this flag is 
 * changed to 'true' then invoicing program shall assume that the 
 * out-of-box item and event processing is replaced by the customized 
 * code in the policy and skip the out-of-box processing.Hence if you 
 * change the  value to true ,then you have to write the code to select 
 * the items and events.
 *******************************************************************/
static void
fm_ac_treinamento_opcode_final(
	pcm_context_t		*ctxp,
	int32			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**ret_flistpp,
	pin_errbuf_t		*ebufp)
{
	pin_flist_t		*r_flistp = NULL;
	
	poid_t			*client_poid=NULL;
	poid_t                      *compra_poid=NULL; 
	poid_t                      *account_poid = NULL;
	
	pin_flist_t                 *read_flist_in=NULL;
	pin_flist_t                 *read_flist_out=NULL;
	pin_flist_t                 *create_flist_in=NULL;
 	pin_flist_t                 *create_flist_out=NULL;

	char                        *name = NULL;
         char 			 *email = NULL;

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
	client_poid = PIN_FLIST_FLD_GET(i_flistp, PIN_FLD_POID, 0, ebufp);
	
	read_flist_in = PIN_FLIST_CREATE(ebufp);
	PIN_FLIST_PUT(read_flist_in, PIN_FLD_POID, client_poid, ebufp);

	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_opcode_final: read flist in", read_flist_in);
	PCM_OP(ctxp, PCM_OP_READ_OBJ, 0, read_flist_in, &read_flist_out, ebufp);
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_opcode_final: read flist out", read_flist_out);

	if (read_flist_out != NULL){
		account_poid = PIN_FLIST_FLD_GET(read_flist_out, PIN_FLD_ACCOUNT_OBJ, 0, ebufp);
		name = PIN_FLIST_FLD_GET(read_flist_out, PIN_FLD_NAME, 0, ebufp);
                  email = PIN_FLIST_FLD_GET(read_flist_out, PIN_FLD_EMAIL_ADDR, 0, ebufp);
		
		create_flist_in= PIN_FLIST_CREATE(ebufp);
		compra_poid = PIN_POID_CREATE(1, "/compras", -1, ebufp);
		PIN_FLIST_PUT(create_flist_in, PIN_FLD_POID, compra_poid, ebufp);
		PIN_FLIST_SET(create_flist_in, PIN_FLD_NAME, name , ebufp);
		PIN_FLIST_SET(create_flist_in, PIN_FLD_EMAIL_ADDR, email , ebufp);
		PIN_FLIST_SET(create_flist_in, PIN_FLD_ACCOUNT_OBJ, account_poid , ebufp);

		PIN_FLIST_FLD_COPY(i_flistp, PIN_FLD_VALUE, create_flist_in, PIN_FLD_VALUE, ebufp);
		PIN_FLIST_FLD_COPY(i_flistp, PIN_FLD_PRODUCT_NAME, create_flist_in, PIN_FLD_PRODUCT_NAME,ebufp);


		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_opcode_final: create flist in", create_flist_in);
	 	PCM_OP(ctxp, PCM_OP_CREATE_OBJ, 0,create_flist_in, &create_flist_out, ebufp);
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_ac_treinamento_opcode_final: create flist out", create_flist_out);

		r_flistp = PIN_FLIST_COPY(create_flist_out, ebufp);
		
		PIN_FLIST_DESTROY_EX(&create_flist_in, NULL);
		PIN_FLIST_DESTROY_EX(&create_flist_out, NULL);
		
	}
		
	
	
	
	/***********************************************************
	 * Error?
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, 
			"fm_ac_treinamento_opcode_final: error", ebufp);
	}else {
		*ret_flistpp = PIN_FLIST_COPY(r_flistp, ebufp);
		PIN_FLIST_DESTROY_EX(&r_flistp, NULL);
		PIN_FLIST_DESTROY_EX(&read_flist_in, NULL);
		PIN_FLIST_DESTROY_EX(&read_flist_out, NULL);
	}

	return;
}
