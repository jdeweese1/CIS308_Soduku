#CYAN 6
#YELLOW 3
#MAGENTA 5
echo "$(tput setaf 6)rm'ing out.txt"
rm out.txt
echo "$(tput setaf 6)Cleaning files..."
make clean > /dev/null


# Make main
echo "$(tput setaf 6)Making main...\n"
make main > /dev/null
# We can solve
echo "$(tput sgr 0)"

echo "About to solve a board by running $(tput setaf 3)'./main solve -i unsolved1.txt -o out.txt' $(tput sgr 0)"
echo "Here is the initial value of the board passed, press enter to continue"
echo "$(tput setaf 5)"
cat unsolved1.txt
echo "$(tput sgr 0)"

read LINE

./main solve -i unsolved1.txt -o out.txt > /dev/null
echo "About to $(tput setaf 3)cat out.txt $(tput sgr 0), press enter to continue"
read LINE
echo "$(tput sgr 0)"

echo "$(tput setaf 5)"
cat out.txt
echo "$(tput sgr 0)"

echo ""

# We can generate
tput setaf 6
echo "rm'ing out.txt"
rm out.txt
tput sgr 0
echo "About to generate a board by running $(tput setaf 3)'./main generate -o out.txt'"
tput sgr 0
read LINE
./main generate -o generated.txt
tput sgr 0
echo "About to $(tput setaf 3)cat generated.txt $(tput sgr 0), press enter to continue"
read LINE
tput setaf 5
cat generated.txt
read LINE
tput sgr 0
./main solve -i generated.txt -o out.txt > /dev/null
tput setaf 5
echo ""
cat out.txt
echo "\n\n"
tput sgr 0

# We can check that a board is valid
echo "About to validate a board is solved by running $(tput setaf 3)'./main check -i solved1.txt'"
read LINE
tput setaf 5
./main check -i solved1.txt
tput sgr 0
echo "\n\n"

# Check board is invalid
echo "About to check a board bad $(tput setaf 3)'./main check -i bad.txt'$(tput sgr 0)"
read LINE
tput setaf 5
./main check -i bad.txt
tput sgr 0

make test > /dev/null
echo "\n"
echo "About to run entire test suite"
read LINE
# We can also run tests
./test

# echo "\n\n"
# echo "About to run only board tests"
# read LINE
# ./test -board

# echo "About to run only dictionary tests"
# read LINE
# ./test -dict


echo "About to solve 100 boards"
read LINE
mkdir ./datafiles/solved > /dev/null
rm ./datafiles/solved/*

make main > /dev/null
init_time="$(date +%s)"
count=0
for file in "$PWD"/datafiles/unsolved/*
do
    ((count+=1))
    temp="$count solved.txt"
    echo "$temp"
    tput setaf 5
    ./main solve -i $file -o "$PWD"/datafiles/solved/"$temp"
    tput sgr 0
done 
final_time="$(date +%s)"
tput setaf 6
echo $((final_time-init_time)) "seconds to solve $count boards"
tput sgr 0


# for funsies lets generate a bunch
# for i in {1..100}
# do
# 	name="generated$i.txt"
# 	./main generate -o "$PWD"/datafiles/generated/"$name"
# 	# sleep 1
# done
make clean > /dev/null

