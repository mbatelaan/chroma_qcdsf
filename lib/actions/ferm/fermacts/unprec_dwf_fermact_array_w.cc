// $Id: unprec_dwf_fermact_array_w.cc,v 1.3 2003-11-15 03:54:40 edwards Exp $
/*! \file
 *  \brief Unpreconditioned domain-wall fermion action
 */

#include "chromabase.h"
#include "actions/ferm/fermacts/unprec_dwf_fermact_array_w.h"
#include "actions/ferm/linop/unprec_dwf_linop_array_w.h"
#include "actions/ferm/linop/lmdagm_w.h"

//! Creation routine
/*! \ingroup fermact
 *
 * \param WilsonMass_   DWF height    (Read)
 * \param m_q_          quark mass    (Read)
 * \param N5_           extent of DW flavor space   (Read)
 */
void UnprecDWFermActArray::create(const Real& WilsonMass_, const Real& m_q_, int N5_)
{
  WilsonMass = WilsonMass_;
  m_q = m_q_;
  N5  = N5_;

  a5  = 1.0;

//    CoeffWilsr_s = (AnisoP) ? Wilsr_s / xiF_0 : 1;
}


//! Produce a linear operator for this action
/*!
 * \ingroup fermact
 *
 * The operator acts on the entire lattice
 *
 * \param u 	    gauge field     	       (Read)
 */
const LinearOperator<multi1d<LatticeFermion> >* 
UnprecDWFermActArray::linOp(const multi1d<LatticeColorMatrix>& u) const
{
  return new UnprecDWLinOpArray(u,WilsonMass,m_q,N5);
}

//! Produce a M^dag.M linear operator for this action
/*!
 * \ingroup fermact
 *
 * The operator acts on the entire lattice
 *
 * \param u 	    gauge field     	       (Read)
 */
const LinearOperator<multi1d<LatticeFermion> >* 
UnprecDWFermActArray::lMdagM(const multi1d<LatticeColorMatrix>& u) const
{
  LinearOperator<multi1d<LatticeFermion> >* mdagm = 
    new lmdagm<multi1d<LatticeFermion> >(UnprecDWLinOpArray(u,WilsonMass,m_q,N5));
  return mdagm;
}

//! Produce a linear operator for this action but with quark mass 1
/*!
 * \ingroup fermact
 *
 * The operator acts on the entire lattice
 *
 * \param u 	    gauge field     	       (Read)
 */
const LinearOperator<multi1d<LatticeFermion> >* 
UnprecDWFermActArray::linOpPV(const multi1d<LatticeColorMatrix>& u) const
{
  return new UnprecDWLinOpArray(u,WilsonMass,1.0,N5);  // fixed to quark mass 1
}

