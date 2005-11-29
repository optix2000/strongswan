/**
 * @file initiate_ike_sa_job.c
 * 
 * @brief Implementation of initiate_ike_sa_job_t.
 * 
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


#include <stdlib.h>

#include "initiate_ike_sa_job.h"

#include <utils/allocator.h>


typedef struct private_initiate_ike_sa_job_t private_initiate_ike_sa_job_t;

/**
 * Private data of an initiate_ike_sa_job_t Object
 */
struct private_initiate_ike_sa_job_t {
	/**
	 * public initiate_ike_sa_job_t interface
	 */
	initiate_ike_sa_job_t public;
	
	/**
	 * Name of the assigned configuration
	 */
	char *configuration_name;
};


/**
 * Implements initiate_ike_sa_job_t.get_type.
 */
static job_type_t get_type(private_initiate_ike_sa_job_t *this)
{
	return INITIATE_IKE_SA;
}

/**
 * Implements initiate_ike_sa_job_t.get_configuration_name.
 */
static char *get_configuration_name(private_initiate_ike_sa_job_t *this)
{
	return this->configuration_name;
}

/**
 * Implements job_t.destroy.
 */
static void destroy(job_t *job)
{
	private_initiate_ike_sa_job_t *this = (private_initiate_ike_sa_job_t *) job;
	allocator_free(this->configuration_name);
	allocator_free(this);
}

/*
 * Described in header
 */
initiate_ike_sa_job_t *initiate_ike_sa_job_create(char *configuration_name)
{
	private_initiate_ike_sa_job_t *this = allocator_alloc_thing(private_initiate_ike_sa_job_t);
	
	/* interface functions */
	this->public.job_interface.get_type = (job_type_t (*) (job_t *)) get_type;
	/* same as destroy */
	this->public.job_interface.destroy_all = (void (*) (job_t *)) destroy;
	this->public.job_interface.destroy = destroy;
	
	/* public functions */
	this->public.get_configuration_name = (char * (*)(initiate_ike_sa_job_t *)) get_configuration_name;
	this->public.destroy = (void (*)(initiate_ike_sa_job_t *)) destroy;
	
	/* private variables */
	this->configuration_name = allocator_alloc(strlen(configuration_name) + 1);
	strcpy(this->configuration_name,configuration_name);
	
	return &(this->public);
}
