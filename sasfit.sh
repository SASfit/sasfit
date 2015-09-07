#!/bin/bash
# http://stackoverflow.com/a/630387
DIR="`dirname \"$0\"`"
UNAME="/bin/uname"
[ -f "$UNAME" ] || UNAME="/usr/bin/uname"
OS=$($UNAME -s)
if [ "$OS" == "Darwin" ]; then
  DYLD_LIBRARY_PATH="$DIR:$DYLD_LIBRARY_PATH" "$DIR"/sasfit
else
  LIBPATH="$DIR/lib"
  "$LIBPATH"/ld-[0-9].[0-9][0-9].so --library-path "$LIBPATH" "$DIR"/sasfit
fi;