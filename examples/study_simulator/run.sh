numEngines=3
host=localhost
socket=51717

first=1
engineID=0
while [ $engineID -lt $numEngines ]
do
	python engine.py $host $socket $engineID $first > log/engine_$engineID.log &
	echo $!, >> pids.log
	engineID=`expr $engineID + 1`
	first=0
done