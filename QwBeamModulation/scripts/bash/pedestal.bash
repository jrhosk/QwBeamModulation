#!/bin/bash
#
# User should set final copy directory to personal directory
#

umask 002

scriptPath=`dirname $0`
cd $scriptPath
scriptPath=`pwd`

export QWSCRATCH=/volatile/hallc/qweak/jhoskins/scratch
export QWANALYSIS=/home/jhoskins/QwAnalysis
. $QWANALYSIS/SetupFiles/SET_ME_UP.bash # >& /dev/null

#export QW_ROOTFILES=/volatile/hallc/qweak/QwAnalysis/run1/rootfiles
export QW_ROOTFILES=/cache/mss/hallc/qweak/rootfiles/pass4b

FINAL_PATH=/volatile/hallc/qweak/jhoskins/
BMOD_FILE_STEM="bmod_tree_"
HOST=`hostname`

# ------------------------------------------------------------------- #
#                                                                     #
# ------------------------------------------------------------------- #


echo "hostname is set to $HOST"

if [ -n "$1" ]
    then
    RUN_NUMBER=${1}
else
    echo "Error::Run number not specified."
    exit
fi

$scriptPath/ramp_pedestal ${RUN_NUMBER}

if [ $? -ne 0 ]
then
    echo "There was and error in the completion of pedestal analysis"
    exit
fi
