inline_cxx_plugin <- Rcpp:::Rcpp.plugin.maker(
    include.before = c("#include <RcppArmadillo.h>","#include <rgen.h>"),
    LinkingTo      = c("rgen", "RcppArmadillo", "Rcpp"),
    Depends        = c("rgen", "RcppArmadillo", "Rcpp"),
    libs           = "$(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)  $(SHLIB_OPENMP_CFLAGS)",
    package        = "rgen"
)
