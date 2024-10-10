#!/bin/bash
BUILD_FOLDER=/home/$USER/qmk_firmware/.build/
UPLOAD_FOLDER=/media/$USER/RPI-RP2
rm $BUILD_FOLDER/*.uf2

set -e
set -x

. ./venv/bin/activate
qmk compile -e CONVERT_TO=liatris


while ! [ -d $UPLOAD_FOLDER ]
do
    echo "Waiting for the keyboard to show up at $UPLOAD_FOLDER"
    sleep 1
done

cp $BUILD_FOLDER/*.uf2 $UPLOAD_FOLDER

echo Done