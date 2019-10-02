library(MASS)
library(doParallel)
registerDoParallel()


#the null hypothesis
h <- function(t, xzes){
  
  (t^xzes[1])*((1 - t - (1-sqrt(t))^2)^xzes[2])*((1-sqrt(t))^(2*xzes[3]))
  
}

#the potential for stationary distribution
s <- function(theta, xzes){
  
  (theta[1]^xzes[1])*(theta[2]^xzes[2])*(theta[3]^xzes[3])
  
}

sigma <- rbind(c(0.07, 0), c(0, 0.07))

#the proposal distribution(for the kernel)
p <- function(previous, sigma){
  
  theta <- numeric(3)
  repeat{
    step <- mvrnorm(1, previous[1:2], sigma)
    if(step[1] >= 0 & step[2] >= 0 &
       step[1] <= 1 & step[2] <= 1 &
       step[1] + step[2] <= 1){
      
      break
    }
  }
  
  theta[1] <- step[1] 
  theta[2] <- step[2]
  theta[3] <- 1 - theta[1] - theta[2]
  
  return(theta)
  
}

#one step of metropolis algorithm
step <- function(previous, #our previous step
                 s, #the potential for stationary distribution
                 xzes, #the fixed parameters for the stationary distribution 
                 p,  #the proposal distribution
                 sigma, #the sigma for the proposal distribution
                 mode = "barker" #the acceptance probability mode 
) {
  
  
  previousresult <- s(previous, xzes)
  dados <- c(previous, previousresult)
  newstep <- p(previous, sigma)#Pick new point
  newresult <- s(newstep, xzes)
  #Acceptance probability:
  if(mode == "hastings"){
    alpha <- ifelse(previousresult != 0,
                    min(1, newresult/previousresult),
                    1)
  }else if(mode == "barker"){
    alpha <- min(1, newresult/(previousresult+newresult))
  }  
  
  #accept new point with probability alpha
  if (runif(1) < alpha)
    dados <- c(newstep, newresult)
  
  return(dados)#returning the point:
}

run <- function(theta, #the initial theta
                s, #the potential for stationary distribution
                xzes, #the fixed parameters for the stationary distribution 
                p,  #the proposal distribution
                sigma, #the sigma for the proposal distribution
                nsteps, #the number of samples
                burnin = 4 # the number of samples to pass for each iteration
) {
  
  #this function generates samples of the metropolis algorithm
  dados <- theta
  matriz <- matrix(nrow = nsteps, ncol = 4)#initilize the samples matrix
  for (i in seq_len(nsteps)){
    for(j in 1:burnin)
      dados <- step(dados[1:3], s, xzes, p, sigma)#iterate to fill the matrix
    matriz[i,] <- dados
  }
  
  return(matriz)#return
}

e_value <- function(s, #the potential for stationary distribution
                    xzes, #the fixed parameters for the stationary distribution 
                    p,  #the proposal distribution
                    sigma, #the sigma for the proposal distribution
                    limit, #the result of the optimization step
                    nsteps = 1000 #the number of samples
) {
  
  #this function calculates the integral for a given interval
  
  #the vector of samples
  res <- run(c(0,0,0), s, xzes, p, sigma, nsteps)
  #the proportion of samples inside our interval minus 
  results <- res[,4]
  evalue <- 1 - length(results[results > limit])/nsteps
  #return the e-value
  return(evalue)
  
}


e_value_estimate <- function(s, #the potential for stationary distribution
                             xzes, #the fixed parameters for the stationary distribution 
                             p,  #the proposal distribution
                             sigma, #the sigma for the proposal distribution
                             limit, #the result of the optimization step
                             nruns = 8000 #the number of runs
){
    
  
  estimates <- foreach(i = 1:nruns,
                       .combine = c
  ) %dopar% {
    e_value(s, xzes, p, sigma, limit)
    
  }
  
  #return data
  return(c(I = mean(estimates), #my integral
           Isd = sd(estimates)) #variance of the estimate
  )
  
}


e_value_precision <- function(s, #the potential for stationary distribution
                              xzes, #the fixed parameters for the stationary distribution 
                              p,  #the proposal distribution
                              sigma, #the sigma for the proposal distribution
                              limit, #the result of the optimization step
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
    nth <- e_value_estimate(s, xzes, p, sigma, limit, n) 
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
           Ev = m, #the value of our integral
           error = errchance) #the estimated error
  )
  
}

xzestable <- rbind(c(1, 17, 2),
                   c(1, 16, 3),
                   c(1, 15, 4),
                   c(1, 14, 5),
                   c(1, 13, 6),
                   c(1, 12, 7),
                   c(1, 11, 8),
                   c(1, 10, 9),
                   c(1, 9, 10),
                   c(1, 8, 11),
                   c(1, 7, 12),
                   c(1, 6, 13),
                   c(1, 5, 14),
                   c(1, 4, 15),
                   c(1, 3, 16),
                   c(1, 2, 17),
                   c(1, 1, 18),
                   c(5, 15, 0),
                   c(5, 14, 1),
                   c(5, 13, 2),
                   c(5, 12, 3),
                   c(5, 11, 4))

evaluestable <- matrix(nrow = 0, ncol = 4)

for(row in 1:nrow(xzestable)){
    
    limite <- optimise(h, c(0, 1), maximum = TRUE, xzestable[row,])$objective
    e <- e_value_precision(s, xzestable[row,], p, sigma, limite)[3]
    evaluestable <- rbind(evaluestable, c(xzestable[row,], e))

}