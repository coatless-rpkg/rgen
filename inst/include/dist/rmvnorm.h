#ifndef RGEN_RMVNORM_H
#define RGEN_RMVNORM_H

#include <RcppArmadillo.h>

// @title Generate Random Multivariate Normal Distribution
// @description Creates a random Multivariate Normal when given number of obs, mean, and sigma.
// @param n  An \code{int}, which gives the number of observations.  (> 0)
// @param mu A \code{vector} length m that represents the means of the normals.
// @param S  A \code{matrix} with dimensions m x m that provides Sigma, the covariance matrix.
// @return A \code{matrix} that is a Multivariate Normal distribution
// @seealso \code{\link{TwoPLChoicemcmc}} and \code{\link{probitHLM}}
// @author James J Balamuta
// @examples
// #Call with the following data:
// rmvnorm(2, c(0,0), diag(2))
inline arma::mat rmvnorm(unsigned int n, const arma::vec& mu, const arma::mat& S){
    unsigned int ncols = S.n_cols;
    arma::mat Y(n, ncols);
    Y.imbue( norm_rand ) ;
    return arma::repmat(mu, 1, n).t() + Y * arma::chol(S);
}

#endif
