library(randtoolbox)
#initialize Torus algorithm
torus(sample(1:100, 1))

#my data
alfa <- 0.307641521 #my RG
beta <- 0.10737290 #my Nusp

#the function to integrate
myfunc <- function(x) exp(-alfa*x)*cos(beta*x)

#the controlvariate function to be used in the 4th method
controlvariate <- function(x) 1 - x*0.269055

#the importance sampling density function G to be used in the 3th method
a <- -0.269055
b <- 1 + 0.1345275 #summing the difference necessary to have a density function
g <- function(x) a*x + b
G <- function(x) a*(x^2)/2 + b*x #integral of G
G_inverse <- function(y) (-b - sqrt(b^2 - 4*(a/2)*(-y)))/2*(a/2)

#p <- plot.function(myfunc, from = 0, to = 1) #a plot of myfunc

#first monte carlo method
mc_crude <- function(intfunc, #the function to integrate
                     n, #the number of iterations
                     seed,
                     usequasi = TRUE) {
  
        # crude monte carlo
        if(!missing(seed)) set.seed(seed)
        if(usequasi){
          xzes <- torus(n, init = FALSE)
        }else{
        xzes <- runif(n, 0, 1)
        }
        return(mean(intfunc(xzes)))
  
}

#second monte carlo method
mc_hitandmiss <- function(intfunc, #the function to integrate
                          n, #the number of iterations
                          seed,
                          usequasi = "yzes") {

        # hit and miss monte carlo
        if(!missing(seed)) set.seed(seed)#is a seed set?
        if(usequasi == "xzes"){#xzes as quasi-random
          xzes <- torus(n, init = FALSE)
          yzes <- runif(n, 0, 1)
        }else if(usequasi == "yzes"){#yzes as quasi-random
          xzes <- runif(n, 0, 1)
          yzes <- torus(n, init = FALSE)
        }else if(usequasi == "both"){#both as quasi-random
          xzes <- torus(n, init = FALSE)
          yzes <- torus(n, init = FALSE)
        }else if(usequasi == "none"){#no use of quasi-random
          xzes <- runif(n, 0, 1)
          yzes <- runif(n, 0, 1)
        }
        n_inside <- sum(yzes < intfunc(xzes)) #number of hits
        return(n_inside/n) # hits/n
}

# third monte carlo method

mc_importancesampling <- function(#the function to integrate
                                  intfunc,
                                  #the number of iterations
                                  n,
                                  #the function which gives the importance
                                  #is = importancesampling,
                                  #the seed for the random number generator
                                  seed,
                                  usequasi = TRUE) {
  
                # importance sampling monte carlo
                if(!missing(seed)) set.seed(seed)
                if(usequasi){
                  U <- torus(n, init = FALSE)
                }else{
                  U <- runif(n, 0, 1)
                }
                #xzes <- qbeta(U, 0.99, 1.05)
                #return(mean(intfunc(xzes)/dbeta(xzes, 0.99, 1.05)))
                xzes <- G_inverse(U)
                return(mean(intfunc(xzes)/G(xzes)))
                
}


# fourth monte carlo method
mc_controlvariate <- function(#the function to integrate
                              intfunc,
                              #the number of iterations
                              n,
                              #the function which reduce the variance
                              cv = controlvariate,
                              #the seed for the random number generator
                              seed,
                              usequasi = FALSE
                              ) {
  
        # control variate monte carlo
        if(!missing(seed)) set.seed(seed)
        if(usequasi){
          xzes <- torus(n, init = FALSE)
        }else{
          xzes <- runif(n, 0, 1)
        }
        Icv <- integrate(cv, 0, 1)[1]$value
        return(mean(intfunc(xzes)) + (Icv - mean(cv(xzes))))
  
}

monte_carlos <- function(#the mathematical function to integrate
                         intfunc,
                         #the R function to evaluate
                         method,
                         #the confidence interval
                         CI = 0.95,
                         #the wanted error tolerance
                         errtolerance = 0.01,
                         #the seed for the random number generator
                         #use quasi-random numbers?
                         ...) {
  
        #initializing variables
        n <- 1 #defining the values for the first try
        s <- 0 #the initial standard deviation must be zero
        errchance <- 1 #chance of error in probability, starting with "1"
        z <- (1 - CI)/2 + CI #the Z for the given confidence interval
        #a vector for all the means
        triesvector <- c(method(intfunc, n, ...))
      
        while(errchance >= errtolerance | s == 0){
    
                n <- n + 1
                nth <- method(intfunc, n, ...) #nth mean
                triesvector <- c(triesvector, nth) #appending nth mean
                m <- mean(triesvector)
                s <- sd(triesvector) #nth mean variance
                cierror <- qnorm(z)*s/sqrt(n) #error for the given s and n
                errchance <- 2*cierror/m
                
        }
        #returning n and the achieved standard deviation
        return(c(n = n,
                 variance = s^2,
                 expected_value = m,
                 error = errchance))
}

#examples

if(FALSE){
# to get n
# error = 1%, CI = 95%
ncr <- monte_carlos(myfunc, method = mc_crude)[1]
nhm <- monte_carlos(myfunc, method = mc_hitandmiss)[1]
nis <- monte_carlos(myfunc, method = mc_importancesampling)[1]
ncv <- monte_carlos(myfunc, method = mc_controlvariate)[1]

# to integrate the function, error = 1%, CI = 95%
icr <- monte_carlos(myfunc, method = mc_crude)[3]
ihm <- monte_carlos(myfunc, method = mc_hitandmiss)[3]
iis <- monte_carlos(myfunc, method = mc_importancesampling)[3]
icv <- monte_carlos(myfunc, method = mc_controlvariate)[3]

# to get the R function error tax
errcr <- monte_carlos(myfunc, method = mc_crude)[4]
errhm <- monte_carlos(myfunc, method = mc_hitandmiss)[4]
erris <- monte_carlos(myfunc, method = mc_importancesampling)[4]
errcv <- monte_carlos(myfunc, method = mc_controlvariate)[4]

#crazy example: error = 2%, CI = 90%, crude monte carlos, seed = 23
crazy <- monte_carlos(myfunc,
                     errtolerance = 0.02,
                     CI = 0.90,
                     method = mc_crude#,
                      #warning: the seed will get hidden in your memory/workspace
                      #seed = 1
)
}
if(FALSE){
qncr <- monte_carlos(myfunc, method = mc_crude)[1]
qnis <- monte_carlos(myfunc, method = mc_importancesampling)[1]
qncv <- monte_carlos(myfunc, method = mc_controlvariate)[1]
pncr <- monte_carlos(myfunc, method = mc_crude, usequasi = FALSE)[1]
pnis <- monte_carlos(myfunc, method = mc_importancesampling, usequasi = FALSE)[1]
pncv <- monte_carlos(myfunc, method = mc_controlvariate, usequasi = FALSE)[1]
ynhm <- monte_carlos(myfunc, method = mc_hitandmiss)[1]
xnhm <- monte_carlos(myfunc, method = mc_hitandmiss, usequasi = "xzes")[1]
xynhm <- monte_carlos(myfunc, method = mc_hitandmiss, usequasi = "both")[1]
nnhm <- monte_carlos(myfunc, method = mc_hitandmiss, usequasi = "none")[1]

return(c(a = pncr,
         b = pnis,
         c = pncv,
         d = qncr,
         e = qnis,
         f = qncv,
         g = ynhm,
         h = xnhm,
         i = xynhm,
         j = nnhm))
}