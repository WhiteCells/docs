#!/bin/bash

set -e

project_source_dir="$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)"

cd $project_source_dir

git add .
git commit -m "update"
git push -u origin main

read
