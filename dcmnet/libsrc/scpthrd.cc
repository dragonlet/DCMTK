/*
 *
 *  Copyright (C) 2013, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  dcmnet
 *
 *  Author:  Michael Onken
 *
 *  Purpose: Class for implementing a threaded Service Class Provider worker.
 *
 */

#include "dcmtk/config/osconfig.h" /* make sure OS specific configuration is included first */

#include "dcmtk/dcmnet/scpthrd.h"
#include "dcmtk/dcmnet/diutil.h"

// ----------------------------------------------------------------------------

DcmThreadSCP::DcmThreadSCP()
 : DcmSCP()
{
}

// ----------------------------------------------------------------------------

DcmThreadSCP::~DcmThreadSCP()
{
  // Nothing to do
 }

// ----------------------------------------------------------------------------

DcmSharedSCPConfig& DcmThreadSCP::getSharedConfig()
{
  return m_cfg;
}

// ----------------------------------------------------------------------------

OFCondition DcmThreadSCP::setSharedConfig(const DcmSharedSCPConfig& config)
{
  if (isConnected())
  {
    return EC_IllegalCall;
  }
  m_cfg = config;
  return EC_Normal;
}

// ----------------------------------------------------------------------------

OFCondition DcmThreadSCP::run(T_ASC_Association* incomingAssoc)
{
  if (incomingAssoc == NULL)
  {
    DCMNET_ERROR("Illegal Association handed to DcmSCP's listen(assoc) method");
    return DIMSE_ILLEGALASSOCIATION;
  }
  if (isConnected())
    return DIMSE_ILLEGALASSOCIATION;

  m_assoc = incomingAssoc;

  return processAssociationRQ();
}
