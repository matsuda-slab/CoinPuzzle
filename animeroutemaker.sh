#/bin/bash

make play | make play | grep -E "[0-9]{2} :" | awk '{ print $3 }' >| route.txt
