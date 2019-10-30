#!/usr/bin/env bash

cd /autograder/source

apt-get install -y python build-essential valgrind

mkdir -p /autograder/build

mkdir -p /root/.ssh
cp deploy_key /root/.ssh/deploy_key

# Hide output of these from students
eval `ssh-agent` > /dev/null
ssh-add deploy_key > /dev/null

# To prevent host key verification errors at runtime
ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts

# Clone autograder files
git clone --quiet git@github.com:stevenbell/classwork13_autograder /autograder/classwork13_autograder

# Close gradescope_util files
git clone --quiet git@github.com:stevenbell/gradescope-utils /autograder/gradescope_utils

