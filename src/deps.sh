#!/bin/sh

awkOutput=$(./makedepf08.awk mainp/*.f* */*.f*)

echo $awkOutput > tmpDeps
# Reemplazar espacios por new lines
sed -i 's/ /\n/g' tmpDeps
# Borrar nombres de archivos
sed -i 's/\/.*:/:/g' tmpDeps
sed -i 's/\/.*$//g' tmpDeps
# Borrar lineas con .mod y lineas en blanco
sed -i '/.*\.mod/d' tmpDeps
# Ordenar y borrar repetidos
echo "$(sort --unique tmpDeps)" > tmpDeps
# Borrar autoreferencias
echo "$(awk -F ":" '{if ($1 != $2) print $1 ":" $2}' tmpDeps)" > tmpDeps

cat tmpDeps
rm tmpDeps
