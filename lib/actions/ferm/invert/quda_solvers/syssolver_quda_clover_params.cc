#include "actions/ferm/invert/quda_solvers/syssolver_quda_clover_params.h"
#include "chromabase.h"
#include "io/xml_group_reader.h"
#include "chroma_config.h"



using namespace QDP;

namespace Chroma {
  GCRInnerSolverParams::GCRInnerSolverParams(XMLReader& xml, 
					     const std::string& path)
  {
    XMLReader paramtop(xml, path);
    read(paramtop, "RsdSloppy", tolSloppy);
    read(paramtop, "MaxIterSloppy", maxIterSloppy);
    read(paramtop, "NKrylov", gcrNkrylov);
    read(paramtop, "VerboseP", verboseInner);
    read(paramtop, "InvTypeSloppy", invTypeSloppy);
  };

  void read(XMLReader& xml, const std::string& path, 
	    GCRInnerSolverParams& p)
  {
    GCRInnerSolverParams tmp(xml, path);
    p = tmp;
  }

  
  
  void write(XMLWriter& xml, const std::string& path, 
	     const GCRInnerSolverParams& p) {
    push(xml, path);
    write(xml, "RsdSloppy", p.tolSloppy);
    write(xml, "MaxIterSloppy", p.maxIterSloppy);
    write(xml, "NKrylov", p.gcrNkrylov);
    write(xml, "VerboseP", p.verboseInner);
    write(xml, "InvTypeSloppy", p.invTypeSloppy);
    pop(xml);

  }

  SysSolverQUDACloverParams::SysSolverQUDACloverParams(XMLReader& xml, 
						       const std::string& path)
  {
    XMLReader paramtop(xml, path);

    read(paramtop, "MaxIter", MaxIter);
    read(paramtop, "RsdTarget", RsdTarget);
    read(paramtop, "CloverParams", CloverParams);
    read(paramtop, "AntiPeriodicT", AntiPeriodicT);

    read(paramtop, "Delta", Delta);
  

    read(paramtop, "SolverType", solverType);

    if ( paramtop.count("Verbose") > 0 ) { 
      read(paramtop, "Verbose", verboseP);
    }
    else { 
      verboseP = false;
    }
    if ( paramtop.count("AsymmetricLinop") > 0 ) { 
      read(paramtop, "AsymmetricLinop", asymmetricP);
    }
    else { 
      asymmetricP = false; // Symmetric is default 
    }

    if( paramtop.count("CudaPrecision") > 0 ) {
      read(paramtop, "CudaPrecision", cudaPrecision);
    }
    else { 
      cudaPrecision = DEFAULT;
    }

    if( paramtop.count("CudaSloppyPrecision") > 0 ) {
      read(paramtop, "CudaSloppyPrecision", cudaSloppyPrecision);
    }
    else { 
      cudaSloppyPrecision = DEFAULT;
    }

    if( paramtop.count("CudaReconstruct") > 0 ) {
      read(paramtop, "CudaReconstruct", cudaReconstruct);
    }
    else { 
      cudaReconstruct = RECONS_12;
    }

    if( paramtop.count("CudaSloppyReconstruct") > 0 ) {
      read(paramtop, "CudaSloppyReconstruct", cudaSloppyReconstruct);
    }
    else { 
      cudaSloppyReconstruct = RECONS_12;
    }

    if( paramtop.count("AxialGaugeFix") > 0 ) {
      read(paramtop, "AxialGaugeFix", axialGaugeP);
    }
    else { 
      axialGaugeP = false;
    }

    if( paramtop.count("SilentFail") > 0) {
      read(paramtop, "SilentFail", SilentFailP);
    }
    else { 
      SilentFailP = false;
    }

    if( paramtop.count("RsdToleranceFactor") > 0 ) { 
       read(paramtop, "RsdToleranceFactor", RsdToleranceFactor);
    }
    else { 
       RsdToleranceFactor = Real(10); // Tolerate an order of magnitude difference by default.
    }

#ifdef BUILD_QUDA_0_3
    if( paramtop.count("AutotuneDslash") > 0 ) { 
      read(paramtop, "AutotuneDslash", tuneDslashP);
    }
    else { 
      tuneDslashP = false;
    }
    QDPIO::cout << "tuneDslasP = " << tuneDslashP << endl;

    if( paramtop.count("CacheAutotuningResults") > 0 ) { 
      read(paramtop, "CacheAutotuningResults", cacheDslashTuningP);
    }
    else { 
      cacheDslashTuningP = true;
    }
    QDPIO::cout << "cacheDslashTuning = " << cacheDslashTuningP << endl;

    if( paramtop.count("GCRInnerParams") > 0 ) {
      innerParams = new GCRInnerSolverParams(paramtop, "./GCRInnerParams");
      innerParamsP = true;
    }
    else { 
      innerParamsP = false;
    }
#endif 
  }

  void read(XMLReader& xml, const std::string& path, 
	    SysSolverQUDACloverParams& p)
  {
    SysSolverQUDACloverParams tmp(xml, path);
    p = tmp;
  }

  void write(XMLWriter& xml, const std::string& path, 
	     const SysSolverQUDACloverParams& p) {
    push(xml, path);
    write(xml, "MaxIter", p.MaxIter);
    write(xml, "RsdTarget", p.RsdTarget);
    write(xml, "CloverParams", p.CloverParams);
    write(xml, "AntiPeriodicT", p.AntiPeriodicT);
    write(xml, "Delta", p.Delta);
    write(xml, "SolverType", p.solverType);
    write(xml, "Verbose", p.verboseP);
    write(xml, "AsymmetricLinop", p.asymmetricP);
    write(xml, "CudaPrecision", p.cudaPrecision);
    write(xml, "CudaReconstruct", p.cudaReconstruct);
    write(xml, "CudaSloppyPrecision", p.cudaSloppyPrecision);
    write(xml, "CudaSloppyReconstruct", p.cudaSloppyReconstruct);
    write(xml, "AxialGaugeFix", p.axialGaugeP);
    write(xml, "SilentFail", p.SilentFailP);
    write(xml, "RsdToleranceFactor", p.RsdToleranceFactor);

#ifdef BUILD_QUDA_0_3
    write(xml, "AutotuneDslash", p.tuneDslashP);
    write(xml, "CacheAutotuningResults", p.cacheDslashTuningP);
    if( p.innerParamsP ) { 
      write(xml, "GCRInnerParams", *(p.innerParams));
    }
#endif

    pop(xml);

  }



}