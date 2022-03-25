# Script
pacman::p_load(tidyverse, cowplot, lme4, lmerTest)

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

# count pellets per day
df %>%
	group_by(animal, date) %>%
	summarise(pellets_consumed = max(pellets)) %>%
	ungroup() -> pellets_consumed
# plot pellets per day
pellets_consumed %>%
	ggplot(aes(date, pellets_consumed, group = animal, color = animal)) +
	geom_point() +
	geom_line() +
	geom_label(aes(label = animal), data = pellets_consumed %>% group_by(animal) %>% slice(which.max(date))) +
	theme_minimal(base_size = 14) +
	xlab("Date") +
	ylab("Pellet Intake") +
	theme(legend.position = "none")

# plot pellets per hour
rect <- data.frame(xmin=hms::as_hms("12:00:00"), xmax=hms::as_hms("23:59:99"), ymin=-Inf, ymax=Inf)
df %>%
	group_by(animal) %>%
	mutate(pellet_ticks = " ") %>%
	ggplot(aes(hour, pellet_ticks, group = animal)) +
	geom_point(shape = "|", size = 4) +
	geom_rect(data=rect, aes(xmin=xmin, xmax=xmax, ymin=ymin, ymax=ymax),
              color=NA,
	      fill = "grey20",
              alpha=0.5,
              inherit.aes = FALSE) +
	facet_grid(vars(animal),
		   space = "free",
		   scale = "free_y") +
	theme_minimal(base_size = 14) +
	theme(axis.ticks = element_blank()) +
	ylab("") -> p1
df %>%
	group_by(animal, isolated_hour) %>%
	summarise(
		  pellets_consumed_hour = n()
	) %>%
	ungroup() %>%
	group_by(animal) %>%
	mutate(
	       pellets_consumed_hour_scaled = scale(pellets_consumed_hour)
	       ) %>%
	ungroup() %>%
	group_by(isolated_hour) %>%
	summarise(
		  mean_pellets = mean(pellets_consumed_hour_scaled),
		  err_pellets = sd(pellets_consumed_hour_scaled) / sqrt(n())
		  ) %>%
	ggplot(aes(isolated_hour, mean_pellets,
		   ymax = mean_pellets + err_pellets,
		   ymin = mean_pellets - err_pellets
		   )) +
	geom_errorbar() +
	geom_line() +
	theme_minimal(base_size = 14) +
	xlab("") +
	ylab("") +
	scale_y_continuous(position = "right") +
	labs(title = "Pellet intake by hour") +
	theme(
	      legend.position = "none",
	      plot.margin = unit(c(0, 0, 0, 22), "pt")
	      ) -> p2
plot_grid(
  p2,
  p1,
  labels = "auto",
  ncol = 1,
  align = "v",
  axis = "b"
) -> raster_plot
raster_plot

# pellets day/night
df %>%
	mutate(
	       day_night = as.factor(if_else(isolated_hour >= 12 & isolated_hour <= 23,
				   "Dark", "Light"))
	) %>%
	group_by(animal, date, day_night) %>%
	summarise(pellets_consumed = n()) %>%
	ungroup() %>%
	group_by(animal) %>%
	mutate(pellets_consumed_scaled = scale(pellets_consumed)) %>%
	ungroup() %>%
	group_by(day_night) %>%
	summarise(
		  mean_pellet_intake = mean(pellets_consumed_scaled),
		  err_pellet_intake = sd(pellets_consumed_scaled) / sqrt(n())
		  ) -> pellets_consumed_circadian
pellets_consumed_circadian %>%
	ggplot(aes(
		   day_night, mean_pellet_intake,
		   ymin = mean_pellet_intake - err_pellet_intake,
		   ymax = mean_pellet_intake + err_pellet_intake,
		   fill = day_night
		   )) +
	geom_col(width = 0.5) +
	geom_hline(yintercept = 0, color = "gray70") +
	geom_point(color = "gray70") +
	geom_errorbar(width=0.3, color = "gray20") +
	theme_minimal(base_size = 14) +
	ylab("Mean pellet intake z-score") +
	xlab("") +
	scale_fill_manual(values=c("#000000", "#004010")) +
	theme(
	      legend.position = "none"
	      )

# statistics
df %>%
	mutate(
	       day_night = as.factor(if_else(isolated_hour >= 11 & isolated_hour <= 23,
				   "Dark", "Light"))
	) %>%
	group_by(animal, day_night) %>%
	summarise(pellets_consumed = n()) %>%
	ungroup() %>%
	group_by(animal) %>%
	mutate(pellets_consumed_scaled = scale(pellets_consumed)) %>%
	ungroup() -> df_circadian_intake

lmer(pellets_consumed ~ day_night + (1 | animal), df_circadian_intake) %>%
	summary()
