# Script
pacman::p_load(tidyverse, cowplot, lme4, lmerTest, ggrepel)

df <- readRDS("df.rds")

# put labels
df %>%
	mutate(
	       protocol = if_else(date <= "2022-03-28", "baseline",
	       if_else(animal %in% c(323, 322, 326, 324), "control", "experimental"))
	       ) -> df

# count pellets per day
df %>%
	group_by(animal, date, protocol) %>%
	summarise(pellets_consumed = n()) %>%
	ungroup() -> pellets_consumed

# get baseline mean intake
pellets_consumed %>%
	filter(protocol == "baseline",
	       date <= "2022-03-28",
	       date >= "2022-03-26",
	       ) %>%
	group_by(animal) %>%
	summarise(
		  baseline_intake = mean(pellets_consumed),
		  baseline_err = sd(pellets_consumed) / sqrt(n())
	) -> baseline


# get experimental phase intake
pellets_consumed %>%
	filter(protocol == "experimental" | protocol == "control",
	       pellets_consumed > 10,
	       date > "2022-03-28",
	       date < "2022-04-06") -> experimental

baseline %>%
	left_join(experimental) -> merged_data

merged_data %>%
	ggplot(aes(date, pellets_consumed, color = protocol)) +
	geom_line() +
	geom_point() +
	geom_line(inherit.aes = FALSE, aes(date, baseline_intake)) +
	geom_line(inherit.aes = FALSE, aes(date, baseline_intake)) +
	facet_wrap(~animal) +
	xlab("Date") +
	ylab("Pellets consumed per day") +
	theme(text = element_text(size = 20)) +
	theme_bw()
ggsave("vsbaseline.png")

#pellets_consumed %>%
#	filter(date > "2022-03-23", date < "2022-03-28") %>%
#	group_by(animal) %>%
#	summarise(mean_p = mean(pellets_consumed)) %>% arrange(desc(mean_p)) %>%
#	mutate(group = as.factor(c(1, 2, 1, 2, 1, 2, 1, 2))) -> group_ll
#a <- group_ll %>% filter(group == 1) %>% select(mean_p)
#b <- group_ll %>% filter(group == 2) %>% select(mean_p)
#t.test(a,b)

# simple plot
pellets_consumed %>%
	filter(pellets_consumed > 10) %>%
	ggplot(aes(date, pellets_consumed, group = animal, color = animal, fill = protocol)) +
	geom_point() +
	geom_line() +
	geom_label_repel(aes(label = animal), data = pellets_consumed %>% group_by(animal) %>% slice(which.max(date))) +
	geom_vline(xintercept = lubridate::ymd("2022-03-29")) +
	theme_minimal(base_size = 14) +
	xlab("Date") +
	ylab("Pellet Intake")

ggsave("licks_per_mice.png")


# grand mean
pellets_consumed %>%
	group_by(date) %>%
	summarise(
		  m_pellets = mean(pellets_consumed),
		  err_pellets = sd(pellets_consumed) / sqrt(n())
		  ) %>%
	ungroup() -> pellets_grand_mean
# plot pellets per day
pellets_consumed %>%
	ggplot(aes(date, pellets_consumed, group = animal, color = animal, alpha = 0.5)) +
	geom_point() +
	geom_line() +
	geom_label_repel(aes(label = animal), data = pellets_consumed %>% group_by(animal) %>% slice(which.max(date))) +
	geom_point(
		   data = pellets_grand_mean,
		   aes(
		       date, m_pellets
		       ),
		   inherit.aes = FALSE
		   ) +
	geom_line(
		   data = pellets_grand_mean,
		   aes(
		       date, m_pellets
		       ),
		   inherit.aes = FALSE
		   ) +
	geom_errorbar(
		   data = pellets_grand_mean,
		   aes(
		       date, m_pellets,
		       ymin = m_pellets - err_pellets,
		       ymax = m_pellets + err_pellets,
		       ),
		   width = 0.3,
		   inherit.aes = FALSE
		   ) +
	theme_minimal(base_size = 14) +
	xlab("Date") +
	ylab("Pellet Intake") +
	theme(legend.position = "none")
ggsave("licks_per_mice.png")

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
	group_by(animal, isolated_hour, date) %>%
	summarise(
		  pellets_consumed_hour = n()
	) %>%
	summarise(
		  mean_pellets = mean(pellets_consumed_hour)
		  ) %>%
	ungroup() %>%
	group_by(animal) %>%
	mutate(
	       mean_pellets_scaled = scale(mean_pellets)
	       ) %>%
	ungroup() %>%
	group_by(isolated_hour) %>%
	summarise(
		  mean_pellets_summ = mean(mean_pellets_scaled),
		  err_pellets_summ = sd(mean_pellets_scaled) / sqrt(n())
		  ) %>%
	ggplot(aes(isolated_hour, mean_pellets_summ,
		   ymax = mean_pellets_summ + err_pellets_summ,
		   ymin = mean_pellets_summ - err_pellets_summ
		   )) +
	geom_errorbar() +
	geom_line() +
	scale_x_continuous(breaks = scales::pretty_breaks(n = 10)) +
	theme_minimal(base_size = 14) +
	xlab("") +
	ylab("") +
	scale_y_continuous(position = "right") +
	labs(title = "Pellet intake by hour") +
	theme(
	      legend.position = "none",
	      plot.margin = unit(c(0, 0, 0, 16), "pt")
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
ggsave("raster_plot.png")

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
		   yax = mean_pellet_intake + err_pellet_intake,
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
	       day_night = as.factor(if_else(isolated_hour >= 12 & isolated_hour <= 23,
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
