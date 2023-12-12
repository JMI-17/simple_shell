#!/bin/bash

# Read the maximum process ID from /proc/sys/kernel/pid_max
jb_max_pid=$(cat /proc/sys/kernel/pid_max)

# Print the maximum process ID
echo "Maximum Process ID: $jb_max_pid"
