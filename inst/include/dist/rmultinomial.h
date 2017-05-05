#ifndef RGEN_RMULTINOMIAL_H
#define RGEN_RMULTINOMIAL_H

#include <RcppArmadillo.h>

/**
 * Generate Multinomial Random Variable
 *
 * Sample a multinomial random variable for given probabilities.
 *
 * @param ps The probability of each category.
 * @return A vector from a multinomial with probability ps.
 * @author Steven Andrew Culpepper
 */
inline double rmultinomial(const arma::vec& ps){
    unsigned int C = ps.n_elem;
    double u = R::runif(0,1);
    arma::vec cps = cumsum(ps);
    arma::vec Ips = arma::zeros<arma::vec>(C);

    Ips.elem(arma::find(cps < u) ).fill(1.0);

    return sum(Ips);
}

#endif
