#!/bin/bash
rm -f README.md
touch README.md

echo "UVa Problems" >> README.md
echo "============" >> README.md
echo " " >> README.md
find ./ -name STATUS | while read FILENAME
do
  cat "$FILENAME" >> README.md
  echo " " >> README.md
  echo " " >> README.md
done
chmod -w README.md
