# Make main
read LINE
echo "Making main..."
make main
# We can solve
echo "About to solve a board by running './main solve -i unsolved1.txt -o out.txt'"
echo "Here is the initial value of the board passed, press enter to continue"
cat unsolved1.txt

read LINE

./main solve -i unsolved1.txt -o out.txt > /dev/null
echo "About to cat out.txt, press enter to continue"
read LINE
cat out.txt
# We can generate
echo "About to generate a board by running './main generate -o out.txt'"
read LINE
./main generate -o out.txt
echo "About to cat out.txt, press enter to continue"
read LINE
cat out.txt

# We can check that a board is valid
echo "About to validate a board is solved by running './main validate -i solved1.txt'"
read LINE
./main validate -i solved1.txt


# Make tests
echo "About to run entire test suite"
read LINE
make test
# We can also run tests