build: clean
	cmake -B build
	make -C build

clean:
	rm -rf ./build

coverage: sanitizers_test
	lcov -c -d build/CMakeFiles --exclude '*main*' -o ./build/info
	genhtml ./build/info -o ./build/html

valgrind_test:
	cmake -B build
	make -C build
	cd build
	valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ctest -VV
	cd ..

sanitizers_test:
	cmake -B build -DSANITIZERS=ON
	make -C build all test ARGS="-VV"

run:
	bash linters/run.sh