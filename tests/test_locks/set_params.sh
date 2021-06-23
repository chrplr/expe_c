#! /bin/bash

FILE=params.toml


touch $FILE

(
  unset foo
  exec {foo}< $FILE
  flock -e $foo
  cat >$FILE <<EOF
square_length = 200
square_color = 0xFFFFFFFFF
circle_radius = 50
circle_color = 0x0000000FF
background_color = 0xFFFFFFFFF
EOF
)


sleep 1

(
    unset foo
    exec {foo}< $FILE
    flock -e $foo
    cat >$FILE <<EOF
square_length = 333
square_color = 0xFFFFFFFFF
circle_radius = 50
circle_color = 0x0000000FF
background_color = 0xFFFFFFFFF
EOF
)


