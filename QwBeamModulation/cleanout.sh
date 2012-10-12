#!/bin/bash
#

if [ "$1" == "--logs" ];
    then
    echo "Cleaning up logs...."
    cp -v bmod*.out /volatile/hallc/qweak/jhoskins/run2/logs/
    rm -rf bmod*.out
elif [ "$1" == "--diagnostics" ];
    then
    echo "Cleaning up diagnostic files...."
    cp -vR bmod_tree_* slopes_*.dat diagnostic*dat regression_*dat /volatile/hallc/qweak/jhoskins/run2/bmod_regression/
    rm -rf bmod_tree_* slopes_* diagnostic_* regression_*
else
    echo "Cleaning up working directory...."
    cp -vR bmod_tree_* slopes_*.dat diagnostic*dat regression_*dat /volatile/hallc/qweak/jhoskins/run2/bmod_regression/
    cp -vR bmod*.out /volatile/hallc/qweak/jhoskins/run2/logs/
    rm -rf bmod_tree_* slopes_* diagnostic_* regression_* bmod*.out
fi