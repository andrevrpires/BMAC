# Análise de Dados e Simulação
# https://www.citibikenyc.com/system-data

# libraries used
library(dplyr)
library(tidyr)
library(lubridate)
library(ggplot2)
library(ggmap)

# downloading the data
# https://s3.amazonaws.com/tripdata/index.html
bikeurl <- "https://s3.amazonaws.com/tripdata/201902-citibike-tripdata.csv.zip"
# here I had first to install curl on Ubuntu
download.file(bikeurl, destfile = "bikesfev.csv.zip", method = "curl")
downloadtime <- date()
unzip("bikesfev.csv.zip")
dadosbike <- read.csv("JC-201902-citibike-tripdata.csv")

# looking at the data
head(dadosbike)
str(dadosbike)
summary(dadosbike)

# then I started to tidy the data
# Tidy 1: numeric to factor
dadosbike$start.station.id <- as.factor(dadosbike$start.station.id)
dadosbike$stop.station.id <- as.factor(dadosbike$stop.station.id)
dadosbike$bikeid <- as.factor(dadosbike$bikeid)
dadosbike$gender <- as.factor(dadosbike$gender)

# there is no need to do the following steps, but I'll keep them
# as.factor(dadosbike$birth.year)
# Tidy 2: 
# dadosbike <- separate(dadosbike, starttime, c("startdate", "starttime"), " ")
# dadosbike <- separate(dadosbike, stoptime, c("stopdate", "stoptime"), " ")
# Tidy 3: string to date
# dadosbike$startdate <- as.Date(dadosbike$startdate)
# dadosbike$stopdate <- as.Date(dadosbike$stopdate)
# Tidy 4: string to hrmour(lubridate)
# dadosbike$starthour <- hms(dadosbike$starthour)
# dadosbike$stophour <- hms(dadosbike$stophour)

#cleaning the data (machado's 99.5 percentile)
plot(sort(dadosbike$tripduration), log = "y")
plot(quantile(dadosbike$tripduration, probs = c(0:100)/100))
quantile(dadosbike$tripduration, probs = c(0, 0.005, 0.25, 0.5, 0.75, 0.995, 1))

# exploring the data

# tripduration by - station, time, day, usertype
# start/stop time - create faixas
# weekday, monthday, month, season
# station by - tripduration(descriptive), birthyear(histogram), usertype, count
# bikeid?
# usertype by - station, birthyear, time, day(weekday, monthday, etc), tripduration
# birthyear by - station, time, day, usertype, tripduration
# create distance variable?

# histograms
# wday by subscriber
# wday by consumer
# hour by subscriber
# hour by consumer
# day/hour peaks
# all these by station

#boxplots
# tripduration by subscriber
# tripduration by consumer
# birthyear


# plots
# over the map (ggmap library)
# read ?register_google
# https://www.r-bloggers.com/how-to-plot-basic-maps-with-ggmap/
x <- dadosbike$start.station.longitude
y <- dadosbike$start.station.latitude
mapinfo <- data.frame(x, y)
mapinfo <- unique(mapinfo)
# https://rdrr.io/cran/ggmap/man/make_bbox.html
bbox <- make_bbox(mapinfo$x, mapinfo$y)

start.station.count <- dadosbike %>%
  select(start.station.longitude, start.station.latitude) %>%
  count(start.station.longitude, start.station.latitude)

stop.station.count <- dadosbike %>%
  select(stop.station.longitude, stop.station.latitude) %>%
  count(stop.station.longitude, stop.station.latitude)

# https://www.littlemissdata.com/blog/maps
get_map(bbox) %>%
  ggmap() +
  geom_point(data = start.station.count,
             aes(x = start.station.longitude,
                 y = start.station.latitude),
             size = (start.station.count$n/200))

get_map(bbox) %>%
  ggmap() +
  geom_point(data = stop.station.count,
             aes(x = stop.station.longitude,
                 y = stop.station.latitude),
             size = (stop.station.count$n/200))

### !!! ?geom_path, ?geom_step, ?geom_line

dir(dirsummary(dadosbike)
head(dadosbike$starttime)
strsplit(head(dadosbike$starttime), " ")
dadosbike$starttime <- hms(dadosbike$starttime)
dadosbike$stoptime <- hms(dadosbike$stoptime)
head(dadosbike)
summary(dadosbike)
tail(arrange(dadosbike$bikeid))
tail(arrange(dadosbike$bikeid))
dadosbike %>% select(bikeid) %>% count(bikeid) %>% arrange(desc(n))
dadosbike %>% select(bikeid) %>% count(bikeid) %>% arrange(n)
dadosbike %>% select(bikeid) %>% count(bikeid) %>% summarise(mean(n))
dadosbike %>% select(bikeid) %>% count(bikeid) %>% summarise(median(n))
dadosbike %>% select(bikeid) %>% count(bikeid) %>% summarise(boxplot(n))
boxplot(dadosbike %>% select(bikeid) %>% count(bikeid) %>% select(n))
boxplot(hour(dadosbike$starttime))
boxplot(hour(dadosbike$starttime)) ~ dadosbike$start.station.id
boxplot(hour(dadosbike$starttime)) ~ dadosbike$start.station.id
boxplot(hour(dadosbike$starttime)) ~ dadosbike$start.station.id
boxplot(hour(dadosbike$starttime)) ~ dadosbike$start.station.id
hist(hour(dadosbike$starttime))
hist(wday(dadosbike$startday))
dadosbike %>% filter(usertype == "Customer") %>% select(startday)
hist(wday(dadosbike$startday))
hist(wday(dadosbike$startday[dadosbike$usertype == "Customer"]))
hist(wday(dadosbike$startday[dadosbike$usertype == "Subscriber"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"]))
unique(dadosbike$start.station.name)
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Grove St PATH"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Grove St PATH"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Morris Canal"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Morris Canal"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Sip Ave"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Sip Ave"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Hamilton Park"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Hamilton Park"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Journal Square"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Journal Square"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "JC Medical Centel"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "JC Medical Center"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Customer"
                              & dadosbike$start.station.name == "Lincoln Park"]))
hist(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"
                              & dadosbike$start.station.name == "Lincoln Park"]))
hist(as.numeric(dadosbike$birth.year))
hist(as.numeric(dadosbike$birth.year[dadosbike$usertype == "Subscriber"]))
hist(as.numeric(dadosbike$birth.year[dadosbike$usertype == "Customer"]))
boxplot(hour(dadosbike$starttime))
boxplot(as.numeric(dadosbike$birth.year[dadosbike$usertype == "Subscriber"]))
boxplot(as.numeric(dadosbike$birth.year[dadosbike$usertype == "Customer"]))
boxplot(hour(dadosbike$starttime)~dadosbike$birth.year)
boxplot(hour(dadosbike$starttime)~dadosbike$usertype)
boxplot(hour(dadosbike$starttime[dadosbike$usertype == "Subscriber"]~
               dadosbike$start.station.name))


# compare histogram vs. boxplot!!!
