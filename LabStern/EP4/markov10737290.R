c <- 1.307641521 #my RG
d <- 1.10737290 #my NUSP

#the potential for stationary distribution
s <- function(x) ifelse(x >= 0, dgamma(x, c)*abs(cos(d*x)), 0)

#the proposal distribution(for the kernel)
p <- function(x) rnorm(1, x, 2)

#one step of metropolis algorithm
step <- function(x, #our previous x
                 s, #the potential for stationary distribution
                 p,  #the proposal distribution
                 mode = "barker" #the acceptance probability mode 
                 ) {
  
  xp <- p(x)#Pick new point
  #Acceptance probability:
  if(mode == "hastings"){
    alpha <- ifelse(s(x) != 0, min(1, s(xp)/s(x)), 1)
  }else if(mode == "barker"){
    alpha <- min(1, s(xp)/(s(x)+s(xp)))
  }  
  
  #accept new point with probability alpha
  if (runif(1) < alpha)
    x <- xp

  return(x)#returning the point:
}

run <- function(x, #the initial x
                s, #the potential for stationary distribution
                p,  #the proposal distribution
                nsteps #the number of samples
                ) {
  
  #this function generates samples of the metropolis algorithm
  xzes <- vector("numeric", nsteps)#initilize the xzes vector
  for (i in seq_len(nsteps)){
    xzes[i] <- x <- step(x, s, p)#iterate to fill the vector
  }
  return(xzes)#return
}


mcmc <- function(s, #the potential for stationary distribution
                 p, #proposal distribution
                 lower, #lower bound of integration
                 upper, #upper bound of integration
                 nsteps = 1000 #the number of samples
                 ) {
  
  #this function calculates the integral for a given interval
  first <- (upper-lower)/2
  #the vector of samples
  res <- run(first, s, p, nsteps)
  #the proportion of samples inside our interval
  value <- length(res[res > lower & res < upper])/nsteps
  #return the integral
  return(value)
  
}


tuning <- function(s,
                    maxsigma,
                    nsteps = 1000){
  
  acvector <- vector() #initializing autocorrelation vector
  maxsigma <- maxsigma*10 #multilplying to iterate by 0.1
  #iterate over a range of variances to observe the autocorrelation
  for(s in 1:maxsigma){
    
    mysigma <- s/10 #multilplying to iterate by 0.1
    p <- function(x) rnorm(1, x, mysigma)
    res <- run(0, s, p, nsteps)
    actotal <- sum(abs(acf(res)$acf))#summing total autocorrelation
    acvector <- c(acvector, actotal)#fill vector of autocorrelations
    
  }
  
  plot(acvector, type = "l")#plot autocorrelation vector

  optimalsigma <- match(min(acvector), acvector)/10
  return(optimalsigma)  #return the best sigma

  
}


mcmc_integrate <- function(s, #the potential for stationary distribution
                           p, #proposal distribution
                           lower, #lower bound of integration
                           upper, #upper bound of integration
                           nruns = 8000 #the number of runs
                           ){
  
  #this function calculates the integral for a given interval
  
  #initiate the vector of the estimates
  estimates <- vector("numeric", nruns)
  #progress bar for the iteration progress
  pb <- txtProgressBar(min = 1, max = nruns, style = 3)
  for(i in 1:nruns){
      estimates[i] <- mcmc(s, p, lower, upper)#fill the vector
      setTxtProgressBar(pb, i)#update progress bar
  }
  close(pb)#close progress bar
  
  #return data
  return(c(I = mean(estimates), #my integral
           Isd = sd(estimates)) #variance of the estimate
         )
  
}


mcmc_precision <- function(#the mathematical function to integrate
                           s,
                           #the R function to evaluate
                           p,
                           #the bounds to our integration
                           lower, upper,
                           #the confidence interval
                           CI = 0.95,
                           #the wanted error tolerance
                           errtolerance = 0.01,
                           #the limit to the iterations
                           nmax = 20000
                           ) {
  
  #initializing variables
  n <- 0 #defining the values for the first try
  s <- 0 #the initial standard deviation must be zero
  errchance <- 1 #chance of error in probability, starting with "1"
  z <- (1 - CI)/2 + CI #the Z for the given confidence interval
  #this progress bar shows how much you are close to the target precision
  pb <- txtProgressBar(min = 0, max = errtolerance/errtolerance, style = 3)

  while(errchance > errtolerance & n != nmax){
    
    n <- n + 1000  #number of runs
    print(paste("n =", n)) #print which n refers to that progress
    nth <- mcmc_integrate(s, p, lower, upper, n) 
    m <- nth[1] #nth mean
    s <- nth[2] #nth mean variance
    cierror <- qnorm(z)*s/sqrt(n) #error for the given s and n
    errchance <- 2*cierror/m #errchance
    print("Precision:")
    setTxtProgressBar(pb, errtolerance/errchance)#update progress bar
    
  }
  
  close(pb)
  #returning
  return(c(n = n, #the minimum number of tries to achieve the desired precision
           variance = s^2, #the achieved standard deviation
           expected_value = m, #the value of our integral
           error = errchance) #the estimated error
  )
  
}



#for testing the real distribution
z <- integrate(s, -Inf, Inf)$value
S <- function(x) s(x)/z