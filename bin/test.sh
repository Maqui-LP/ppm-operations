#!/bin/bash

# Change to repo's top level directory
cd $(dirname "$0")/..

assert() {
    echo "Running ./bin/ppm -i ./samples/model.ppm -o ./hidden/$2.ppm $3"
    ./bin/ppm -i ./samples/model.ppm -o ./hidden/$2.ppm $3
    diff ./samples/$1.ppm ./hidden/$2.ppm >/dev/null
    if [[ $? -ne 0 ]]; then 
        echo "Test failed for flag $3"
        exit 1
    fi
    echo "Succeded!"
    echo
}

assert "modelCopy" "modelCopy2"
assert "modelNegative" "modelNegative2" "-n"
assert "modelRotated" "modelRotated2" "-r"
assert "modelHorizontalMirror" "modelHorizontalMirror2" "-h"
assert "modelVerticalMirror" "modelVerticalMirror2" "-v"
assert "modelBlur7" "modelBlur72" "-b 7"
assert "modelBlackNWhite" "modelBlackNWhite2" "-w"
assert "modelGrayscale" "modelGrayscale2" "-g"
assert "modelSepia" "modelSepia2" "-s"