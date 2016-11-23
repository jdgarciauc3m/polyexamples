COUNTERS1="-e'{cpu-clock,instructions,cache-references,cache-misses,LLC-loads,LLC-load-misses}'"
COUNTERS2="-e'{branches,branch-misses}'"

INFILES="1k 10k 100k 1m"
for i in $INFILES
do
  echo "***Evaluating $i***"
  perf stat -r 10 $COUNTERS1 ./area $i.data 2> $i.stat
done
