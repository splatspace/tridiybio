#!/bin/bash
# sync.sh written by Claude Pageau for pi-timolo, his excellent video processing application.
# re-purposed and mangled by Malcolm Taylor for use with MotionPie
# edited by Emil Janesten to stop duplicate running instances and duplicate files and folders in Google Drive.

# folder where motion files are located
SYNC_DIR=output

# Get current folder where this script is located
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Lockfile
LOCK=/var/tmp/gdrive_sync

# check if script is already running to avoid multiple instances
if [ -f $LOCK ]; then
  echo "--   Job is already running\! --"
  exit 6
fi
touch $LOCK

# Run gdrive for files in folder specified by variable $SYNC_DIR
echo "$(date)"
echo "---------------------- PROCESSING ---------------------------------"
echo "Starting gdrive Push From $DIR/$SYNC_DIR"
echo "                      To  google drive subfolder $SYNC_DIR"
echo "-------------------------------------------------------------------"     
cd $DIR
echo "Start synchronization ....."
echo "gdrive push -r -no-prompt -ignore-conflict -ignore-name-clashes $SYNC_DIR/*"
echo "Starting gdrive sync at $(date)" >> sync.log

gdrive push -r -no-prompt -ignore-conflict -ignore-name-clashes $SYNC_DIR/*

# Check if gdrive exited successfully
if [ $? -ne 0 ]
then
  echo "ERROR - gdrive Processing failed."
  echo "Possible Cause - No internet connection or some other reason."
fi
cd $DIR

echo "Done at $(date)."
rm $LOCK
exit