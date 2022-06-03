# Script
pacman::p_load(
  tidyverse,
  ggplot2
  )

# high uncertainty fed data ----

# load files
csv_list <- list.files(path = "../raw_data",
                            recursive = TRUE,
                            pattern = "\\.CSV$",
                            full.names = TRUE)
data_raw <- csv_list %>%
	set_names() %>%
	map_dfr(function(x) 
	  {
	  read_csv(x) %>% 
	    mutate_at(
	      c(
	        "time", "animal", "pellets", "motorTurns", "battery",
	        "delay"
	      ),
	      as.numeric
	    )
	},
	        .id = "file_name")

# create date
data_raw %>%
	mutate(
	       complete_date = as.POSIXct(time, origin="1970-01-01"),
	       date = as.Date(as.POSIXct(time, origin="1970-01-01")),
	       hour = hms::as_hms(lubridate::ymd_hms(complete_date)),
	       isolated_hour = lubridate::hour(complete_date),
	       animal = as.factor(animal),
	       pellets = as.numeric(pellets),
	       protocol = as.factor(protocol)
	       ) %>%
	filter(date >= "2022-01-01", date <= "2022-05-15", delay != 1) -> df

# set experimental condition
df %>%
	mutate(
		protocol = if_else(
				   date <= "2022-03-28",
				   "baseline",
				   if_else(
					   animal %in% c(321, 322, 324, 327),
					   "control",
					   "experimental"
					   )
				   )
		) -> df

# fix pellets count every day
df %>%
	group_by(animal, date) %>%
	mutate(pellets = seq(1, n(), 1)) %>% 
  select(-c(file_name, motorTurns)) %>% 
  rename(
    epoch = time,
    ymd_hms = complete_date,
    ymd = date,
    hms = hour,
    hour_of_day = isolated_hour
  ) %>% 
  mutate(experiment_id = "high_uncertainty_fed") -> df

saveRDS(df, "../raw_data/high_uncertainty.rds")



# low uncertainty fed data ----

csv_list_2 <- list.files(path = "../raw_data",
                       recursive = TRUE,
                       pattern = "[0-9]{3}.csv$",
                       full.names = TRUE)

data_raw_2 <- csv_list_2 %>%
  set_names() %>%
  map_dfr(read_csv, .id = "file_name") %>% 
  mutate(time = `MM:DD:YYYY hh:mm:ss`)

# get animal number

df_2 <- data_raw_2 %>% 
  mutate(
    animal = str_extract(file_name, "\\d+"),
    ymd_hms = lubridate::mdy_hms(time),
    ymd = lubridate::ymd(
      paste(
        lubridate::year(ymd_hms),
        lubridate::month(ymd_hms),
        lubridate::day(ymd_hms),
        sep = "-"
  )),
   hms = hms::as_hms(ymd_hms),
  hour_of_day = lubridate::hour(ymd_hms)
  ) %>% 
  group_by(
    animal,
    ymd
  ) %>% 
  mutate(
    pellets = seq(1, n(), 1)
    ) %>% 
  ungroup() %>% 
  mutate(
    protocol = case_when(
      ymd >= "2021-08-30" & ymd <= "2021-09-06" ~ "baseline",
      animal %in% c(234, 235, 236, 245, 265) ~ "experimental",
      TRUE ~ "control"),
      epoch = as.integer(as.POSIXct(ymd_hms))
  ) %>% 
  filter(ymd >= "2021-08-30") %>% 
  drop_na() %>% 
  rename(
    battery = BatteryVoltage,
    delay = Delay
  ) %>% 
  select(
    epoch,
    animal,
    pellets,
    battery,
    delay,
    protocol,
    ymd_hms,
    ymd,
    hms,
    hour_of_day
  ) %>% 
  mutate(
    experiment_id = "low_uncertainty_fed"
  )

saveRDS(df_2, "../raw_data/low_uncertainty.rds")

# weights low and high uncertainty fed data ----

h <- read_csv("~/repos/nbolab_FED/raw_data/weights/high_uncertainty_weights.csv")
l <- read_csv("~/repos/nbolab_FED/raw_data/weights/low_uncertainty_weights.csv")

h <- h %>% 
  pivot_longer(
    cols = !c("experiment_id", "date"),
    names_to = "animal",
    values_to = "weight"
  )
l <- l %>% 
  pivot_longer(
    cols = !c("experiment_id", "date"),
    names_to = "animal",
    values_to = "weight"
  )

weight_data <- bind_rows(h, l)
saveRDS(weight_data, "../raw_data/weights/weights.rds")


# lickometer data ----

unc_lick <- load_experiment(
  "/home/nicoluarte/repos/nbolab_FED/raw_data/metadata/metadata_lickometer_low_uncertainty.csv",
  "/home/nicoluarte/repos/FED_data/data/lickometer_data/"
) %>% 
  filter(ID != 246) %>% 
  mutate(task_type = str_extract(pool, ".{2}$"))

saveRDS(unc_lick, "/home/nicoluarte/repos/nbolab_FED/raw_data/lickometer_data.rds")
