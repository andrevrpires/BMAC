#my data
a <- 0.307641521 #my RG
b <- 0.10737290 #my Nusp

#the function to integrate
myfunc <- function(x) exp(-a*x)*cos(b*x)

#the importance sampling desity function to be used in the 3th method
#beta[0.99, 1]

#the controlvariate function to be used in the 4th method
controlvariate = function(x) myfunc(0) - x*(1 - myfunc(1))

p <- plot.function(myfunc, from = 0, to = 1) #a plot of the myfunc

#first monte carlo method
mc_crude <- function(intfunc, #the function to integrate
                     n, #the number of iterations
                     seed) {
  
        # crude monte carlo
        if(!missing(seed)) set.seed(seed)
        xzes <- runif(n, 0, 1)
        return(mean(intfunc(xzes)))
  
}

#second monte carlo method
mc_hitandmiss <- function(intfunc, #the function to integrate
                          n, #the number of iterations
                          seed) {

        # hit and miss monte carlo
        if(!missing(seed)) set.seed(seed)
        xzes <- runif(n, 0, 1)
        yzes <- runif(n, 0, 1)
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
                                  seed) {
  
                # importance sampling monte carlo
                if(!missing(seed)) set.seed(seed)
                xzes <- rbeta(n, 0.99, 1.05)
                return(mean(intfunc(xzes)/dbeta(xzes, 0.99, 1.05)))
  
}


# fourth monte carlo method
mc_controlvariate <- function(#the function to integrate
                              intfunc,
                              #the number of iterations
                              n,
                              #the function which reduce the variance
                              cv = controlvariate,
                              #the seed for the random number generator
                              seed) {
  
        # control variate monte carlo
        if(!missing(seed)) set.seed(seed)
        xzes <- runif(n, 0, 1)
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
                         ...) {
  
        #initializing variables
        n <- 1 #defining the values for the first try
        s <- 0 #the initial standard deviation must be zero
        errchance <- 1 #chance of error in probability, starting with "1"
        z <- (1 - CI)/2 + CI #the Z for the given confidence interval
        #a vector for all the means
        triesvector <- c(method(intfunc, n, ...)) 
      
        while(errchance > errtolerance | s == 0){
    
                n <- n + 1
                nth <- method(intfunc, n, ...) #nth mean
                triesvector <- c(triesvector, nth) #appending nth mean
                m <- mean(triesvector)
                s <- sd(triesvector) #nth mean variance
                cierror <- qnorm(z)*s/sqrt(n) #error for the given s and n
                errchance <- 2*cierror/m
                
        }
  
        #returning n and the achieved standard deviation
        return(c(n = n, variance = s^2, expected_value = m))
        
}


# usage

# to get n
# error = 1%, CI = 95%
ncr <- monte_carlos(myfunc, method = mc_crude)[1]
nhm <- monte_carlos(myfunc, method = mc_hitandmiss)[1]
nis <- monte_carlos(myfunc, method = mc_importancesampling)[1]
ncv <- monte_carlos(myfunc, method = mc_controlvariate)[1]

# crazy example: error = 2%, CI = 90%, crude monte carlos, seed = 23
crazy <- monte_carlos(myfunc,
                      errtolerance = 0.02,
                      CI = 0.90,
                      method = mc_crude#,
                      #warning: the seed will get hidden in your memory/workspace
                      #seed = 1
                      )

# to integrate the function, error = 1%, CI = 95%
icr <- monte_carlos(myfunc, method = mc_crude)[3]
ihm <- monte_carlos(myfunc, method = mc_hitandmiss)[3]
iis <- monte_carlos(myfunc, method = mc_importancesampling)[3]
icv <- monte_carlos(myfunc, method = mc_controlvariate)[3]