#!/bin/sh

date
starttime="$(date +%s)"
echo "Current working directory:"
pwd

echo "Environment variables:"
env | sort

echo
echo "Compiler:     '$COMPILER'"
echo "Architecture: '$MSYS2_ARCH'"
echo "Platform:     '$PLATFORM'"
echo "MSYS2 dir:    '$MSYS2_DIR'"
echo "MSYS2 system: '$MSYSTEM'"
echo "Bits:         '$BIT'"
echo

[ "$COMPILER" = msys2 ] || exit 1

export PATH="/c/$MSYS2_DIR/$MSYSTEM/bin:/c/$MSYS2_DIR/usr/bin:$PATH"

echo "Ensure pacman mirrors and GIT are up to date:"
pacman -S --needed --noconfirm pacman-mirrors
pacman -S --needed --noconfirm git

echo "Updating packages first:"
pacman -Syu --noconfirm

echo "Installing required packages:"
pacman -S --noconfirm cmake make diffutils patch

elapsedSec="$(date +%s)"
elapsedSec=$((elapsed - starttime))
elapsedMin=$((elapsedSec/60))
elapsedSec=$((elapsedSec - (elapsedMin*60)))
echo
echo "Installation ran $elapsedMin:$elapsedSec min:sec."
echo

# vim: set ts=2 sw=2 sts=2 tw=0: