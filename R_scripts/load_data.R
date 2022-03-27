# Script
pacman::p_load(tidyverse, cowplot, lme4, lmerTest, ggrepel)

# load files
csv_list <- list.files(path = "../raw_data",
                            recursive = TRUE,
                            pattern = "\\.CSV$",
                            full.names = TRUE)
data_raw <- csv_list %>%
	set_names() %>%
	map_dfr(read_csv, .id = "file_name") %>%
	filter(animal != 111)

# create date
data_raw %>%
	select(-numJamClears) %>%
	mutate(
	       complete_date = as.POSIXct(time, origin="1970-01-01"),
	       date = as.Date(as.POSIXct(time, origin="1970-01-01")),
	       hour = hms::as_hms(lubridate::ymd_hms(complete_date)),
	       isolated_hour = lubridate::hour(complete_date),
	       animal = as.factor(animal),
	       pellets = as.numeric(pellets),
	       ) %>%
	filter(date >= "2022-03-21") -> df

# fix pellets count every day
# remove test pellets
df %>%
	filter(isolated_hour < 8 | isolated_hour > 10) %>%
	group_by(animal, date) %>%
	mutate(pellets = seq(1, n(), 1)) -> df


saveRDS(data_raw, "df_raw.rds")
saveRDS(df, "df.rds")
