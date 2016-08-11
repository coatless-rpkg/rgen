#ifndef RGEN_RIWISHART_H
#define RGEN_RIWISHART_H

#include <RcppArmadillo.h>
#include <rwishart.h>

// @title Generate Random Inverse Wishart Distribution
// @description Creates a random inverse wishart distribution when given degrees of freedom and a sigma matrix.
// @param df An \code{int} that represents the degrees of freedom.  (> 0)
// @param S A \code{matrix} with dimensions m x m that provides Sigma, the covariance matrix.
// @return A \code{matrix} that is an inverse wishart distribution.
// @seealso \code{\link{rwishart}}
// @author James J Balamuta
// @examples
// #Call with the following data:
// riwishart(3, diag(2))
// [[Rcpp::export]]
arma::mat riwishart(unsigned int df, const arma::mat& S){
    return rwishart(df, S.i()).i();
}

#endif
