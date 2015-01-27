#!/bin/sh

WORKDIR=${TMPDIR:-/tmp}/test_prog1.$$
mkdir -p $WORKDIR

if [ -x ./test_prog1 ]; then
  ./test_prog1
else
  echo test_prog1 does not exist.
fi

if [ -x ./calc ]; then

cat << EOF > $WORKDIR/input.$$
1
2
+
3
4
+
*
4
+
sqrt
EOF

cat << EOF > $WORKDIR/correct.$$
1
2
3
3
4
7
21
4
25
5
EOF

./calc < $WORKDIR/input.$$ > $WORKDIR/output.$$
#cat $WORKDIR/output.$$
if diff -q $WORKDIR/output.$$ $WORKDIR/correct.$$; then
  echo calc passed all tests.
else
  echo calc did not pass all tests:
  diff -y $WORKDIR/output.$$ $WORKDIR/correct.$$
fi

else
  echo calc does not exist.
fi

if [ -x ./ccalc ]; then

cat << EOF > $WORKDIR/input.$$
-1
sqrt
1
+
EOF

cat << EOF > $WORKDIR/correct.$$
(-1,0)
(0,1)
(1,0)
(1,1)
EOF

./ccalc < $WORKDIR/input.$$ > $WORKDIR/output.$$
cat $WORKDIR/output.$$
if diff -q $WORKDIR/output.$$ $WORKDIR/correct.$$; then
  echo ccalc passed all tests.
else
  echo ccalc did not pass all tests:
  diff -y $WORKDIR/output.$$ $WORKDIR/correct.$$
fi

else
  echo ccalc does not exist.
fi
