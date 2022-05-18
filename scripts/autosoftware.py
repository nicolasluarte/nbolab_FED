import os
import pyfiglet


print(pyfiglet.figlet_format("FED CLOCK SYNC"))
cmdClock = 'pio run -d ~/repos/nbolab_FED/fed_programs/FED_set_clock -t upload'
os.system(cmdClock)
print(pyfiglet.figlet_format("CLOCK SYNC DONE!"))

print(pyfiglet.figlet_format("FED DELAY CONTROL"))
cmdDelayControl = 'pio run -d ~/repos/nbolab_FED/fed_programs/FED_delay_control -t upload'
os.system(cmdDelayControl)
print(pyfiglet.figlet_format("DELAY CONTROL UPLOADED!"))

