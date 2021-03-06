#!  /bin/bash
#
# Script to set up the build environment before running make for the first
# time. Note that this script was NOT generated by the GNU build system,
# and this project does not make use of the GNU build system. This script
# is responsible for creating a Depend file (which defines what header
# files each C source file depends on), since make fails unless a file
# titled Depend exists. That means that the Depend target cannot be built
# unless the file already exists.

touch Depend
make Depend

# vim: ft=sh ts=4 sw=4 et
