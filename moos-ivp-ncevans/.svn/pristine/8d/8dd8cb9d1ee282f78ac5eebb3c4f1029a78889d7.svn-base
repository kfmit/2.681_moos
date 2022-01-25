#!/bin/bash
#----------------------------------------------------------
#----------------------------------------------------------
#  Script: launch.sh
#  Author: Craig Evans
#  LastEd: March 30th 2021
#  Modified From: Launch.sh from M. Benjamin
#----------------------------------------------------------
#----------------------------------------------------------
trap "kill -- -$$" EXIT SIGTERM SIGHUP SIGINT SIGKILL
TIME_WARP=1
COMMUNITY1="shore_alpha"
COMMUNITY2="vehicle_alpha"
GUI="yes"

#handle command line
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	echo "launch.sh [SWITCHES] [time_warp]   "
	echo "  --help, -h           Show this help message            " 
	exit 0;
    elif [ "${ARGI}" = "--nogui" ] ; then
	GUI="no"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    else 
        echo "launch.sh Bad arg:" $ARGI " Exiting with code: 1"
        exit 1
    fi
done

#launch the processes
echo "Launching All MOOS Communities with WARP:"

pAntler $COMMUNITY1.moos --MOOSTimeWarp=$TIME_WARP >& /dev/null & 

pAntler $COMMUNITY2.moos --MOOSTimeWarp=$TIME_WARP >& /dev/null &

uMAC -t $COMMUNITY1.moos
