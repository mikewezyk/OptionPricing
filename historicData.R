# 
# #sourceCpp("/Users/mikewezyk/Documents/QF465/OptionPricing/rtester.cpp")
# 
# 
# getYahooStockUrl <- function(symbol, start, end, type="d") {
#   # Creates a Yahoo URL for fetching historical stock data
#   #
#   # Args:
#   #   symbol - the stock symbol for which to fetch data
#   #   start - the date (CCYY-MM-DD) to start fetching data
#   #   end - the date (CCYY-MM-DD) to finish fetching data
#   #   type - daily/monthly data indicator ("d" or "m")
#   #
#   # Returns:
#   #   A Yahoo URL string for fetching historical stock data
#   
#   start <- as.Date(start)
#   end <- as.Date(end)
#   url <- "http://ichart.finance.yahoo.com/table.csv?s=%s&a=%d&b=%s&c=%s&d=%d&e=%s&f=%s&g=%s&ignore=.csv"
#   
#   sprintf(url,
#           toupper(symbol),
#           as.integer(format(start, "%m")) - 1,
#           format(start, "%d"),
#           format(start, "%Y"),
#           as.integer(format(end, "%m")) - 1,
#           format(end, "%d"),
#           format(end, "%Y"),
#           type)
# }
# 
# calcVolat <- function(symbol, start, end) {
#   data <- read.csv(getYahooStockUrl(symbol, start, end),stringsAsFactors=FALSE)
#   monthlyData <- data[order(data$Date), c('Date', 'Adj.Close')]
#   ret <- log(lag(ts(monthlyData$Adj.Close))) - log(ts(monthlyData$Adj.Close))
#   vol <- sd(ret) * sqrt(250) * 100
#   #return(vol);
#   write.csv(vol, "readIn.csv", row.names = FALSE)
# }
# 
# cInfo=read.csv("writeOut.csv",header=FALSE)
# ticker <- cInfo$V1[1]
# start <- cInfo$V1[2]
# end <- cInfo$V1[3]
# calcVolat(ticker, start, end)


getYahooStockUrl <- function(symbol, optionExp, type="d") {
  # Creates a Yahoo URL for fetching historical stock data
  #
  # Args:
  #   symbol - the stock symbol for which to fetch data
  #   start - the date (CCYY-MM-DD) to start fetching data
  #   end - the date (CCYY-MM-DD) to finish fetching data
  #   type - daily/monthly data indicator ("d" or "m")
  #
  # Returns:
  #   A Yahoo URL string for fetching historical stock data
  

  end <- Sys.Date()
  # dateDiff <- (as.Date(optionExp) - Sys.Date())
  start <- Sys.Date() - ((as.Date(optionExp) - Sys.Date()) * 4)
  url <- "http://ichart.finance.yahoo.com/table.csv?s=%s&a=%d&b=%s&c=%s&d=%d&e=%s&f=%s&g=%s&ignore=.csv"
  
  sprintf(url,
          toupper(symbol),
          as.integer(format(start, "%m")) - 1,
          format(start, "%d"),
          format(start, "%Y"),
          as.integer(format(end, "%m")) - 1,
          format(end, "%d"),
          format(end, "%Y"),
          type)
}

calcVolat <- function(symbol, optionExp) {
  data <- read.csv(getYahooStockUrl(symbol, optionExp),stringsAsFactors=FALSE)
  monthlyData <- data[order(data$Date), c('Date', 'Adj.Close')]
  ret <- log(lag(ts(monthlyData$Adj.Close))) - log(ts(monthlyData$Adj.Close))
  vol <- sd(ret) * sqrt(250)
  end <- Sys.Date()
  start <- Sys.Date() - ((as.Date(optionExp) - Sys.Date()) * 4)
  diffDates <- as.numeric(as.Date(end), units = "days") - as.numeric(as.Date(start), units = "days")
  Ufact <- exp(vol * sqrt(diffDates/365))
  Dfact <- exp(vol* -1 * sqrt(diffDates/365))
  myVector <- c(vol, Ufact, Dfact)
  write.csv(myVector, "readIn.csv", row.names = FALSE)
  return(myVector)
}


cInfo=read.csv("writeOut.csv",header=FALSE)
ticker <- cInfo$V1[1]
optionExp <- cInfo$V1[2]
#end <- cInfo$V1[3]
calcVolat(ticker, optionExp)
