pacman::p_load(
  tidyverse,
  ggplot2,
  rstudioapi,
  devtools
)

# source lickometer library
devtools::source_url("https://github.com/lab-cpl/lickometer-library/blob/main/src/lickometer_functions_compilate.R?raw=TRUE")

# set working directory where this file is located
setwd("~/nbolab_FED/R_scripts")

# lickometer data for both pool with low and high uncertainty
lickometer_uncertainty <- readRDS("../raw_data/lickometer_data.rds")

# fed data for both pool with low and high uncertainty
fed_high_uncertainty <- readRDS("../raw_data/high_uncertainty.rds")
fed_low_uncertainty <- readRDS("../raw_data/low_uncertainty.rds")

# merge both fed data sets
fed_uncertainty <- bind_rows(
  fed_high_uncertainty,
  fed_low_uncertainty
)

# weight data
weight_uncertainty <- readRDS("../raw_data/weights/weights.rds")

weight_uncertainty <- readRDS("../raw_data/weights/weights.rds")
# create control and experimental groups
weight_uncertainty <- weight_uncertainty %>% 
  mutate(
    group = case_when(
      animal %in% c(320, 323, 325, 326) ~ "experimental_high_unc",
      animal %in% c(234, 235, 236, 245, 265) ~ "experimental_low_unc",
      TRUE ~ "control"
    )
  )

# add groups
# first we get them from fed_uncerainty data
groups <- fed_uncertainty %>% 
  select(
    animal,
    protocol,
    ymd
  ) %>% 
  distinct(., ymd, .keep_all = TRUE)
# add the group into weight data
weight_uncertainty <- weight_uncertainty %>% 
  left_join(groups, by = c("animal", "date" = "ymd")) %>% 
  filter(protocol %in% c("experimental", "control"))

# calculate percent difference between days
weight_uncertainty <- weight_uncertainty %>% 
  group_by(
    animal
  ) %>% 
  mutate(
    init_weight = weight[1],
    delta_bw = ((weight - init_weight) / ((weight + init_weight) / 2)) * 100,
    cumm_delta_bw = cumsum(delta_bw),
    session = as.numeric(as.factor(date))
  ) %>% 
  # right number of weight sessions
  filter(session <= 16)

# add relevant labels: experimental group and protocol
labels <- weight_uncertainty %>% 
  select(animal, group, protocol, experiment_id) %>% 
  distinct(., animal, .keep_all = TRUE) %>% 
  rename(ID = animal)


lickometer_data <- lickometer_uncertainty %>% 
  left_join(
    labels,
    by = c("ID")
  ) %>% 
  # add session instead of dates
  group_by(
    group,
    task_type
  ) %>% 
  mutate(
    session = as.numeric(as.factor(fecha))
  ) %>% 
  ungroup()

# preference for sucrose
spout_pref <- lickometer_data %>% 
  group_by(
    ID,
    group,
    protocol,
    tipo_recompensa,
    session,
    task_type,
    fecha,
    experiment_id
  ) %>% 
  summarise(
    n_licks = n(),
    n_events = max(evento)
  )

pr_sessions <- spout_pref %>% 
  filter(task_type == "pr") %>% 
  group_by(
    group,
    protocol,
    experiment_id
  ) %>% 
  mutate(
    session = as.numeric(as.factor(fecha)),
    valid_session = if_else(protocol == "control" & session > 5, 0, 1)
  ) %>% 
  # consider only sucrose licks and events
  filter(valid_session == 1, tipo_recompensa == "sacarosa") %>% 
  select(-valid_session) %>% 
  # re compute standarized mean after merging both controls group together
  mutate(
    experiment_id = if_else(protocol == "control", "control", experiment_id)
  ) %>% 
  # z-score licks and events
  group_by(
    ID
  ) %>% 
  mutate(
    n_licks_z = scale(n_licks),
    n_events_z = scale(n_events)
  ) %>% 
  ungroup() %>% 
  # obtain group estimates
  group_by(
    protocol,
    group,
    experiment_id,
    session
  ) %>% 
  summarise(
    mean_licks = mean(n_licks_z),
    mean_events = mean(n_events_z),
    err_licks = sd(n_licks_z) / sqrt(n()),
    err_events = sd(n_events_z) / sqrt(n())
  )

# obtain timeout measure via peri-event interval
peri_event_data <- lickometer_data %>% 
  select(
    ID,
    pool,
    task_type,
    group,
    timestamp,
    experiment_id,
    protocol,
    tipo_recompensa,
    n_sesion,
    sensor,
    evento,
    actividad,
    fecha
  ) %>% 
  uncumulate()

saveRDS(peri_event_data %>%  synch_lick_event(., TRUE), "peri_event.rds")
