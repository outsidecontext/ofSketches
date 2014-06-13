#!/bin/bash

# Clones dependencies for Mumm
# !Run this script from the Mumm project root!

# cd ../../addons/

# create new addons dir
# mkdir addons
cd ../../addons

# passing no arguments means read only
if [ -z $1 ]; then
    CLONE="git clone https://github.com/"
    echo "Cloning read-only"
else
    CLONE="git clone git@github.com:"
    echo "Cloning writable"
fi

# git clone specific revision of the addons
${CLONE}rezaali/ofxUI
cd ofxUI
git checkout 1f524f2c41c73113c7529703e6f3274fdcc19956
cd ..

${CLONE}armadillu/ofxRemoteUI
cd ofxRemoteUI
git checkout 6ed3a5b15bb75355a472934b77853588ce646895
cd ..

${CLONE}timscaffidi/ofxOpticalFlowFarneback
cd ofxOpticalFlowFarneback
git checkout 86e7154a76cb8b52c84a8c672e56119f0e5bebaf
cd ..


# final step is to cd back to the start dir
cd ..