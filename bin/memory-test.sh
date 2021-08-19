#!/bin/bash

# Change to repo's top level directory
cd $(dirname "$0")/..

assert() {
    echo "Running valgrind check for ./bin/ppm -i ./samples/model.ppm $2"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --error-exitcode=1 \
    ./bin/ppm -i ./samples/model.ppm $2
    if [[ $? -ne 0 ]]; then 
        echo "Memory leak found"
        exit 1
    fi
    echo "No memory leaks found!"
    echo
}

assert "modelCopy" "-o ./hidden/modelCopy2.ppm"
assert "modelNegative" "-o ./hidden/modelNegative2.ppm -n"
assert "modelRotated" "-o ./hidden/modelRotated2.ppm -r"
assert "modelHorizontalMirror" "-o ./hidden/modelHorizontalMirror2.ppm -h"
assert "modelVerticalMirror" "-o ./hidden/modelVerticalMirror2.ppm -v"
assert "modelBlur7" "-o ./hidden/modelBlur72.ppm -b 7"
assert "modelBlackNWhite" "-o ./hidden/modelBlackNWhite2.ppm -w"
assert "modelBlackNWhite" "-o ./hidden/modelBlackNWhite3.ppm -wwwwww"
assert "modelGrayscale" "-o ./hidden/modelGrayscale2.ppm -g"
assert "modelSepia" "-o ./hidden/modelSepia2.ppm -s"
assert "modelSepiaGray" "-o ./hidden/modelSepiaGray2.ppm -s -g"