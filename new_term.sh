#!/bin/bash

# Command or script to run in the new terminal
command1="python3  ~/CPractise/term1.py "
commandfin="python3  ~/caesar2020/auto/zed_became_imu.py"


# Open a new terminal and run the command
gnome-terminal -- bash -c "$command1; exec bash"
gnome-terminal -- bash -c "$command2; exec bash"

