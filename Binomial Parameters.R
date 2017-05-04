#Format exp as: "YYYY-MM-DD"
#Returns vector in form: S0, Vol, r


calcParam = function(symbol,exp){
  #Queries data from Quantmod
  start = Sys.Date() - 365 
  start = start - 1
  data = getSymbols(symbol,src = "yahoo", from = start, to = Sys.Date(), auto.assign = FALSE)
  returns = diff(log(data[,6]))[-1]
  vol = sd(returns) * sqrt(252)
  getSymbols("DGS3MO", src = "FRED")
  rf = tail(DGS3MO,n=1)/100
  price = tail(data[,6],n=1)
  price = as.double(price[1,1])
  results = c(price,vol,rf)
  write.csv(results, "readIn.csv", row.names = FALSE)
  #return(results)
}

setwd("/Users/mikewezyk/Documents/QF465/OptionPricing/OptionPricing")
require(quantmod)
cInfo = read.csv("writeOut.csv",header=FALSE)
ticker = toString(cInfo$V1[1])
optionExp = toString(cInfo$V1[2])
calcParam(toString(ticker), optionExp)