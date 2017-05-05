
<!-- README.md is generated from README.Rmd. Please edit that file -->
[![Build Status](https://travis-ci.org/coatless/rgen.svg)](https://travis-ci.org/coatless/rgen) [![Downloads](http://cranlogs.r-pkg.org/badges/rgen?color=brightgreen)](http://www.r-pkg.org/pkg/rgen) [![CRAN](http://www.r-pkg.org/badges/version/rgen)](https://cran.r-project.org/package=rgen) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html)

`rgen` - C++ Headers for Sampling Distributions
===============================================

The repository houses random distribution sampling routines based in [`armadillo`](https://github.com/conradsnicta/armadillo-code). These routines connect into *R*'s seed generator using [`RcppArmadillo`](https://github.com/RcppCore/RcppArmadillo). This package was spun off from the [`r-to-armadillo`](https://github.com/coatless/r-to-armadillo) project as it contained more direct references to internal *R* seeds.

Supported Distributions
-----------------------

Presently, `rgen` provides random sample functionality from:

-   [dirichlet](https://en.wikipedia.org/wiki/Dirichlet_distribution)
-   [multinomial](https://en.wikipedia.org/wiki/Multinomial_distribution)
-   [wishart](https://en.wikipedia.org/wiki/Wishart_distribution)
-   [inverse wishart](https://en.wikipedia.org/wiki/Inverse-Wishart_distribution)
-   [multivariate normal](https://en.wikipedia.org/wiki/Multivariate_normal_distribution)
-   [matrix normal](https://en.wikipedia.org/wiki/Matrix_normal_distribution)

Most notably, this is a header-only collection of functions. Therefore, this package can be linked to a pre-existing package instead of having to copy and paste the header files directly into your project's source.

Installation of `rgen`
----------------------

`rgen` is currently only available on GitHub, but should also be available on CRAN shortly.

To install the package, you must first have a compiler on your system that is compatible with R.

For help on obtaining a compiler consult:

-   [OS X](http://thecoatlessprofessor.com/programming/r-compiler-tools-for-rcpp-on-os-x/)
-   [Windows](http://thecoatlessprofessor.com/programming/rcpp/install-rtools-for-rcpp/)

With a compiler in hand, one can then install the package from GitHub by:

``` r
# install.packages("devtools")

devtools::install_github("coatless/rgen")
```

Using `rgen`
------------

There are two ways to use `rgen`. The first is to use `rgen` in a standalone script. The script is typically built using `sourceCpp()`. The second approach allows for `rgen` to be used within an R package.

### Standalone file usage

Within the `C++` file, the `rgen` package provides an Rcpp plugins' depends statement that must be included after `rgen.h` header. This plugin statement indicates that a dependency is `rgen`.

``` cpp
#include <RcppArmadillo.h> 
// [[Rcpp::depends(RcppArmadillo)]]

#include <rgen.h> 
// [[Rcpp::depends(rgen)]]
```

**Note:** Since `rgen` relies upon `RcppArmadillo`, you must include the `RcppArmadillo.h` header *and* include the traditional Rcpp dependency attribute, e.g. `// [[Rcpp::depends(RcppArmadillo)]]`.

For example, the following would allow for you to sample from an inverse wishart distribution:

``` cpp
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include <rgen.h>
// [[Rcpp::depends(rgen)]]

// Surface the riwishart function in the rgen package into R.
// [[Rcpp::export]]
arma::mat riwishart(unsigned int df, const arma::mat& S) {
    return rgen::riwishart(df, S);
}

/*** R
# Set seed for reproducibility
set.seed(111)

# Call the C++ function from R
riwishart(3, diag(2))
*/
```

### Package usage

To use `rgen` in your R package, modify the `DESCRIPTION` file by adding:

    LinkingTo: Rcpp, RcppArmadillo, rgen
    Imports:
        Rcpp (>= 0.12.10)

To use `C++11`, you **may** wish to add the following to your `src/Makevars` and `src/Makevars.win` file:

    CXX_STD = CXX11
