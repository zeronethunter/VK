BUILD_DIR=build
REPORT_DIR=${BUILD_DIR}/report
PROJECT_DIR=~/vk/semester_1/C/task1

.PHONY: all

coverage:
	lcov -t "${BUILD_DIR}/tests/test_subnet" -o ${BUILD_DIR}/coverage.info -c -d ${BUILD_DIR}/subnet_lib/
	genhtml -o ${BUILD_DIR}/report ${BUILD_DIR}/coverage.info

clean:
	rm -rf ${BUILD_DIR}

build_off_sanitizers: clean
	cmake -B ${BUILD_DIR}
	cmake --build ${BUILD_DIR}

build_on_sanitizers: clean
	cmake -B ${BUILD_DIR} -DSANITIZERS=ON
	cmake --build ${BUILD_DIR}

valgrind: build_off_sanitizers
	valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ${BUILD_DIR}/tests/test_subnet

sanitizers: build_on_sanitizers
	${BUILD_DIR}/tests/test_subnet

docker:
	# sudo docker build . -f Dockerfile -t task1
	docker run -v ${PROJECT_DIR}:/home/project -it task1:latest

check:
	./linters/run.sh
