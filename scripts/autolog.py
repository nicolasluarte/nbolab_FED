import re
import json
import os


# mount micro sd card

# show currect connected devices
showDevices = 'lsblk'
os.system(showDevices)

# auto choose sdb1 for now
# later on implement a selection prompt
mountDevices = 'sudo mount /dev/sdb1 ~/usb-drive'
lsMountDevices = 'ls ~/usb-drive'
lsExperimental = 'cat ~/usb-drive/config.txt'
mountPrompt = input("Code to run  " + mountDevices + "(y/n) : ")

if mountPrompt == 'y':
    os.system(mountDevices)
    print("### LISTING FILES BELOW ###")
    os.system(lsMountDevices)
    print("### EXPERIMENTAL PARAMETERS ###")
    os.system(lsExperimental)
    # load json file
    f = open('/home/nicoluarte/usb-drive/config.txt').read()
    pattern = re.compile("[0-9]{3}")
    animalNumber = pattern.search(f)[0]
    # animal number
    print(animalNumber)
    # create folder based on animal name if it does not exists
    createDirectory = 'mkdir -p ../raw_data/' + animalNumber
    os.system(createDirectory)
    # copy animal data .CSV into the folder
    copyCSV = 'sudo cp ~/usb-drive/' + animalNumber + '.CSV' + ' ../raw_data/' + animalNumber + '/'
    os.system(copyCSV)
    # unmount micro sd
    unmountSd = 'sudo umount /dev/sdb1'
else:
    print(":c")
    exit(0)


