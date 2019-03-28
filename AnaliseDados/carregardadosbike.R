bikeurl <- "https://s3.amazonaws.com/tripdata/201902-citibike-tripdata.csv.zip"
unzippedfile <- "201902-citibike-tripdata.csv"
if (!file.exists(unzippedfile))
{
  destfile <- "bikesfev.csv.zip"
  if (!file.exists(destfile))
  {
    # here I had first to install curl on Ubuntu
    download.file(bikeurl, destfile = destfile, method = "curl")
    downloadtime <- date()
  }
  unzip(destfile)
}
dadosbike <- read.csv(unzippedfile)
