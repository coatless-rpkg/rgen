#ifndef RGEN_RMULTINOMIAL_H
#define RGEN_RMULTINOMIAL_H

#include <RcppArmadillo.h>

// @title Generate Multinomial Random Variable
// @description Sample a multinomial random variable for given probabilities.
// @usage rmultinomial(ps)
// @param ps A \code{vector} for the probability of each category.
// @return A \code{vector} from a multinomial with probability ps.
// @author Steven Andrew Culpepper
double rmultinomial(const arma::vec& ps){
    unsigned int C = ps.n_elem;
    double u = R::runif(0,1);
    arma::vec cps = cumsum(ps);
    arma::vec Ips = arma::zeros<arma::vec>(C);

    Ips.elem(arma::find(cps < u) ).fill(1.0);

    return sum(Ips);
}

#endif
