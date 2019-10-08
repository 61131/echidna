# echidna - IEC 61131-3 Virtual Machine

.PHONY: src tests

all: clean 
	make -C src
	test -x src/echidna && ln -s src/echidna echidna

clean:
	test -L echidna && rm echidna || true
	make -C src clean
	make -C tests clean
	rm -f core gcovr.xml || true

tests: clean
	make -C src libechidna.a
	make -C tests
#	gcovr -r . -x -o gcovr.xml 2>/dev/null || true

docker:
	docker build -t echidna .circleci/images
	docker tag echidna:latest robcasey/dev:echidna
	docker push robcasey/dev:echidna
