#!/usr/bin/env bash

set -xe

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

brew install opencv
brew install dlib
brew install pkg-config
