// -*- C++ -*-
// $Id: unprec_dwf_fermact_base_array_w.h,v 1.1 2003-11-15 03:22:41 edwards Exp $
/*! \file
 *  \brief Base class for unpreconditioned domain-wall-like fermion actions
 */

#ifndef __unprec_dwf_fermact_base_array_w_h__
#define __unprec_dwf_fermact_base_array_w_h__

#include "fermact_array.h"

using namespace QDP;

//! Base class for unpreconditioned domain-wall-like fermion actions
/*! \ingroup fermact
 *
 * Unprecondition domain-wall fermion action. The conventions used here
 * are specified in Phys.Rev.D63:094505,2001 (hep-lat/0005002).
 */

class UnprecDWFermActBaseArray : public UnprecWilsonTypeFermActArray<LatticeFermion>
{
public:
  //! Produce a linear operator for this action but with quark mass 1
  virtual const LinearOperator< multi1d<LatticeFermion> >* linOpPV(const multi1d<LatticeColorMatrix>& u) const = 0;

  //! Define quark propagator routine for 4D fermions
  void qprop(LatticeFermion& psi, 
	     const multi1d<LatticeColorMatrix>& u, 
	     const LatticeFermion& chi, 
	     enum InvType invType,
	     const Real& RsdCG, 
	     int MaxCG, int& ncg_had) const;

  //! Compute dS_f/dU
  multi1d<LatticeColorMatrix> dsdu(const multi1d<LatticeColorMatrix>& u,
				   const multi1d<LatticeFermion>& psi) const;
};

#endif
